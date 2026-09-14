#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(
  uint8_t dataPin,
  uint8_t clockPin,
  uint8_t latchPin)
  : dataPin(dataPin),
    clockPin(clockPin),
    latchPin(latchPin) {
}

void ShiftRegister::begin() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  state = 0;

  write();
}

void ShiftRegister::setBit(uint8_t bit, bool value) {
  if (bit > 7) {
    return;
  }

  if (value) {
    state |= (1 << bit);
  } else {
    state &= ~(1 << bit);
  }
}

void ShiftRegister::clearBit(uint8_t bit) {
  setBit(bit, false);
}

void ShiftRegister::write() {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, state);

  digitalWrite(latchPin, HIGH);
}
