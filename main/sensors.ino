#include "config.h"
#include "wifi.h"


// ---------- SOIL SENSOR ----------
String readSoil() {
    int soilValue = plantMonitor.getWater();
    if (soilValue < 100) return "Error reading soil sensor.";
    else if (soilValue <= 300) return "Soil Moisture: " + String(soilValue) + ". Soil is too wet.";
    else if (soilValue <= 500) return "Soil Moisture: " + String(soilValue) + ". Soil is just right.";
    else return "Soil Moisture: " + String(soilValue) + ". Soil is too dry.";
} 
String readTemp() {
    int soilTemp = plantMonitor.getTemp();
    return "Temp" + String(soilTemp)
} 
String readHumidity() {
    int soilHumidity = plantMonitor.getHumidity();
    return "Humidity" + String(soilHumidity)
} 
