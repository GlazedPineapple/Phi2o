#include <DHT.h>
#include <InfluxDb.h>

extern DHT dht;
extern InfluxDBClient client;

void update_sensors() {
    static Point datum("environment");

    datum.addTag("board_id", String(ESP.getChipId(), HEX));
    datum.addTag("flash_id", String(ESP.getFlashChipId(), HEX));
    datum.addTag("cpu_freq", ESP.getCpuFreqMHz() + String(" MHz"));
    datum.addTag("core_version", ESP.getCoreVersion());
    datum.addTag("hash", ESP.getSketchMD5());
    datum.addTag("sdk", ESP.getSdkVersion());

    datum.addField("vcc", (float)ESP.getVcc() / 1000.0);

    static float humidity = dht.readHumidity();
    static float temp = dht.readTemperature();

    datum.addTag("dht_status", isnan(humidity) || isnan(temp) ? "disconnected" : "connected");
    datum.addField("humidity", humidity);
    datum.addField("temp", temp);
}