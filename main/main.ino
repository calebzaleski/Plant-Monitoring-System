#define ENABLE_SMTP
#define ENABLE_DEBUG

//Project Libraries
#include "wifi.h"
#include "config.h"



// ---------- BUTTON ----------
void checkButton() {
    bool buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && lastButtonState == HIGH) {
        Serial.println("🔘 Button pressed! Sending email...");
        digitalWrite(LED_BUILTIN, HIGH);
        sendEmail("Button Pressed", "Button was pressed!\n" + readSoil()/* + readTemp()*/, "Caleb.Zaleski@icloud.com");
        digitalWrite(LED_BUILTIN, LOW);
    }
    lastButtonState = buttonState;
}

void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    digitalWrite(LED_BUILTIN, LOW);

    client.setServer(mqtt_server, 1883);

    while (WiFi.status() != WL_CONNECTED) {
        connectWiFi();
        if (WiFi.status() != WL_CONNECTED) {
            delay(5000);
        }
    }

    connectMQTT();

}

void loop() {
    maintainWiFi();

    static unsigned long lastSync = 0;
    if (millis() - lastSync > 3600000) { // every 1 hour
        syncTime();
        lastSync = millis();
    }

    connectMQTT();

    if (i == 600) {
      pushMQTT();
      i = 1;
    }
    i++;

    checkScheduledEmail();
    checkButton();

    delay(100); // .1 second

}