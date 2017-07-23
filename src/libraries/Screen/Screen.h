#include "Arduino.h"

#ifndef Screen_h
#define Screen_h

class Screen {
    public:
        Screen();
        void clear();
        void pos(uint8_t row, uint8_t col);
        void pos(uint8_t row, uint8_t col, String &value);
        void pos(uint8_t row, uint8_t col, uint8_t value);
        void pos(uint8_t row, uint8_t col, bool value);

};



#endif