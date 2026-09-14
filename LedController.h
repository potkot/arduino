#pragma once

#include <Arduino.h>
#include "ShiftRegister.h"

class LedController {
public:
  enum Color : uint8_t {
    OFF,
    RED,
    GREEN,
    BLUE
  };

  LedController(
    ShiftRegister &shiftRegister,
    uint8_t redBit,
    uint8_t greenBit,
    uint8_t blueBit);

  void begin();

  void setColor(Color color);

  void setColorFor(
    Color color,
    unsigned long durationMs);

  void off();

  void update();

private:
  ShiftRegister &shiftRegister;
  uint8_t redBit;
  uint8_t greenBit;
  uint8_t blueBit;

  bool timed = false;

  unsigned long offAt = 0;

  void writeColor(Color color);
};
