

#include "Arduino.h"

#ifndef Motor_h
#define Motor_h

static const unsigned int MOTOR_CURRENT_SENSE_DELAY = 500;

struct MotorConfig {
    uint8_t fb;
    uint8_t sf;
    uint8_t in1;
    uint8_t in2;
};


class Motor {
    private:
        uint8_t _pwmPin;
        bool _changed;
        uint8_t _speed;
        uint8_t _direction;
        bool _status;
        int _current;
        bool _enabled;
        unsigned long _last;
        MotorConfig _config;
    
    public:
        Motor(MotorConfig config);
        bool getStatus();
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