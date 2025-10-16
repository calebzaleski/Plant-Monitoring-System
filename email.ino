
#define ENABLE_SMTP
#define ENABLE_DEBUG

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>
#include <ReadyMail.h>
#include "wifi.h"

// ---------- Temp Sensor ----------
#define DHTPIN 15      // GPIO pin connected to DATA
#define DHTTYPE DHT22  // or DHT11
DHT dht(DHTPIN, DHTTYPE);



//gmail cert
const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n"
"MIIDdzCCAl+gAwIBAgIJAKK+2XnZkYBfMA0GCSqGSIb3DQEBCwUAMFIxCzAJBgNV\n"
"BAYTAlVTMRMwEQYDVQQIDApDYWxpZm9ybmlhMRQwEgYDVQQKDAtHb29nbGUgSW5j\n"
"MRcwFQYDVQQDDA5Hb29nbGUgU1NMIFJvb3QwHhcNMjEwMTAxMDAwMDAwWhcNMzEw\n"
"MTAxMDAwMDAwWjBSMQswCQYDVQQGEwJVUzETMBEGA1UECAwKQ2FsaWZvcm5pYTEU\n"
"MBIGA1UECgwLR29vZ2xlIEluYzEXMBUGA1UEAwwOR29vZ2xlIFNTTCBSb290MIIB\n"
"IjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAs0Yq1X7L4VYJbg9RJ87bHwZL\n"
"2rPNzZ5ZKZ/cB4hF8uVYwU5skY5Q2NJ5b3xB5d70tL+KMzz2GqOa5F7lP9BrgTPB\n"
"eXu6Xb2+sbkMfZ6uPq3/LmTQmFBvVbQbP7sRZyRllUu6e8b1g+4u8sFJoTGQjOQk\n"
"2/fCcxJf0q4pU1b7lwIDAQABo1AwTjAdBgNVHQ4EFgQU1NflO6YjGnm/vG6mKrF+\n"
"9WhC1BswHwYDVR0jBBgwFoAU1NflO6YjGnm/vG6mKrF+9WhC1BswDAYDVR0TBAUw\n"
"AwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAo/71S1ymL6tDypV1kMlQ9oVnB0Dzxy9R\n"
"ZyR5P5J2oE3VfyKzRzP7l3TQ1hLwTnro7DrC1cn4xnZxLx5N+0EwIDAQAB\n"
"-----END CERTIFICATE-----\n";

// Pins
const int buttonPin = 3;
const int soilPin   = 26;

// Globals
bool lastButtonState = HIGH;
bool emailSentThisMinute = false;
int lastMinute = -1;

// Network



WiFiClientSecure ssl_client;
SMTPClient smtp(ssl_client);
SMTPMessage msg;

// ---------- SOIL SENSOR ----------
String readSoil() {
    int soilValue = analogRead(soilPin);
    if (soilValue < 100) return "Error reading soil sensor.";
    else if (soilValue <= 300) return "Soil Moisture: " + String(soilValue) + ". Soil is too wet.";
    else if (soilValue <= 500) return "Soil Moisture: " + String(soilValue) + ". Soil is just right.";
    else return "Soil Moisture: " + String(soilValue) + ". Soil is too dry.";
}
// ---------- TEMP + HUMITY SENSOR ----------
String readTemp() {
    float tempValue = dht.readTemperature(true); // °F
    float humidityValue = dht.readHumidity();
    return "It is " + String(tempValue) + "°F in the area and humidity is " + String(humidityValue) + "%";
}

// ---------- WIFI ----------
void connectWiFi() {
    if (WiFi.status() == WL_CONNECTED) return;

    Serial.print("Connecting to Wi-Fi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    unsigned long startAttempt = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 30000) {
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✅ Wi-Fi connected!");
        Serial.print("IP Address: "); Serial.println(WiFi.localIP());
        ssl_client.setInsecure(); // ⚠️ only for testing, or use 
        //ssl_client.setCACert(root_ca);
    } else {
          Serial.print("\n❌ Failed to connect, status: "); 
          Serial.println(WiFi.status());    }
}

void maintainWiFi() {
    static unsigned long lastWiFiAttempt = 0;
    const unsigned long wifiRetryInterval = 15000;
    if (WiFi.status() != WL_CONNECTED && millis() - lastWiFiAttempt > wifiRetryInterval) {
        lastWiFiAttempt = millis();
        connectWiFi();
    }
}

// ---------- EMAIL ----------
void sendEmail(String subject, String body) {
    msg.headers.clear();
    msg.headers.add(rfc822_from, "Zpiprojects <Zpiprojects@gmail.com>");
    msg.headers.add(rfc822_to, "Caleb <Caleb.zaleski@icloud.com>");
    msg.headers.add(rfc822_subject, subject);
    msg.text.body(body);
    msg.timestamp = time(nullptr);

    auto statusCallback = [](SMTPStatus status) {
        Serial.print("[SMTP] "); Serial.println(status.text);
    };

    Serial.println("📧 Connecting to SMTP server...");
    if (smtp.connect("smtp.gmail.com", 465, statusCallback)) {
        smtp.authenticate(EMAIL_USER, EMAIL_APP_PASSWORD, readymail_auth_password);
        if (smtp.send(msg)) Serial.println("✅ Email sent successfully!");
        else Serial.println("❌ Failed to send email.");
    } else {
        Serial.println("❌ Failed to connect to Gmail SMTP.");
    }
}
// ---------- TIME SYNC ----------
time_t syncTime() {
    // Ensure Wi-Fi is connected first
    if (WiFi.status() != WL_CONNECTED) connectWiFi();

    // Set timezone for EST/EDT
    setenv("TZ", "EST5EDT,M3.2.0,M11.1.0", 1);
    tzset();

    // Configure NTP servers
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    // Wait for NTP sync (max 30s)
    Serial.print("Syncing time");
    time_t now = time(nullptr);
    unsigned long start = millis();
    while (now < 100000 && millis() - start < 30000) {
        Serial.print(".");
        delay(100);
        now = time(nullptr);
    }
    Serial.println("\n⏱️ Time synced!");

    // Print current local time
    struct tm *timeinfo = localtime(&now);
    Serial.printf("Current time: %02d:%02d:%02d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    return now; // return current time
}

// ---------- BUTTON ----------
void checkButton() {
    bool buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && lastButtonState == HIGH) {
        Serial.println("🔘 Button pressed! Sending email...");
        digitalWrite(LED_BUILTIN, HIGH);
        sendEmail("Button Pressed", "Button was pressed!\n" + readSoil() + readTemp());
        digitalWrite(LED_BUILTIN, LOW);
    }
    lastButtonState = buttonState;
}

// ---------- SCHEDULED EMAIL ----------
void checkScheduledEmail() {
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;

    // Define scheduled times
    const int scheduledHours[] = {7, 13, 18, 19, 21};
    const int scheduledMinutes[] = {0, 0, 0, 0, 0}; // 7:00, 15:00, 19:56

    for (int i = 0; i < 3; i++) {
        if (hour == scheduledHours[i] && minute == scheduledMinutes[i] && !emailSentThisMinute) {
            sendEmail("Scheduled Soil Update", "Scheduled soil reading:\n" + readSoil() + readTemp());
            emailSentThisMinute = true;
        }
    }

    // Reset flag when minute changes
    if (minute != lastMinute) {
        emailSentThisMinute = false;
        lastMinute = minute;
    }
}

// ---------- SETUP ----------
void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    digitalWrite(LED_BUILTIN, LOW);
    dht.begin();          // Initialize the sensor


    // Keep trying to connect to Wi-Fi until successful
    while (WiFi.status() != WL_CONNECTED) {
        connectWiFi();
        if (WiFi.status() != WL_CONNECTED) {
            // Blink LED to show retry
            digitalWrite(LED_BUILTIN, HIGH);
            delay(250);
            digitalWrite(LED_BUILTIN, LOW);
            delay(250);
            Serial.println("Retrying Wi-Fi in 5 seconds...");
            delay(5000);
        }
    }

    // Wi-Fi connected, sync time
    time_t now = syncTime();

    // Send startup email only after Wi-Fi is ready
    sendEmail("Pico W Online", "Device started successfully.\n" + readSoil() + readTemp());
}
// ---------- LOOP ----------
void loop() {
    maintainWiFi();

    // Optionally re-sync NTP every hour or so
    static unsigned long lastSync = 0;
    if (millis() - lastSync > 3600000) { // every 1 hour
        syncTime();
        lastSync = millis();
    }

    // Use local time for scheduled emails
    checkScheduledEmail();
    checkButton();
    delay(100);

    //digitalWrite(LED_BUILTIN, HIGH);
    //delay(50);
    //digitalWrite(LED_BUILTIN, LOW);
    //delay(50);
}