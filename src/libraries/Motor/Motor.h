

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
        uint8_t _pwmSpeed;
        bool _changed;
        int16_t _speed;
        bool _status;
        int _current;
        bool _enabled;
        unsigned long _last;
        MotorConfig _config;
    
    public:
        Motor(MotorConfig config);
        bool getStatus();
        int16_t getSpeed();
        void setSpeed(int16_t value);
        int getCurrent();
        void loop();
        void enable(bool value);
        bool enabled();
};


#endif