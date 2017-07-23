

#include "Arduino.h"

#ifndef Motor_h
#define Motor_h

class Motor {
    private:
        uint8_t _fb;
        uint8_t _sf;
        uint8_t _d2;
        uint8_t _in1;
        uint8_t _in2;

        bool _changed;
        uint8_t _speed;
        uint8_t _direction;
        bool _error;
        int _current;
        bool _enabled;
    
    public:
        Motor(uint8_t fb, uint8_t sf, uint8_t d2, uint8_t in1, uint8_t in2);
        bool getError();
        uint8_t getSpeed();
        void setSpeed(uint8_t value);
        int getCurrent();
       
        uint8_t getDirection();
        void setDirection(uint8_t value);
        void loop();
        void flipDirection();
        void enable(bool value);
        bool enabled();


};


#endif