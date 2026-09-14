#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

class RfidReader {
public:
  RfidReader(
    uint8_t ssPin,
    uint8_t rstPin);

  void begin();

  void update();

private:

  MFRC522 mfrc522;

  bool uidEquals(
    const byte *uid,
    byte size,
    const byte *expected,
    byte expectedSize) const;
};