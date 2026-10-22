#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "DHT11Sensor.h"
#include "TelemetrySensor.h"

#include <DHT.h>

DHT11Sensor::DHT11Sensor()
    : TelemetrySensor(meshtastic_TelemetrySensorType_SENSOR_UNSET, "DHT11"),
      dht(DHT11_PIN, DHT11)
{
}

bool DHT11Sensor::initDevice(TwoWire *bus, ScanI2C::FoundDevice *dev)
{
    (void)bus;
    (void)dev;

    LOG_INFO("Init sensor: DHT11 on GPIO %d", DHT11_PIN);

    dht.begin();

    status = 1;
    initialized = true;

    return true;
}

bool DHT11Sensor::getMetrics(meshtastic_Telemetry *measurement)
{
    LOG_DEBUG("DHT11 getMetrics");

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        LOG_WARN("DHT11 read failed");
        return false;
    }

    measurement->variant.environment_metrics.has_temperature = true;
    measurement->variant.environment_metrics.temperature = temperature;

    measurement->variant.environment_metrics.has_relative_humidity = true;
    measurement->variant.environment_metrics.relative_humidity = humidity;

    LOG_INFO("DHT11: temperature=%f C, humidity=%f %%", temperature, humidity);

    return true;
}

#endif