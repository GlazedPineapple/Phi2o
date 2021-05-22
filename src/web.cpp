#include <ArduinoJson.h>
#include <DHT.h>
#include <ESP8266WebServer.h>

extern DHT dht;
extern ESP8266WebServer web;

void handle_root() {
    DynamicJsonDocument doc(1024);

    doc["humidity"] = dht.readHumidity();
    doc["temp"] = dht.readTemperature();
    doc["uptime"] = millis();
    doc["vcc"] = ESP.getVcc();
    doc["id"] = ESP.getChipId();

    String result;

    serializeJson(doc, result);

    web.sendHeader("Refresh", "5");
    web.send(200, "text/plain", result);
}