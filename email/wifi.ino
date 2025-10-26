#include "config.h"
#include "wifi.h"


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
