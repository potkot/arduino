#include "RfidReader.h"

#include "Config.h"
#include "Events.h"

RfidReader::RfidReader(
  uint8_t ssPin,
  uint8_t rstPin)
  : mfrc522(ssPin, rstPin) {
}

void RfidReader::begin() {
  SPI.begin();

  mfrc522.PCD_Init();

  Serial.println(F("RFID initialized"));
}

bool RfidReader::uidEquals(
  const byte *uid,
  byte size,
  const byte *expected,
  byte expectedSize) const {

  //Проверяем длинну массивов
  if (size != expectedSize) {
    return false;
  }

  //Проверяем байты uid - который пришел,  expected - ожидаемый
  for (byte i = 0; i < size; i++) {
    if (uid[i] != expected[i]) {
      return false;
    }
  }

  return true;
}

void RfidReader::update() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print(F("RFID UID: { "));

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (i > 0) {
      Serial.print(F(", "));
    }

    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print(F("0x0"));
    } else {
      Serial.print(F("0x"));
    }

    Serial.print(
      mfrc522.uid.uidByte[i],
      HEX);
  }

  Serial.println(F(" }"));

  if (uidEquals(
        mfrc522.uid.uidByte,
        mfrc522.uid.size,
        MAXIM_UID,
        sizeof(MAXIM_UID))) {
    emitEvent(EVENT_MAXIM_CARD);
  } else if (uidEquals(
               mfrc522.uid.uidByte,
               mfrc522.uid.size,
               ACCESS_UID,
               sizeof(ACCESS_UID))) {
    emitEvent(EVENT_ACCESS_GRANTED);
  } else {
    emitEvent(EVENT_ACCESS_DENIED);
  }

  mfrc522.PICC_HaltA();

  mfrc522.PCD_StopCrypto1();
}