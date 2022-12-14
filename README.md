![Intro](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Intro.png?raw=true)

HealthLamp Air is an IoT project built on an ESP8266 microchip. It's designed to measure, record and visualize the air quality in your house in real time in a stylish way.

**Project status:** The device was built in 2021. At the moment, the MVP has been working for one year.  

# Product design & development

This product is positioned to be a stylish part of your house while offering a full range of modern air quality control capabilities.

I decided to use natural materials and developed a special conical design which provides elegant air quality visualization and efficient airflow for precise measurements.

![Features](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Features.png?raw=true)

The project development process includes the following steps:
1. Product design and idea development
2. Hardware prototyping and components selection
2. Software development
3. Body molding and internal components printing
4. Prototype assembly and testing

## Product design development (Autodesk Fusion 360 / 3ds Max):

![Render1](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Render1.PNG?raw=true)

## Hardware prototyping (Easy EDA):

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

The first project's draft was developed in an Arduino IDE environment. Currently, it is conducted in the [PlatformIO](https://platformio.org) framework.

All information from the device is stored and visualized in a [Blynk](https://blynk.io) IoT framework (legacy one). The mobile app is developed in a Blynk no-code environment.

Project's diagram:  

![ProjectDiagram](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/ProjectDiagram.png?raw=true)

# Data validation results:

I personally have been using this device for a year, without any issues. Thousands of rows with multiple data were collected during this time. In the case studies below, I'm validating its accuracy and presenting some interesting facts and observations which were made during this time.

## Case # 1 - CO2 dataset analysis (or “I know when you are back home”)

I took 7 days of CO2 data measurement from my home and ran a small analysis (the visualization was made in [Tableau Public](https://www.tableau.com)).

I hope the below graphs and observations will show how the CO2 sensor works, possible non-standard use cases, and some interesting facts about CO2 indoor behavior.

**Graph 1 "CO2 (ppm) vs Time (hours) - All at once"**
![CO2_All](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/CO2_All.png?raw=true)

There are two main patterns on the graph above. The first pattern represents regular workdays (Mon-Fri / 26-30 of September) and the second shows weekend days (Sat-Sun, 1-2 of October).

Let’s have a close look at them. We will start from the pattern # 1.

**Graph 2 "CO2 (ppm) vs Time (hours) - Workdays"**
![CO2_Mon-Fri](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/CO2_Mon-Fri.png?raw=true)

The main observations here are:
1. My wake-up time was around 8am. You can see a clear spike in CO2 levels around that time. The reason for that is because the device was placed in my living room. So you can clearly see when I woke up and started my morning routine.
2. You could also note that I mostly left my house before 9am (except for Sep 27).
3. It took 4-5 hours for the CO2 level to drop to the normal outdoor level (370-420 ppm). All the windows in the house were closed with a small gap for passive ventilation.
4. The strong CO2 spikes also show the exact time when I arrived home (it’s mostly around 9pm). *At this moment two thoughts jumped into my mind:*
   - *CO2 sensors could be used as a home security device (ideally, with closed windows and ventilation). CO2 spikes are strong enough to show the moment when people enter a house.*
   - *However, CO2 sensors connected to the internet could also be a potential security issue (if hacked they could be used as a hidden spy device)*
5. During the night CO2 levels tend to slowly decrease, but there are still some small peaks somewhere in the middle of the night. This could be attributed to me moving back and forth feeding our cat (or opening/closing windows to increase/decrease the temperature or to get some fresh air)

Finally, let’s take a look at the weekend’s CO2 pattern.

**Graph 3 "CO2 (ppm) vs Time (hours) - Weekends"**
![CO2_Sat-Sun](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/CO2_Sat-Sun.png?raw=true)

This one looks a little bit messier. A few things to highlight here:
1. The wake-up time was around 10am (there is a spike - like the one in the pattern # 1)
2. During the weekend I mostly stayed at home, moving from one room to another (+opening/closing windows). So, the graph shows recurring peaks and troughs during the day.

## Case # 2 - Full dataset analysis (looking for a correlation between sensors measurements)

In this case study I'll try to understand how multiple measurements from the device are connected to each other.

A [Dataset](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/analytics/csv/DS-1.csv) represents 7 days of indoor measurements. Dataset features:
 - CO2
 - [PM2.5](https://www.epa.gov/pm-pollution/particulate-matter-pm-basics)
 - [PM10](https://www.epa.gov/pm-pollution/particulate-matter-pm-basics)
 - Humidity
 - Temperature

The analysis was done using [Pandas](https://pandas.pydata.org) open source data analysis tool. I used the [k-means clustering]( https://scikit-learn.org/stable/modules/generated/sklearn.cluster.KMeans.html) method to reveal the dataset’s insights. You can find all the details and source code in this [Jupyter notebook](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/analytics/pandas/Main.ipynb).


**Graph 1 "Sample 1, (CO2 vs Fine Particles PM2.5/PM10) k-means clustering results"**

k = 4 was selected based on the elbow method and the silhouette coefficient *(please refer to the Jupyter notebook for more details)*

![Sample1](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Sample1.png?raw=true)

The algorithm revealed the following 4 data clusters:

| Cluster | CO2 level | PM2.5/10 level |
| --- | --- | --- |
|1 (Blue)|HIGH|LOW|
|2 (Purple)|HIGH|HIGH|
|3 (Red)|LOW|LOW|
|4 (Green)|LOW|HIGH|

**Graph 2 "Sample 2, (CO2 vs Humidity & Temperature) k-means clustering results"**

k = 3 was selected based on the elbow method and the silhouette coefficient *(please refer to the Jupyter notebook for more details)*

![Sample2](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Sample2.png?raw=true)

The algorithm revealed the following 3 data clusters:

| Cluster | CO2 level | Hum level | Temp level |
| --- | --- | --- | --- |
|1 (Blue)|HIGH|HIGH|HIGH|
|2 (Red)|LOW|LOW|LOW|
|3 (Green)|LOW|HIGH|HIGH|

**Graph 3 "Sample 3, (Humidity vs Fine Particles PM2.5/PM10) k-means clustering results"**

k = 3 was selected based on the elbow method and the silhouette coefficient *(please refer to the Jupyter notebook for more details)*

![Sample3](https://github.com/rodionpotachin/iot-air-quality-healthlamp-project/blob/master/img/Sample3.png?raw=true)

The algorithm revealed the following 3 data clusters:

| Cluster | Hum level | PM2.5/10 level |
| --- | --- | --- |
|1 (Blue)|LOW|LOW|
|2 (Red)|HIGH|HIGH|
|3 (Green)|MID|HIGH|

**Main observations and results:**

1. Sample # 1: The CO2 and fine particle (PM2.5/PM10) levels behave quite similarly. However, there is no real correlation between these measurements. The fine particle levels in clusters 2, 3 follow the CO2 level and propose a basic theory that people's presence disturbs fine particles and increases their level in the air. At the same time, clusters 1 and 4 clearly show that PM2.5/PM10 levels are not really affected by people's presence. It looks likely that it gets affected by outdoor conditions (wind speed and directions, weather in general, etc.) and potential industrial pollutants.
2. Sample # 2: There is a strong correlation between CO2, Humidity and Temperature levels (Cluster 1 and 2). The only outlier here is the green cluster (have a look at the measurements at the time between Sep 30 and Oct 1. The humidity level shows a clear peak while the CO2 constantly decreases).
3. Sample # 3: There is some kind of correlation between Humidity and Fine particle levels. The only robust cluster here is cluster # 1. It shows that low Humidity levels are linked to low Fine particle levels (at least in our experiment).

Finally, here is the correlation analysis summary:

|             | CO2 | PM2.5/10 | Hum | Temp |
| ---         | --- | ---      | --- | ---  |
|CO2          |-    |LOW       |HIGH |HIGH  |
|PM2.5/10     |LOW  |-         |MID  |LOW   |
|Hum          |HIGH |MID       |-    |HIGH  |
|Temp         |HIGH |LOW         |HIGH | -    |

I think the above case studies show that the device is working. All the sensor signals are synchronized with real world conditions and show a reasonable correlation.

# License

The content of this repository is licensed under a [CERN-OHL-S-2.0](https://cern-ohl.web.cern.ch)
