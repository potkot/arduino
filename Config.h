#pragma once

#include <Arduino.h>

// RFID модуль MFRC522
constexpr uint8_t RFID_RST_PIN = 4;
constexpr uint8_t RFID_SS_PIN = 10;

// RGB светодиод
constexpr uint8_t REGISTER_DATA_PIN = 6;
constexpr uint8_t REGISTER_CLOCK_PIN = 3;
constexpr uint8_t REGISTER_LATCH_PIN = 5;

// Piezo пищалка
constexpr uint8_t PIEZO_PIN = 8;

// Сервоприводы
constexpr uint8_t SERVO1_PIN = 7;
constexpr uint8_t SERVO2_PIN = 9;

// ИК приемник
constexpr uint8_t IR_PIN = 2;

// Сдвиговый регистр 74HC165
constexpr uint8_t BUTTON_DATA_PIN = A0;
constexpr uint8_t BUTTON_CLOCK_PIN = A1;
constexpr uint8_t BUTTON_LATCH_PIN = A2;

constexpr uint8_t BUTTON_COUNT = 8;



// ИК комманды
constexpr uint8_t IR_CMD_MUSIC = 0x16;
constexpr uint8_t IR_CMD_CLOSE = 0x8;
constexpr uint8_t IR_CMD_OPEN = 0x5A;
constexpr uint8_t IR_CMD_STOP = 0x52;

// RFID карты
constexpr uint8_t ACCESS_UID[] = { 0x43, 0xFE, 0x3F, 0x38 };
constexpr uint8_t MAXIM_UID[] = { 0x34, 0xD7, 0xDF, 0xC1 };

constexpr uint8_t RFID_UID_SIZE = 4;

// Тайминги

constexpr unsigned long BUTTON_SCAN_INTERVAL = 10;
constexpr unsigned long BUTTON_DEBOUNCE_TIME = 30;

constexpr unsigned long SERVO_STEP_INTERVAL = 15;

constexpr unsigned long LED_ACCESS_TIME = 2000;
constexpr unsigned long LED_DENIED_TIME = 1000;
constexpr unsigned long LED_MAXIM_TIME = 1000;

constexpr unsigned long BEEP_TIME = 120;