#include "Arduino.h"
#include "Screen.h"


Screen::Screen() {

}

void Screen::postPrint(size_t s, uint8_t min) {
    int i;
    if (s < min) {
        for(i = 0; i < min - s; i++) {
            Serial.print(' ');
        }
    }
}

void Screen::init() {
    Serial.print("\eSP F");  // tell to use 7-bit control codes
    Serial.print("\e[?25l"); // hide cursor
    Serial.print("\e[?12l"); // disable cursor highlighting
    clear();
}


void Screen::clear() {
    Serial.print("\e[2J\e[1;1H"); //clear from top to bottom
}


void Screen::pos(uint8_t row, uint8_t col) {
    Serial.print("\e[");
    Serial.print(row);
    Serial.print(";");
    Serial.print(col);
    Serial.print("H");
}


void Screen::pos(uint8_t row, uint8_t col, const String &value) {
    pos(row, col);
    postPrint(Serial.print(value), 4);
}


void Screen::pos(uint8_t row, uint8_t col, const char value[]) {
    pos(row, col);
    postPrint(Serial.print(value), 4);
}


void Screen::pos(uint8_t row, uint8_t col, char value) {
    pos(row, col);
    postPrint(Serial.print(value), 4);
} 


void Screen::pos(uint8_t row, uint8_t col, const uint8_t value) {
    pos(row, col);
    postPrint(Serial.print(value), 4);
}


void Screen::pos(uint8_t row, uint8_t col, int value) {
    pos(row, col);
    postPrint(Serial.print(value), 4);
}


void Screen::pos(uint8_t row, uint8_t col, const bool value) {
    pos(row, col);
    postPrint(Serial.print(value), 4);
}

