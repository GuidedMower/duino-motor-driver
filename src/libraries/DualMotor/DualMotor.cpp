
#include "Arduino.h"
#include "DualMotor.h"

DualMotor::DualMotor(uint8_t en, const MotorConfig *configs) {
    motor1 = new Motor(configs[0]);
    motor2 = new Motor(configs[1]);
    _en = en;
    _enabled = false;
    _running = false;
    _speed = 0;
    _direction = 0;
    pinMode(_en, OUTPUT);
    digitalWrite(_en, 0);
    
}

void DualMotor::setEnable(bool value) {
    digitalWrite(_en, value);
    _enabled = value;
}

bool DualMotor::getEnable() {
    return _enabled;
}

void DualMotor::loop() {
    motor1->loop();
    motor2->loop();
    // if (!motor2->getStatus() || !motor1->getStatus()) {
    //     setRunning(false);
    // }
}

void DualMotor::setRunning(bool value) {
    motor1->enable(value);
    motor2->enable(value);
    _running = value;
}

bool DualMotor::getRunning() {
    return _running;
}

void DualMotor::setDirection(int16_t value) {
    if (value == _direction) return;
    _direction = value;
    sendVector();
}

int16_t DualMotor::getDirection() {
    return _direction;
}

void DualMotor::setSpeed(int16_t value) {
    if (_speed == value) return;
    _speed = value;
    sendVector();
}

void DualMotor::sendVector() {
    int32_t base_speed = DUALMOTOR_MAX_SPEED * _speed;
    int32_t s1 = base_speed;
    int32_t s2 = base_speed;


    if (_direction < 0) {
        s1 = s1 + (DUALMOTOR_MAX_SPEED * _direction * 2); 
    }
    else if (_direction > 0) {
        s2 = s2 - (DUALMOTOR_MAX_SPEED * _direction * 2);
    }
    s1 = s1 / 1000;
    s2 = s2 / 1000;
    motor1->setSpeed(s1);
    motor2->setSpeed(s2);
}

int16_t DualMotor::getSpeed() {
    return _speed;
}

uint8_t DualMotor::getStatus() {
    uint8_t status = 0;
    if (motor1->getStatus()) {
        bitSet(status, 0);
    }
    if (motor1->enabled()) {
        bitSet(status, 1);
    }
    if (motor2->getStatus()){
        bitSet(status, 2);
    }
    if (motor1->enabled()) {
        bitSet(status, 3);
    }
    if (_enabled) {
        bitSet(status, 4);
    }
    return status;
}