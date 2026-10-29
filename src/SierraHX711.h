// SierraHX711.h - calibration helper for Sierra single-point load cells (sierra.market)
#ifndef SIERRA_HX711_H
#define SIERRA_HX711_H

#include <Arduino.h>

class SierraHX711 {
public:
  SierraHX711(uint8_t dtPin, uint8_t sckPin);
  void begin();
  void tare(int samples = 10);
  void setCalibrationFactor(float rawPerGram);
  float readGrams(int samples = 5);
  long readRaw(int samples = 5);

private:
  uint8_t _dt, _sck;
  float _factor;
  long _offset;
  long _readRawOnce();
};

#endif
