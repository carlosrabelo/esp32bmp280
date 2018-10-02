#include <Arduino.h>
#include <WiFi.h>

#include "secret.h"

void connectToWiFi() {
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(1000);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.print("WiFi connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.print("Signal strength: ");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");

        if (WiFi.RSSI() < -70) {
            Serial.println("Warning: WiFi signal strength is weak (< -70dBm)");
        }
    } else {
        Serial.println();
        Serial.println("WiFi connection failed!");
    }
}

void setup() {
    Serial.begin(115200);
    delay(10);

    Serial.println();
    Serial.println("ESP32 starting...");
    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());

    connectToWiFi();
}

void loop() {
}
