#include "config.h"
#include "wifi.h"


void connectMQTT() {
    while (!client.connected()) {
        client.connect("PicoWClient");
        delay(5000);
    }
}

void pushMQTT() {
    String commit = readSoil() + " | " + Time();
    client.publish("Soil_Sensor/topic", commit.c_str());
}