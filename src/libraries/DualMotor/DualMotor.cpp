
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
    if (!motor2->getStatus() || !motor1->getStatus()) {
        setRunning(false);
    }
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
    if (_direction < -254) {
        _direction = -254;
    }
    else if (_direction > 254) {
        _direction = 254;
    }
    setSpeed(getSpeed());
}

int16_t DualMotor::getDirection() {
    return _direction;
}

void DualMotor::setSpeed(uint8_t value) {
    _speed = value;
    uint8_t s1 = _speed;
    uint8_t s2 = _speed;

    if (_direction < 0) {
        factor = float(_direction) / 254.0 * - 1;
        s1 = _speed - int(factor * float(_speed));
    }
    else if (_direction > 0) {
        factor = float(_direction) / 254.0;
        s2 = _speed - int(factor * float(_speed));
    }
    motor1->setSpeed(s1);
    motor2->setSpeed(s2);
}

uint8_t DualMotor::getSpeed() {
    return _speed;
}