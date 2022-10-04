![Intro](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Intro.png?raw=true)

HealthLamp Air is an IoT project built on the ESP8266 microchip. It's designed to measure, record and visualize the quality of air in your house in real time in a the stylish & unique way.

# Design & development

The main idea of this device is to be a minimalistic stylish part of your house design while offering a full range of modern air quality control capabilities.

I decided to use the natural materials and developed the special conical design which provide elegant lightning air quality visualization and great airflow.

![Features](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Features.png?raw=true)

Project development included the following parts:
1. Product design and idea development
2. Hardware prototype development and components selection
2. Software prototype development
3. Body molding and internal components printing
4. Prototype assembly and testing

## Product design development (Autodesk Fusion 360 / 3ds Max):

![Render1](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Render1.PNG?raw=true)

## Hardware development (Easy EDA):

![PCB](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/PCB.png?raw=true)

## Prototype assembly and testing:

![MVP](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/MVP.png?raw=true)

## Mobile app dashboard (designed in Blynk IoT platform environment):

![App](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/App.png?raw=true)

## Technical specification

| Parameter  | Description  |
| ---------- | ------------ |
| Connectivity |Wi-Fi IEEE 802.11 b/g/n 2.4GHz|
| CO2 Sensor | 0-10,000 ppm (±40 ppm)|
| PM2.5 / PM10 | 0-999.9 μg /m3 (±10 μg/m3)|
| Temp sensor| -10 to 60 ℃ (±0.3 ℃)|
| Humidity sensor | 0%-99% RH (±2% RH)|
| Power input | 5V DC 1000 mA |

# Software development

The first project's draft was developed in Arduino IDE environment. Currently, all development is occurring in the [PlatformIO](https://platformio.org) framework.

All information from the device is stored and visualized in [Blynk](https://blynk.io) IoT framework (legacy one). A mobile app is developed in the Blynk no-code environment.

Project diagram (at the current moment):  

![ProjectDiagram](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/ProjectDiagram.png?raw=true)

# Data validation results:

The device is currently working for a year. Thousands of rows with multiple data were collected during this time.
In the below case studies I'm trying to check their accuracy and show some interesting facts and observations which were made during this time.

## Case # 1

## Case # 2

## Case # 3

# License

The content of this repository is licensed under a [CERN-OHL-S-2.0](https://cern-ohl.web.cern.ch)
