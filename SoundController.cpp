#include "SoundController.h"


const SoundController::Note
  SoundController::melody[] = {
    // Такт 1

    { 196, 260 },  // G3
    { 196, 260 },  // G3
    { 233, 170 },  // Bb3
    { 262, 170 },  // C4
    { 196, 260 },  // G3
    { 0, 60 },     // Пауза


    // Такт 2

    { 196, 260 },  // G3
    { 196, 260 },  // G3
    { 349, 170 },  // F4
    { 370, 170 },  // Fis4
    { 196, 260 },  // G3
    { 0, 60 },     // Пауза


    // Такт 3

    { 196, 260 },  // G3
    { 196, 260 },  // G3
    { 233, 170 },  // Bb3
    { 262, 170 },  // C4
    { 196, 260 },  // G3
    { 0, 60 },     // Пауза


    // Такт 4

    { 196, 260 },  // G3
    { 196, 260 },  // G3
    { 349, 170 },  // F4
    { 370, 170 },  // Fis4
    { 196, 350 },  // G3
    { 0, 100 },    // Пауза


    // Повтор мотива выше, октава выше

    { 392, 260 },  // G4
    { 392, 260 },  // G4
    { 466, 170 },  // Bb4
    { 523, 170 },  // C5
    { 392, 260 },  // G4
    { 0, 60 },     // Пауза


    { 392, 260 },  // G4
    { 392, 260 },  // G4
    { 349, 170 },  // F4
    { 370, 170 },  // Fis4
    { 392, 400 }   // G4
  };


const uint8_t
  SoundController::melodyLength = sizeof(SoundController::melody) / sizeof(SoundController::melody[0]);


SoundController::SoundController(
  uint8_t pin,
  IrRemoteReader& remote)
  : pin(pin),
    remote(remote) {
}


void SoundController::begin() {
  pinMode(pin, OUTPUT);

  noTone(pin);
}


void SoundController::beep(
  uint16_t frequency,
  unsigned long durationMs) {

  remote.pause();

  tone(pin, frequency);

  state = BEEP;

  endAt = millis() + durationMs;
}


void SoundController::playMissionImpossible() {

  melodyIndex = 0;

  state = MELODY;

  startNote();
}


void SoundController::startNote() {
  if (melodyIndex >= melodyLength) {
    stop();

    return;
  }

  remote.pause();


  if (melody[melodyIndex].frequency == 0) {
    noTone(pin);
  } else {
    tone(
      pin,
      melody[melodyIndex].frequency);
  }


  noteEndAt =
    millis()
    + melody[melodyIndex].duration;
}


void SoundController::stop() {
  noTone(pin);
  remote.resume();
  state = IDLE;
}


void SoundController::update() {
  unsigned long now = millis();


  if (state == BEEP) {
    if ((long)(now - endAt) >= 0) {
      stop();
    }

    return;
  }


  if (state == MELODY) {
    if ((long)(now - noteEndAt) >= 0) {
      melodyIndex++;


      if (melodyIndex >= melodyLength) {
        stop();
      } else {
        startNote();
      }
    }
  }
}


bool SoundController::isBusy() const {
  return state != IDLE;
}