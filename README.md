# Lakezones Geofence
## 1. Introduction (Summary)

 Check in wich zone you are and what you are allowed to do:

![Device](ReadmeFiles/HeaderImage.png)


## Table of Contents:
[1. Introduction (Summary)](#1-introduction-summary) <br>
[2. My goals for this project](#2-my-goals-for-this-project) <br>
[3. Usecase](#3-usecase) <br>
[4. How does it work?](#4-how-does-it-work) <br>
&nbsp;&nbsp;[4.1 Create the map](#41-create-the-map) <br>
&nbsp;&nbsp;[4.2 Create the Hardware](#42-create-the-hardware) <br>
&nbsp;&nbsp;[4.3 Create the software](#43-create-the-software) <br>
[5. My tests](#5-my-tests) <br>
[6. Conclusion](#6-conclusion) <br>



## 2. My goals for this project

## 3. Usecase
- auf Binnenseene gibt es unterschiedliche Zonen, für die unterschiedliceh Regeln gelten
- Vorallem in der Schweiz kann dies zu gravierenden Bussgeldern führen
- Ziel der Vorschriften ist es, Schwimmer, SUpper und Tiere in der Uferzone zu schützen.
- 

- Von Bootsführer ist vorgesehen, die Abstände zu schätzen. Das mag einfach seinen, wenn man Zeit hat und nur einmal rausfährt. Als Trainier von Junioren kann dies jedoch öfter hinterannder passieren. Um keine Strage zu risikieren, lassen sich so die Abstände besser einschätzen,
- Die Wasserschutzpolizei führt die Messungen auf zwei Arten durch. zum einen mit einem Fernglas mit integriertem Distanzmesser oder via Kartenplotter und der eingezeichneten 300m Zone. Beide Methoden lassen keine genuaen Messungen zu.

## 4. How does it work?

### 4.1 Create the map
1. Open QGIS and import the base file "BASEMAP_Swisstopo_Lakes_WGS84.geojson"
2. Duplicate the layer, toggle edit and delete all lake that you don't want to work on. Rename the layer e.g. "LakeZurich"
3. Toolbox -> Reproject to "EPSG:2056 - CH1903+ / LV95" -> so we can buffer by meter -> temporary layer is enough
4. Toolbox -> Buffer to -150m and -300m. Temporary is enough. We need 
5. Toolbox -> Reproject to "WGS84" both. and save the them to Geopackage named e.g. "LakeZurich-150m_WGS84" and "LakeZurich-300m_WGS84"
   // before continuting with the next step. Have a look at optional 2 (Manipulation the created zones)
7. Toolbox -> Vertics and save the them to Geopackage named e.g. "LakeZurich-150m_Vertics_WGS84" and "LakeZurich-300m_Vertics_WGS84"
SAVE!

**Optional**
If you want to create background maps/ images. Do it with WMS
Link: https://wms.geo.admin.ch/?VERSION=1.3.0&LAYERS=ch.bafu.bundesinventare-bln&STYLES=default&CRS=EPSG:2056&BBOX=2550000,1060000,2660000,1140000&WIDTH=800&HEIGHT=582 <br>

1. SWISS IMAGES
2. 100'000

![MapAfterCreatingZones](ReadmeFiles/Image_Map-ZonesCreated.png)



**Optional 2** - Manipulation and reduction (if you do it before converting it to Vertics, you just have to do it once.)
If you are using a not so powerfull board to run the script, you need to reduce the count of points. The most effective method for is to narrow down your polygons.
1. Choose the Map you want to work on
2. Toggle Editing 
3. Click on the Vertex-Tool
4. Change everything that you like - Change the zones/ Delete Points


<img src="ReadmeFiles/Image_RemovedZoneSeebecken.png" align="left" width="500px"/>
For example the "Seebecken in Zurich has a special rule wich allign with the rule for the first 150m from shore. So I just deleted the part of the 300 zone.

Here you also can see the vertics, that describe the polygon. Its basicly nothing else then the points where the outline of the polygone changes its direction.

<br clear="left"/>
<br>
<br/>
Since I am using a Arduino Nano for my project, i need to reduce the count of the points. I decided to not simplify the form, to keep the accuracy, and just keep the part, where I will be mainly using it.
So Area between Zurich and Thalwil. (4265 Point reduced to around 600)
<br/>
<br/>

![MapAfterCreatingZones](ReadmeFiles/Image_ReducedArea.png)



**Create a list with points for the software:**
Export the Attribute table
1. right click on the layer with vertics
2. "just show feature visible on map" (bottom left)
3. Click "open Attribute Table"
4. Open fiel calculator
5. Create new field (Expression: "x($geometry)")
6. Repeat with (Expression: "y($geometry)")
7. Check the x and y column
8. Close the Attribute table
9. Right click on the layer and click "Export" & "Save Feature as..."
10. Save as CSV

**Restructure the List of Points, so it can be copyed and pasted into the arduino script**
1. Open the python script "CreateListOfPoints.py"
2. Change the paths to your previously created csv's
3. Run the script
4. Copy the output to your software and replace the existing coordinates (WATCH OUT! Don't swap X and Y)


### 4.2 Create the Hardware

**What you need:**
- Arduino (Nano)
- GPS-Modul
- 3x LEDs (red/yellow/green)
- 3x resistors (220 Ω)
- LCD Display (optional)
- Power Source (PowerBank with cable)
- Several cables to solder or pin the circuits.

**Circuit diagram**
![CircuitDiagramm](ReadmeFiles/circuitdiagram.png)

Create a copy of the **Wokwi project** and modify it according to your needs: [https://wokwi.com/projects/396244731597052929](https://wokwi.com/projects/396244731597052929)

### 4.3 Create the software

Find the script for the arduino [here](Arduino_Scripts/CheckCoordinatesSpeedBlinking10.ino). And requirements [here](Arduino_Scripts/requirements.txt). The script is commented and filled with sample coordinates of Lake Zurich.

The software setup for this project involves the following key components and steps:

**Initialization** <br>
The system initializes by setting up the libraries needed for GPS data processing (TinyGPS++), serial communication (SoftwareSerial), and LCD display control (LiquidCrystal_I2C). It configures the pins for the GPS module, LEDs, and LCD, and establishes serial connections for both GPS data reception and debugging output.

**GPS Data Processing** <br>
The software continuously reads from the GPS module, parsing latitude, longitude, and speed using the TinyGPS++ library. This parsed data drives the application's logic flow.

**Geofencing with Ray-Casting** <br>
Utilizing the Ray-Casting algorithm, the software determines the presence of the device within predefined polygonal geofences. Based on the device's location:
- Red LED indicates outside both polygons.
- Yellow LED signals presence within the larger polygon.
- Green LED lights up within the smaller polygon.

**LED and LCD Management** <br>
LED behavior is controlled based on the geolocation data and speed, with LEDs blikin, when the allowed speed is exceeded (10 km/h - red / 10 km/h - yellow / 40 km/h - green) . The LCD displays real-time updates of the current geographical coordinates. The software employs non-blocking delay techniques using millis() to manage LED blinking without halting the system.

This streamlined approach ensures efficient data handling and responsive output through the hardware interfaces, integrating technical operations into a cohesive system.

## 5. My tests
- Ich habe mehrere Test gemacht, welche mehrer Iterationen zur Fehlerbehebung benötigt haben. Teil simple Fehler führen zu vollständigen unfähigkeit des Gerätes.
- Zonen werden akurat angezeigt und wechseln die Farbe.
- Geschwindifkeit stimmt der eines Speedometers des iphones überein und es fängt den Geschwindigfkeitsvorschriften an entsprechend zu blinken
- IKEA Boxen sind die Idealen COntainer für Prototypen. Wasserdicht und haben genug platz.
- Das Ersetzen von LED Durch "Leucht-Würmer" von AliExpress erhöht die Sichtbarkeit auch bei Sonnenschein.
- 

![TheColorTest](ReadmeFiles/AllColors.png)

## 6. Conclusion
- Es war sehr interessant herauszufinden, wie man Karten entsprechend bearbeiten kann, um sie in eine Probgrammierung einzubinden.
- Der Unique Selling Point ist nicht gegeben. Eine kommerzielle Verwertung des Projektes hätte keinen Erfolg, da die Wasserschutzpolizei auch nicht genau kontrolliert, sondern auf den guten Menschenverstand abzielt.
