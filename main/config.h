#ifndef CONFIG_H
#define CONFIG_H

#include <WiFiClientSecure.h>
#include <ESP_Mail_Client.h> 
#include <WiFi.h>
#include <PubSubClient.h>

// ---------- PIN DEFINITIONS ----------
extern const int soilPin;
extern const int buttonPin;

// ---------- MQTT ----------
extern const char* mqtt_server;

// ---------- TIME ----------
extern int i;
extern time_t currentTime;

// ---------- STATE VARIABLES ----------
extern bool emailSentThisMinute;
extern int lastMinute;
extern bool lastButtonState;

// ---------- NETWORK CLIENTS ----------
extern WiFiClientSecure ssl_client;
extern SMTPSession smtp;
extern WiFiClient espClient;
extern PubSubClient client;

// Function prototypes
void connectWiFi();
void maintainWiFi();
void connectMQTT();
void pushMQTT();
String readSoil();
void sendEmail(String subject, String body, String to);
void checkScheduledEmail();
void checkButton();
time_t syncTime();
String Time();

#endif