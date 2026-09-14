#include "App.h"

#include "Events.h"
#include "Config.h"

#include "ServoController.h"
#include "SoundController.h"
//#include "LedController.h"

extern ServoController servos;
extern SoundController sound;
//extern LedController led;


//Метки для автоматического открытия
namespace {
bool closeAfterOpen = false;
unsigned long closeAt = 0;
}


void processEvents() {
  Event event;

  while (getEvent(event)) {

    switch (event.type) {
      case EVENT_ACCESS_GRANTED:
        servos.open();
        closeAfterOpen = true;
        closeAt = millis() + 5000;

        break;
      case EVENT_ACCESS_DENIED:
        sound.beep(1200, BEEP_TIME);
        break;
      case EVENT_IR_MUSIC:
        sound.playMissionImpossible();
        break;
      case EVENT_IR_SERVO_OPEN:
        servos.open();
        break;
      case EVENT_IR_SERVO_CLOSE:
        servos.close();
        break;
      case EVENT_IR_SERVO_STOP:
        servos.stop();
        break;


      case EVENT_NONE:
      default:
        break;
    }
  }

  if (closeAfterOpen) {
    unsigned long now = millis();

    if ((long)(now - closeAt) >= 0) {
      servos.close();

      closeAfterOpen = false;
    }
  }
}