![Intro](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Intro.png?raw=true)

HealthLamp Air is an IoT project built on the ESP8266 microchip. It's designed to measure, record and visualize the quality of air in your house in real time in the stylish & unique way.

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

## Mobile app dashboard (Blynk Legacy no-code mobile app):

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

The device prototype is currently working for a year in my house. Thousands of rows with multiple data were collected during this time.
In the below case studies I'm trying to check their accuracy and show some interesting facts and observations which were made during this time.

## Case # 1 - CO2 dataset investigation (or “I know when you are back home”)

I took 7 days of historical CO2 data measurement from my home and ran a small analysis (visualization was made in [Tableau Public](https://www.tableau.com)).

I hope the below graphs and observations will show CO2 sensor work, possible non-standard use scenarios, and just some interesting facts about CO2 itself. I also want to highlight that I’m not showing here the classic sensor’s use case - then you use the sensor to check when you should open a window.

**Graph 1 "CO2 (ppm) vs Time (hours) - All at once"**
![CO2_All](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/CO2_All.png?raw=true)

You can see that there are two main patterns on the graph. The first one is composed of regular workdays (Mon-Fri / 26-30 of September) and second one is just weekend days (Sat-Sun, 1-2 of October).

Let’s look closely at the workdays pattern.

**Graph 2 "CO2 (ppm) vs Time (hours) - Workdays"**
![CO2_Mon-Fri](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/CO2_Mon-Fri.png?raw=true)

Main observations (and some fun facts) here are:
1. Our wake-up time is around 8am. You can see a clear spike in CO2 level around that time. The reason for that is because the device is placed in a living (+kitchen) room so you can clearly see when we start our morning routine.
2. You can also note that we usually leave a house before 9am (except for Sep 27).
3. 4-5 hours is needed for CO2 to drop to the normal outdoor level (400-450 ppm). All windows in the house are closed but with a small gap for passive ventilation.
4. Clear CO2 spikes also show exact time when we arrive at home (it’s usually around 9pm). At this moment two thoughts jumped into my mind:
   - CO2 sensors could be used as a home security device (with closed windows and ventilation for the sake of clarity). CO2 spikes are clear enough to show the moment people enter a house (as was shown in the above analysis).
   - However, CO2 sensors connected to the internet could also be a potential security issue (if hacked they could be used as a hidden spy device)
5. During the night CO2 tempt to slowly decrease, but there is always a small peak somewhere in the middle of the night. It’s us moving back and forth, feeding our cat (or open/close windows to increase/decrease temperature or get some fresh air)

Finally, let’s have a look on the weekend’s CO2 pattern.

**Graph 3 "CO2 (ppm) vs Time (hours) - Weekends"**
![CO2_Sat-Sun](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/CO2_Sat-Sun.png?raw=true)

This one looks a little bit messier. A few things to highlight here:
1. Wake-up time is around 10am (there is a good spike which was observed many times before)
2. During the weekend most of the time we stayed at home, moving from one room to another (and opening and closing windows as well). So, the graph shows recurring peaks and valleys during the day.  

## Case # 2 - Correlation between sensors measurement

In this case study I was trying to understand how multiple measurements from the device are connected to each other.

A [Dataset]() is composed from 7 days of indoor measurements of:
 - CO2
 - [PM2.5](https://www.epa.gov/pm-pollution/particulate-matter-pm-basics)
 - [PM10](https://www.epa.gov/pm-pollution/particulate-matter-pm-basics)
 - Humidity
 - Temperature

Analysis was made in [Pandas](https://pandas.pydata.org) open source data analysis tool. I used [k-means clustering]( https://scikit-learn.org/stable/modules/generated/sklearn.cluster.KMeans.html) method to reveal dataset’s possible insights. All details and the source code you can find in this [Jupyter notebook]().


**Graph 1 – Sample 1, (CO2 vs Fine Particles PM2.5/PM10) k-means clustering results**
k = 4 was selected based on elbow method and silhouette coefficient

![Sample1](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Sample1.png?raw=true)

The algorithm brings to us 4 data groups:

| Cluster | CO2 level | PM2.5/10 level |
| --- | --- | --- |
|1 (Blue)|HIGH|LOW|
|2 (Purple)|HIGH|HIGH|
|3 (Red)|LOW|LOW|
|4 (Green)|LOW|HIGH|

**Graph 2 – Sample 2, (CO2 vs Humidity & Temperature) k-means clustering results**
k = 3 was selected based on elbow method

![Sample2](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Sample2.png?raw=true)

The algorithm brings to us 3 data groups:

| Cluster | CO2 level | Hum level | Temp level |
| --- | --- | --- | --- |
|1 (Blue)|HIGH|HIGH|HIGH|
|2 (Red)|LOW|LOW|LOW|
|3 (Green)|LOW|HIGH|HIGH|

**Graph 3 – Sample 3, (Humidity vs Fine Particles PM2.5/PM10) k-means clustering results**
k = 3 was selected based on elbow method

![Sample3](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Sample3.png?raw=true)

The algorithm brings to us 3 data groups:

| Cluster | Hum level | PM2.5/10 level |
| --- | --- | --- |
|1 (Blue)|LOW|LOW|
|2 (Red)|HIGH|HIGH|
|3 (Green)|MID|HIGH|

**Main observations and results:**

1. Sample # 1: CO2 and fine particles (PM2.5/PM10) levels have similar pattern, but there is no real correlation between these measurements. Fine particles in clusters 2 and 3 follow CO2 level and describe the simple theory that people presence affect fine particles level and increase their presence in the air.  At the same time, clusters 1 and 4 clearly show that PM2.5/PM10 is not really affected by people presence. Looks likely it’s based on the outdoor conditions mostly (wind speed and directions, weather in general, etc.).
2. Sample # 2: There is a good correlation between CO2, Humidity and Temperature levels (Cluster 1 and 2). The only outlier here is the green cluster 3 (particularly time between 22-09-30 and 22-10-01).
3. Sample # 3: There is some correlation between Humidity and fine particles level. The only clear cluster here is cluster 1, which says that usually low humidity level means low fine particles level.

Correlation summary:

|             | CO2 | PM2.5/10 | Hum | Temp |
| ---         | --- | ---      | --- | ---  |
|CO2          |-    |LOW       |HIGH |HIGH  |
|PM2.5/10     |LOW  |-         |MID  |LOW   |
|Hum          |HIGH |MID       |-    |HIGH  |
|Temp         |HIGH |LOW         |HIGH | -    |


# License

The content of this repository is licensed under a [CERN-OHL-S-2.0](https://cern-ohl.web.cern.ch)
