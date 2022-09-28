#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

// Beginning of: Libraries ...
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_SHT31.h"
#include <SoftwareSerial.h>
#include "SdsDustSensor.h"
#include <FastLED.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Beginning of: WI-FI data ...
char auth[] = "Your_Blynk_Authentication";
char ssidBlynk[] = "Your_WiFi_Name";
char passBlynk[] = "Your_WiFi_Password";
const char *ssid = ssidBlynk;
const char *password = passBlynk;

// Beginning of: PINs ...
#define BLYNK_PRINT Serial
Adafruit_SHT31 sht31 = Adafruit_SHT31();
SoftwareSerial mySerialS8(D5, D6);
#define SDS_RX D7
#define SDS_TX D8
#define LED_PIN 2
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];


// Beginning of: Variables ...
float hum;
float temp;
byte cmdS8[7] = {0xFE, 0x44, 0x00, 0x08, 0x02, 0x9F, 0x25};
float ppmS8;
unsigned char responseS8[7];
SdsDustSensor sds(SDS_RX, SDS_TX);
float SDS_pm25;
float SDS_pm10;
int fill_check = 0;
int delay_value = 0;
int NUM_LEDS_value = 0;

// Beginning of: Timer ...
BlynkTimer timer;

void SHT31() {
  hum = sht31.readHumidity();
  temp = sht31.readTemperature();  
}

void Dust() {
  PmResult pm = sds.readPm();
  if (pm.isOk())
  {
    SDS_pm25 = pm.pm25;
    SDS_pm10 = pm.pm10;
  }
}

void S8() {
  unsigned int responseHigh;
  unsigned int responseLow;
  mySerialS8.write(cmdS8, 7);
  memset(responseS8, 0, 7);
  while (mySerialS8.available())  {
    mySerialS8.readBytes(responseS8, 7);
    responseHigh = responseS8[3];
    responseLow = responseS8[4];
    ppmS8 = (256 * responseHigh) + responseLow;
  }
}

void printTo(String name, float value, String ea, int blynkPort) {
  Serial.print(name + "   : ");
  Serial.print(value);
  Serial.print(" " + ea);
  Serial.println(" ");
  Blynk.virtualWrite(blynkPort, value);
}

void printing() {
  printTo("Humidity", hum, "%", V0);
  printTo("Temperature", temp, "C", V1);
  printTo("PM 2.5", SDS_pm25, "ug/m3", V2);
  printTo("PM 10", SDS_pm10, "ug/m3", V3);
  printTo("CO2", ppmS8, "ppm", V4);
}

void Mode1_lightAuto() {
  int y1 = 0;
  int y2 = 0;
  int y3 = 0;
  int y = 0;
  if (SDS_pm25 > 0 || SDS_pm10 > 0 || ppmS8 > 0) {
    y1 = (-100 / 54.4) * SDS_pm25 + (5540 / 54.4);
    y2 = (-4/3) * SDS_pm10 + (304/3);
    y3 = (-0.0625) * ppmS8 + (125);
    y = min(y1, min(y2, y3));
    Serial.println(y1);
    Serial.println(y2);
    Serial.println(y3);
    Serial.println(y);
    fill_solid(leds, NUM_LEDS, CRGB(255, y, 4));
    FastLED.setBrightness(200);
    FastLED.show();
  }
  else
  {
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
    FastLED.setBrightness(0);
    FastLED.show();
  }
}

void readRun(){
  SHT31();
  Dust();
  S8();
  printing();
  Mode1_lightAuto();
}

void setup() {
  // Beginning of: Arduino WIFI OTA & Blynk
  Serial.begin(9600);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      type = "sketch";
    }
    else
    { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(auth, ssidBlynk, passBlynk);

  mySerialS8.begin(9600);

  // Beginning of: SHT31 ...
  sht31.begin(0x44);

  // Beginning of: SDS ...
  sds.begin();
  sds.setActiveReportingMode().toString();  // ensures sensor is in 'active' reporting mode
  sds.setCustomWorkingPeriod(3).toString(); // sensor sends data every 3 minutes

  // Blynk Timer for 30 sec
  timer.setInterval(30000L, readRun);

  // Led initializer
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.setBrightness(0);
  FastLED.show();
}

void loop() {
  ArduinoOTA.handle();
  Blynk.run();
  timer.run();
}