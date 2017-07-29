#include "Arduino.h"

#ifndef Screen_h
#define Screen_h

class Screen {
    public:
        Screen();
        void init();
        void clear();
        void pos(uint8_t row, uint8_t col);
        void pos(uint8_t row, uint8_t col, const String &value);
        void pos(uint8_t row, uint8_t col, const char str[]);
        void pos(uint8_t row, uint8_t col, char c);
        void pos(uint8_t row, uint8_t col, const uint8_t value);
        void pos(uint8_t row, uint8_t col, int value);
        void pos(uint8_t row, uint8_t col, const bool value);
        void pos(uint8_t row, uint8_t col, int16_t value);
    
    private:

        void postPrint(size_t s, uint8_t min);

};



#endif