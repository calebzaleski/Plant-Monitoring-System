#include "config.h"
#include "wifi.h"


// ---------- PIN DEFINITIONS ----------
const int soilPin     = 26;
const int buttonPin   = 3;

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
