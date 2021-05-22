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

    web.on("/", handle_root);
    web.begin();

    dht.begin();

    Serial.println("Ready");
}

void loop() {
    web.handleClient();
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(1000);
    // Serial.println("penis");
}