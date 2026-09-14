#pragma once

#include <Arduino.h>

class LedController {
public:

  enum Color : uint8_t {
    OFF,
    RED,
    GREEN,
    BLUE
  };

  LedController(
    uint8_t dataPin,
    uint8_t clockPin,
    uint8_t latchPin);

  void begin();

  void setColor(Color color);

  void setColorFor(
    Color color,
    unsigned long durationMs);

  void off();

  void update();

private:

  uint8_t dataPin;
  uint8_t clockPin;
  uint8_t latchPin;

  uint8_t registerState = 0;

  bool timed = false;

  unsigned long offAt = 0;

  void writeColor(Color color);
  void writeRegister();
};