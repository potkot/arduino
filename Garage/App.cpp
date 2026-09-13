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
        Serial.println("Get EVENT_ACCESS_GRANTED");

        sound.playMissionImpossible();

        servos.open();
        closeAfterOpen = true;
        closeAt = millis() + 5000;

        break;
      case EVENT_ACCESS_DENIED:
        Serial.println("Get EVENT_ACCESS_DENIED");
        sound.beep(1200, BEEP_TIME);
        break;
      case EVENT_NONE:
      default:
        Serial.println("Not found event in app");
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