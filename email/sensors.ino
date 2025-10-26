#include "config.h"
#include "wifi.h"


// ---------- SOIL SENSOR ----------
String readSoil() {
    int soilValue = analogRead(soilPin);
    if (soilValue < 100) return "Error reading soil sensor.";
    else if (soilValue <= 300) return "Soil Moisture: " + String(soilValue) + ". Soil is too wet.";
    else if (soilValue <= 500) return "Soil Moisture: " + String(soilValue) + ". Soil is just right.";
    else return "Soil Moisture: " + String(soilValue) + ". Soil is too dry.";
} 
/* // ---------- TEMP + HUMITY SENSOR ----------
String readTemp() {
    float tempValue = dht.readTemperature(true); // °F
    float humidityValue = dht.readHumidity();
    return "It is " + String(tempValue) + "°F in the area and humidity is " + String(humidityValue) + "%";
} */