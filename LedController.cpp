#include "LedController.h"

LedController::LedController(
  uint8_t dataPin,
  uint8_t clockPin,
  uint8_t latchPin)
  : dataPin(dataPin),
    clockPin(clockPin),
    latchPin(latchPin) {
}

void LedController::begin() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  off();
}

void LedController::writeRegister() {

  digitalWrite(latchPin, LOW);

  Serial.print("dataPin: ");
  Serial.println(dataPin);

  Serial.print("clockPin: ");
  Serial.println(clockPin);

  Serial.print("latchPin: ");
  Serial.println(latchPin);

  shiftOut(
    dataPin,
    clockPin,
    MSBFIRST,
    registerState);

  digitalWrite(latchPin, HIGH);
}

void LedController::writeColor(Color color) {
  registerState = 0;

  switch (color) {
    case BLUE:
      registerState |= (1 << 0);  // Q0
      break;

    case RED:
      registerState |= (1 << 1);  // Q1
      break;

    case GREEN:
      registerState |= (1 << 2);  // Q2
      break;

    case OFF:
    default:
      break;
  }

  writeRegister();
}

void LedController::setColor(Color color) {
  timed = false;

  writeColor(color);
}

void LedController::setColorFor(
  Color color,
  unsigned long durationMs) {


  writeColor(color);

  timed = true;

  offAt = millis() + durationMs;
}

void LedController::off() {
  timed = false;

  writeColor(OFF);
}

void LedController::update() {
  if (!timed) {
    return;
  }

  if ((long)(millis() - offAt) >= 0) {
    off();
  }
}