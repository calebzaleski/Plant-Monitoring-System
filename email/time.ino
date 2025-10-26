#include "config.h"
#include "wifi.h"


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
// ---------- TIME ----------

String Time() {
    time_t now = time(nullptr);              // get current epoch time
    struct tm *timeinfo = localtime(&now);   // convert to local time

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // format: YYYY-MM-DD HH:MM:SS

    return String(buffer);                   // return as Arduino String
}
