#pragma once

#include <Arduino.h>
#include "IrRemoteReader.h"

class SoundController {
public:

  struct Note {
    uint16_t frequency;  //Частота
    uint16_t duration;   //Длительность
  };

  explicit SoundController(
    uint8_t pin,
    IrRemoteReader& remote);

  void begin();

  void beep(
    uint16_t frequency,
    unsigned long durationMs);

  void playMissionImpossible();

  void update();

  bool isBusy() const;

private:

  enum State : uint8_t {
    IDLE,   //ничего не играет
    BEEP,   //играет короткий сигнал
    MELODY  //играет мелодия
  };

  uint8_t pin;

  IrRemoteReader& remote;  

  State state = IDLE;

  unsigned long endAt = 0;  //Это время, когда должен закончиться одиночный

  uint8_t melodyIndex = 0;  //Это индекс текущей ноты мелодии

  unsigned long noteEndAt = 0;  //Это время окончания текущей ноты.

  static const Note melody[];

  static const uint8_t melodyLength;

  void startNote();

  void stop();
};