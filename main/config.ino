#include "config.h"
#include "wifi.h"


// ---------- PIN DEFINITIONS ----------
const int buttonPin   = 15;

// ---------- PLANT MONITOR ----------
PlantMonitor plantMonitor(Serial2);  // for pico/esp32/


// ---------- MQTT ----------
const char* mqtt_server = "192.168.1.30";

// ---------- TIME ----------
int i = 1;
time_t currentTime;

// ---------- STATE VARIABLES ----------
bool emailSentThisMinute = false;
int lastMinute = -1;
bool lastButtonState = HIGH;

// ---------- NETWORK CLIENTS ----------
WiFiClientSecure ssl_client;
SMTPSession smtp;  
WiFiClient espClient;
PubSubClient client(espClient);
