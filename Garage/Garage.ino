#include "Config.h"
#include "Events.h"

#include "RfidReader.h"
#include "IrRemoteReader.h"
//#include "Buttons165.h"

#include "ServoController.h"
#include "SoundController.h"
//#include "LedController.h"

#include "App.h"

RfidReader rfid(RFID_SS_PIN, RFID_RST_PIN);
IrRemoteReader remote(IR_PIN);

SoundController sound(PIEZO_PIN, remote);
ServoController servos(SERVO1_PIN, SERVO2_PIN);


void setup() {
  Serial.begin(115200);

  rfid.begin();
  remote.begin();
  //buttons.begin();

  servos.begin();
  sound.begin();
  //led.begin();

  Serial.println(F("Controller started"));
}

void loop() {

  // Получаем события от устройств
  rfid.update();
  remote.update();
  //buttons.update();

  // Обрабатываем события
  processEvents();

  // Обновляем устройства
  servos.update();
  sound.update();
  //led.update();
}
