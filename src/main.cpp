#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "secret.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define BMP280_I2C_ADDRESS (0x76)

Adafruit_BMP280 bmp;

float temperature, pressure, altitude;

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
    Serial.println("ESP32 BMP280 Weather Station starting...");
    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());

    if (!bmp.begin(BMP280_I2C_ADDRESS)) {
        Serial.println("Could not find a valid BMP280 sensor, check wiring!");
        Serial.println("Verify I2C connections: SDA=21, SCL=22");
        while (1);
    }

    Serial.println("BMP280 sensor initialized successfully");

    connectToWiFi();
}

unsigned long lastReading = 0;
const unsigned long READING_INTERVAL = 5000;

void readAndPrintSensor() {
    temperature = bmp.readTemperature();
    pressure = bmp.readPressure() / 100.0F;
    altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);

    if (isnan(temperature) || isnan(pressure)) {
        Serial.println("ERROR: Failed to read from BMP280 sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.print(" °C | Pressure: ");
    Serial.print(pressure, 1);
    Serial.print(" hPa | Altitude: ");
    Serial.print(altitude, 1);
    Serial.println(" m");
}

void loop() {
    unsigned long now = millis();

    if (now - lastReading >= READING_INTERVAL) {
        lastReading = now;
        readAndPrintSensor();
    }
}
