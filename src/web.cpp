#include "main.hpp"
#include <DHT.h>

void handle_metrics() {
    static size_t const BUFSIZE = 1024;
    static char const *response_template =
        "# HELP board_info Metadata about the device.\n"
        "# TYPE board_info gauge\n"
        "# UNIT board_info \n"
        "board_info{core_version=\"%s\",board_id=\"%x\",hash=\"%s\",sdk=\"%s\"} 1\n"

        "# HELP air_humidity_percent Air humidity.\n"
        "# TYPE air_humidity_percent gauge\n"
        "# UNIT air_humidity_percent %%\n"
        "air_humidity_percent %f\n"

        "# HELP air_temperature_celsius Air temperature.\n"
        "# TYPE air_temperature_celsius gauge\n"
        "# UNIT air_temperature_celsius \u00B0C\n"
        "air_temperature_celsius %f\n"

        "# HELP board_vcc Board voltage.\n"
        "# TYPE board_vcc gauge\n"
        "# UNIT board_vcc V\n"
        "board_vcc %f\n";

    float vcc = (float)ESP.getVcc() / 1000.0;

    static uint32_t board_id = ESP.getChipId();
    static String core_version = ESP.getCoreVersion();
    static String hash = ESP.getSketchMD5();
    static String sdk = ESP.getSdkVersion();

    if (isnan(humidity) || isnan(temp)) {
        web.send(500, "text/plain; charset=utf-8", "Sensor error.");
        return;
    }

    static char response[BUFSIZE];
    snprintf(response, BUFSIZE, response_template,
             core_version.c_str(), board_id, hash.c_str(), sdk.c_str(),
             humidity, temp, vcc);

    // web.sendHeader("Refresh", "5");
    web.send(200, "text/plain; charset=utf-8", response);
}

void handle_root() {
    web.sendHeader("Location", "/metrics");
    web.send(307, "text/plain; charset=utf-8", "");
}