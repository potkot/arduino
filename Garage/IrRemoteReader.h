#pragma once

#include <Arduino.h>

class IrRemoteReader {
public:

  explicit IrRemoteReader(uint8_t pin);

  void begin();

  void update();

  void pause();

  void resume();

private:
  uint8_t pin;
};