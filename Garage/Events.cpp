#include "Events.h"

namespace {
constexpr uint8_t QUEUE_SIZE = 12;

Event queue[QUEUE_SIZE];

uint8_t head = 0;
uint8_t tail = 0;
}

void emitEvent(EventType type) {
  uint8_t next = (head + 1) % QUEUE_SIZE;

  // Очередь заполнена
  if (next == tail) {
    return;
  }

  queue[head].type = type;

  head = next;
}

bool getEvent(Event &event) {
  if (head == tail) {
    return false;
  }

  event = queue[tail];

  tail = (tail + 1) % QUEUE_SIZE;

  return true;
}