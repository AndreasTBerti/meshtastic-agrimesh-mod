#pragma once

#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "TelemetrySensor.h"
#include <DHT.h>

#ifndef DHT11_PIN
#define DHT11_PIN 6
#endif

class DHT11Sensor : public TelemetrySensor
{
  private:
    DHT dht;

  public:
    DHT11Sensor();

    virtual bool getMetrics(meshtastic_Telemetry *measurement) override;

    virtual bool initDevice(TwoWire *bus, ScanI2C::FoundDevice *dev) override;
};

#endif