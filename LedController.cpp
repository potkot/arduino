#include "LedController.h"

LedController::LedController(
  ShiftRegister &shiftRegister,
  uint8_t redBit,
  uint8_t greenBit,
  uint8_t blueBit)
  : shiftRegister(shiftRegister),
    redBit(redBit),
    greenBit(greenBit),
    blueBit(blueBit) {
}

void LedController::begin() {
  off();
}

void LedController::writeColor(Color color) {
  shiftRegister.setBit(redBit, false);
  shiftRegister.setBit(greenBit, false);
  shiftRegister.setBit(blueBit, false);

  switch (color) {
    case BLUE:
      shiftRegister.setBit(blueBit, true);
      break;

    case RED:
      shiftRegister.setBit(redBit, true);
      break;

    case GREEN:
      shiftRegister.setBit(greenBit, true);
      break;

    case OFF:
    default:
      break;
  }

  shiftRegister.write();
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
