#pragma once

#include <Arduino.h>
#include <Servo.h>

class ServoController {
public:

  ServoController(uint8_t pin1, uint8_t pin2);

  void begin();

  void open();

  void close();

  void stop();

  void update();

private:

  enum State : uint8_t {
    IDLE,     //Простаивают, не работают
    OPENING,  //Открываются
    CLOSING   //Закрываются
  };

  Servo servo1;
  Servo servo2;

  uint8_t pin1;
  uint8_t pin2;

  State state = IDLE;

  int angle = 0;

  unsigned long lastStepMs = 0;
};