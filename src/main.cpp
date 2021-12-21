#include "psk.hpp"
#include "room_name.hpp"
#include "sensors.hpp"
#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <InfluxDb.h>

#define DHTPIN 2
#define DHTTYPE DHT22

#define REFRESH_DELAY 30 // seconds

#define INFLUXDB_URL "http://tempmon.wellesleyps.org:8086"
#define INFLUXDB_DB_NAME "tempmon"

DHT dht(DHTPIN, DHTTYPE);
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);

ADC_MODE(ADC_VCC);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);

    WiFi.hostname(String("WPS-TempMon-") + String(P2O_CLOSET_NAME) + String("-Node-") + String(ESP.getChipId(), HEX));
    WiFi.setAutoReconnect(true);
    WiFi.begin(ssid, psk);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.hostname());

    dht.begin();

    Serial.println("Ready");
}

bool led_on = false;

uint32_t last_millis = 0;

void loop() {
    uint32_t current_millis = millis();

    if (current_millis > last_millis + (REFRESH_DELAY * 1000)) {
        last_millis = current_millis;

        update_sensors();

        led_on = !led_on;
        digitalWrite(LED_BUILTIN, led_on);
    }
}