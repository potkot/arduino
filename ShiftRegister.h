#pragma once

#include <Arduino.h>

class ShiftRegister {
public:

  ShiftRegister(
    uint8_t dataPin,
    uint8_t clockPin,
    uint8_t latchPin);

  void begin();

  void setBit(
    uint8_t bit,
    bool state);

  void clearBit(uint8_t bit);

  void write();

private:

  uint8_t dataPin;
  uint8_t clockPin;
  uint8_t latchPin;

  uint8_t state = 0;
};