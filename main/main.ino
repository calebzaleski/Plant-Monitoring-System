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
        sendEmail("Button Pressed", String("Button was pressed!") + "Raw value: " + String(readASoil())  + "Soil reading: " + readSoil()  + readTemp() + readHumidity() + String(wtime), "Caleb.Zaleski@icloud.com");
        digitalWrite(LED_BUILTIN, LOW);
    }
    lastButtonState = buttonState;
}

void setup() {

    pinMode(pumpPin, OUTPUT);
    digitalWrite(pumpPin, LOW);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    digitalWrite(LED_BUILTIN, LOW);
     

    Serial.begin(115200);
    

// ---------- Pico Sensor Code S ----------
    Serial2.setRX(5);    
    Serial2.setTX(4);     
    Serial2.begin(9600);  
    plantMonitor.begin();   
// ---------- Pico Sensor Code E ----------

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
    checkScheduledEmail();
    checkButton();


// ---------- MQTT SERVER S ----------
    connectMQTT();

    if (i == 600) {
      pushMQTT();
      i = 1;
    }
    
    i++;
// ---------- MQTT SERVER E ----------

    delay(100); // .1 second

// ---------- WATERPUMP ----------   
 
if (readASoil() < 600 && x > 24000) {
    Waterpump3_5s();
    x = 1;
    wtime++;
}
    x++;
}