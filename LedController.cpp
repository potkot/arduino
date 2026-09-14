#include "LedController.h"

LedController::LedController(
    uint8_t rPin,
    uint8_t gPin,
    uint8_t bPin
)
    : rPin(rPin),
      gPin(gPin),
      bPin(bPin)
{
}

void LedController::begin()
{
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);

    off();
}

void LedController::writeColor(Color color)
{
    analogWrite(
        rPin,
        color == RED ? 255 : 0
    );

    analogWrite(
        gPin,
        color == GREEN ? 255 : 0
    );

    analogWrite(
        bPin,
        color == BLUE ? 255 : 0
    );
}

void LedController::setColor(Color color)
{
    timed = false;

    writeColor(color);
}

void LedController::setColorFor(
    Color color,
    unsigned long durationMs
)
{
    writeColor(color);

    timed = true;

    offAt = millis() + durationMs;
}

void LedController::off()
{
    timed = false;

    writeColor(OFF);
}

void LedController::update()
{
    if (!timed)
    {
        return;
    }

    if ((long)(millis() - offAt) >= 0)
    {
        off();
    }
}