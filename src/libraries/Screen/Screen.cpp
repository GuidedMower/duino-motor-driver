#include "Arduino.h"
#include "Screen.h"


Screen::Screen() {

}

void Screen::pos(uint8_t row, uint8_t col) {
    Serial.print("\e[");
    Serial.print(row);
    Serial.print(";");
    Serial.print(col);
    Serial.print("H");
}

void Screen::pos(uint8_t row, uint8_t col, String &value) {
    pos(row, col);
    Serial.print(value);
}

void Screen::pos(uint8_t row, uint8_t col, uint8_t value) {
    pos(row, col);
    Serial.print(value);
}

void Screen::pos(uint8_t row, uint8_t col, bool value) {
    pos(row, col);
    Serial.print(value);
}

void Screen::clear() {
    Serial.print("\eSP F");  // tell to use 7-bit control codes
    Serial.print("\e[?25l"); // hide cursor
    Serial.print("\e[?12l"); // disable cursor highlighting
}