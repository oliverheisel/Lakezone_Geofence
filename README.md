# Lakezones Geofence
 Check in wich zone you are and what you are allowed to do:

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





## 1. Introduction (Summary)

## 2. My goals for this project

## 3. Usecase

## 4. How does it work?

### 4.1 Create the map
1. Open QGIS and import the base file "BASEMAP_Swisstopo_Lakes_WGS84.geojson"
2. Duplicate the layer, toggle edit and delete all lake that you don't want to work on. Rename the layer e.g. "LakeZurich"
3. Toolbox -> Reproject to "EPSG:2056 - CH1903+ / LV95" -> so we can buffer by meter -> temporary layer is enough
4. Toolbox -> Buffer to -150m and -300m. Temporary is enough. We need 
5. Toolbox -> Reproject to "WGS84" both. and save the them to Geopackage named e.g. "LakeZurich-150m_WGS84" and "LakeZurich-300m_WGS84"
6. Toolbox -> Vertics and save the them to Geopackage named e.g. "LakeZurich-150m_Vertics_WGS84" and "LakeZurich-300m_Vertics_WGS84"
SAVE!

**Optional**
If you want to create background maps/ images. Do it with WMS
Link: https://wms.geo.admin.ch/?VERSION=1.3.0&LAYERS=ch.bafu.bundesinventare-bln&STYLES=default&CRS=EPSG:2056&BBOX=2550000,1060000,2660000,1140000&WIDTH=800&HEIGHT=582 <br>

1. SWISS IMAGES
2. 100'000

![MapAfterCreatingZones](ReadmeFiles/Image_Map-ZonesCreated.png)



**Optional 2**
If you are using a not so powerfull board to run the script, you need to reduce the count of points. The most effective method for is to narrow down your polygons.

Create a list with points: 
-> Attribute table
-> Python script


### 4.2 Create the Hardware

### 4.3 Create the software

## 5. My tests

## 6. Conclusion
