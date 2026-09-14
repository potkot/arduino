#pragma once

#include <Arduino.h>

class LedController
{
public:

    enum Color : uint8_t
    {
        OFF,
        RED,
        GREEN,
        BLUE
    };

    LedController(
        uint8_t rPin,
        uint8_t gPin,
        uint8_t bPin
    );

    void begin();

    void setColor(Color color);

    void setColorFor(
        Color color,
        unsigned long durationMs
    );

    void off();

    void update();

private:

    uint8_t rPin;
    uint8_t gPin;
    uint8_t bPin;

    bool timed = false;

    unsigned long offAt = 0;

    void writeColor(Color color);
};