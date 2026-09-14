#include "ServoController.h"

#include "Config.h"


ServoController::ServoController(
  uint8_t pin1,
  uint8_t pin2)
  : pin1(pin1),
    pin2(pin2) {
}


void ServoController::begin() {
}


void ServoController::open() {
  if (state == OPENING) {
    return;
  }

  servo1.attach(pin1);
  servo2.attach(pin2);

  state = OPENING;

  lastStepMs = millis();
}


void ServoController::close() {
  if (state == CLOSING) {
    return;
  }

  servo1.attach(pin1);
  servo2.attach(pin2);

  state = CLOSING;

  lastStepMs = millis();
}


void ServoController::stop() {
  servo1.write(angle);
  servo2.write(angle);

  servo1.detach();
  servo2.detach();

  state = IDLE;
}


void ServoController::update() {
  if (state == IDLE) {
    return;
  }

  unsigned long now = millis();

  if (now - lastStepMs < SERVO_STEP_INTERVAL) {
    return;
  }

  lastStepMs = now;


  if (state == OPENING) {
    if (angle < 90) {
      angle++;

      servo1.write(angle);
      servo2.write(angle);
    }

    if (angle >= 90) {
      stop();
    }
  }


  else if (state == CLOSING) {
    if (angle > 0) {
      angle--;

      servo1.write(angle);
      servo2.write(angle);
    }

    if (angle <= 0) {
      stop();
    }
  }
}