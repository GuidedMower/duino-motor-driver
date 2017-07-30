
#include "Arduino.h"
#include "Motor.h"

#ifndef DualMotor_h
#define DualMotor_h

static const int DUALMOTOR_MAX_SPEED = 255;

class DualMotor {
    private:
        uint8_t _en;
        bool _enabled;
        bool _running;
        int16_t _speed;
        int16_t _direction;
        void sendVector();


    public:
        Motor *motor1;
        Motor *motor2;
        DualMotor(uint8_t en, const MotorConfig *configs);
        void loop();

        void setEnable(bool value);
        bool getEnable();

        void setSpeed(int16_t value);
        int16_t getSpeed();

        void setDirection(int16_t value);
        int16_t getDirection();

        void setRunning(bool value);
        bool getRunning();

        uint8_t getStatus();
    
};

#endif