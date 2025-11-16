#include "config.h"
#include "wifi.h"

// ---------- SOIL SENSOR ----------
String readSoil() {
    int soilValue = plantMonitor.getWater();
    if (soilValue <= 30)  {
        return "Soil Moisture: " + String(soilValue) + ". Soil is too dry."; 
    }
    else if (soilValue <= 60) return "Soil Moisture: " + String(soilValue) + ". Soil is just right.";
    else return "Soil Moisture: " + String(soilValue) + ". Soil is too wet.";
}

int readASoil() {
    int soilAValue = analogRead(sensorPin); 
    return soilAValue;
}

String readTemp() {
    float soilTemp = plantMonitor.getTemp();
    return "Temp: " + String(soilTemp) + "°C";
} 

String readHumidity() {
    float soilHumidity = plantMonitor.getHumidity();
    return "Humidity: " + String(soilHumidity) + "%";
}
