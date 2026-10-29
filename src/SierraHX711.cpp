// SierraHX711.cpp - minimal HX711 driver for Sierra single-point load cells
#include "SierraHX711.h"

SierraHX711::SierraHX711(uint8_t dtPin, uint8_t sckPin) : _dt(dtPin), _sck(sckPin), _factor(-7050.0f), _offset(0) {}

void SierraHX711::begin() {
  pinMode(_sck, OUTPUT);
  pinMode(_dt, INPUT);
  digitalWrite(_sck, LOW);
}

long SierraHX711::_readRawOnce() {
  while (digitalRead(_dt) == HIGH) delay(1);
  long value = 0;
  for (uint8_t i = 0; i < 24; i++) {
    digitalWrite(_sck, HIGH);
    delayMicroseconds(1);
    digitalWrite(_sck, LOW);
    delayMicroseconds(1);
    value = (value << 1) | (digitalRead(_dt) == HIGH ? 1 : 0);
  }
  digitalWrite(_sck, HIGH);
  delayMicroseconds(1);
  digitalWrite(_sck, LOW);
  if (value & 0x800000) value |= 0xFF000000;
  return value;
}

long SierraHX711::readRaw(int samples) {
  long sum = 0;
  for (int i = 0; i < samples; i++) sum += _readRawOnce();
  return sum / samples;
}

void SierraHX711::tare(int samples) { _offset = readRaw(samples); }

void SierraHX711::setCalibrationFactor(float rawPerGram) { _factor = rawPerGram; }

float SierraHX711::readGrams(int samples) {
  return (readRaw(samples) - _offset) / _factor;
}
