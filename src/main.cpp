#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "secret.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define BMP280_I2C_ADDRESS (0x76)

Adafruit_BMP280 bmp;
WiFiServer server(80);

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

String sendHTML(float temperature, float pressure, float altitude) {
    String ptr = "<!DOCTYPE html>";
    ptr += "<html>";
    ptr += "<head>";
    ptr += "<title>ESP32 Weather Station with BMP280</title>";
    ptr += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    ptr += "<style>";
    ptr += "body { font-family: Arial, sans-serif; margin: 0; padding: 0; text-align: center; background-color: #f4f4f4; color: #333; }";
    ptr += "h1 { font-size: 2.5em; margin: 20px 0; }";
    ptr += ".data { margin: 20px auto; padding: 20px; background: #fff; border-radius: 10px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); width: 90%; max-width: 400px; }";
    ptr += ".icon { width: 50px; margin: 0 auto 10px; }";
    ptr += ".label { font-size: 1.2em; font-weight: bold; }";
    ptr += ".value { font-size: 2em; color: #007BFF; }";
    ptr += "</style>";
    ptr += "</head>";
    ptr += "<body>";
    ptr += "<h1>ESP32 Weather Station</h1>";

    ptr += "<div class='data'>";
    ptr += "<img src='https://img.icons8.com/ios-filled/50/temperature.png' alt='Temperature Icon' class='icon'>";
    ptr += "<div class='label'>Temperature</div>";
    ptr += "<div class='value'>" + String(temperature, 1) + " &deg;C</div>";
    ptr += "</div>";

    ptr += "<div class='data'>";
    ptr += "<img src='https://img.icons8.com/ios-filled/50/pressure.png' alt='Pressure Icon' class='icon'>";
    ptr += "<div class='label'>Pressure</div>";
    ptr += "<div class='value'>" + String(pressure, 1) + " hPa</div>";
    ptr += "</div>";

    ptr += "<div class='data'>";
    ptr += "<img src='https://img.icons8.com/ios-filled/50/mountain.png' alt='Altitude Icon' class='icon'>";
    ptr += "<div class='label'>Altitude</div>";
    ptr += "<div class='value'>" + String(altitude, 1) + " m</div>";
    ptr += "</div>";

    ptr += "</body>";
    ptr += "</html>";

    return ptr;
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

    if (WiFi.status() == WL_CONNECTED) {
        server.begin();
        Serial.println("Web server started");
        Serial.print("Access web interface at: http://");
        Serial.println(WiFi.localIP());
    }
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

void handleClient() {
    WiFiClient client = server.available();

    if (client) {
        Serial.println("New HTTP client connected");
        client.readStringUntil('\r');
        client.flush();

        String html = sendHTML(temperature, pressure, altitude);

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.println(html);
        client.println();

        delay(1);
        client.stop();
        Serial.println("HTTP client disconnected");
    }
}

void loop() {
    unsigned long now = millis();

    if (now - lastReading >= READING_INTERVAL) {
        lastReading = now;
        readAndPrintSensor();
    }

    handleClient();
}
