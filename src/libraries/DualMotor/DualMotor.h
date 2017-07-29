
#include "Arduino.h"
#include "Motor.h"

#ifndef DualMotor_h
#define DualMotor_h



class DualMotor {
    private:
        uint8_t _en;
        bool _enabled;
        bool _running;
        uint8_t _speed;
        int16_t _direction;


    public:
        float factor;
        Motor *motor1;
        Motor *motor2;
        DualMotor(uint8_t en, const MotorConfig *configs);
        void loop();

        void setEnable(bool value);
        bool getEnable();

        void setSpeed(uint8_t value);
        uint8_t getSpeed();

        void setDirection(int16_t value);
        int16_t getDirection();

        void setRunning(bool value);
        bool getRunning();

        uint8_t getStatus();
    
};

#endif