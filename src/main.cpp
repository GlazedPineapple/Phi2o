#include "psk.hpp"
#include "web.hpp"
#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer web(8000);

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

ADC_MODE(ADC_VCC);

// TODO: Setup config files and stuff on these with psks and all that as well as static IPs
// also setup hostnames for them? `WiFi.hostname(aHostname)`

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);

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

    web.on("/metrics", handle_metrics);
    web.on("/", handle_root);
    web.begin();

    dht.begin();

    Serial.println("Ready");
}

float humidity;
float temp;
bool led_on = false;

static void update_sensors() {
    humidity = dht.readHumidity();
    temp = dht.readTemperature();
}

uint32_t last_millis = 0;

void loop() {
    uint32_t current_millis = millis();

    if (current_millis > last_millis + 1000) {
        last_millis = current_millis;

        update_sensors();

        led_on = !led_on;
        digitalWrite(LED_BUILTIN, led_on);
    }
    web.handleClient();
}