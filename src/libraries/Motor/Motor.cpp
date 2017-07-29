#include "Arduino.h"
#include "Motor.h"


Motor::Motor(MotorConfig config)
{
  _config = config;
  pinMode(config.sf, INPUT_PULLUP);
  pinMode(config.in1, OUTPUT);
  pinMode(config.in2, OUTPUT);
  digitalWrite(config.in1, LOW);
  digitalWrite(config.in2, LOW);
  analogWrite(config.in1, 0);
  analogWrite(config.in2, 0);

  _speed = 0;
  _direction = 1;
  _pwmPin = config.in1;
  _enabled = false;
  _status = false;
  _current = 0;
  _changed = false;
  _last = 0;
}


bool Motor::getStatus() {
  return _status;
}


int Motor::getCurrent() {
  return _current;
}


uint8_t Motor::getSpeed() {
  return _speed;
}


void Motor::setSpeed(uint8_t value) {
  if (value == _speed) {
    return; //if no change do nothing
  }
  _speed = constrain(value, 0, 255);
  if (_enabled) {
    analogWrite(_pwmPin, _speed);
  }
}


uint8_t Motor::getDirection() {
  return _direction;
}


void Motor::setDirection(uint8_t value) {
  if (value == _direction) {
    return; //if no change do nothing
  }
  bool old_enable = _enabled;
  _direction = constrain(value, 1, 2);
  enable(false); //stop first
  if (_direction == 1) {
    _pwmPin = _config.in1;
    analogWrite(_config.in2, 0);
    digitalWrite(_config.in2, LOW);
  } 
  else if (_direction == 2) {
    _pwmPin = _config.in2;
    analogWrite(_config.in1, 0);
    digitalWrite(_config.in1, LOW);
  }
  enable(old_enable);
}


void Motor::flipDirection() {
  if (_direction == 1) {
    _direction = 2;
  }
  else {
    _direction = 1;
  }
  setDirection(_direction);
}


void Motor::enable(bool value) {
  // if (value == _enabled) {
  //   return; //if no change do nothing
  // }
  _enabled = value;
  if (!_enabled) {
    analogWrite(_pwmPin, 0);
  }
  else {
    analogWrite(_pwmPin, _speed);
  }
}


bool Motor::enabled() {
  return _enabled;
}


void Motor::loop() {
  unsigned long now = millis();
  //don't read fb that often
  if (now - _last >= MOTOR_CURRENT_SENSE_DELAY) { 
    _current = analogRead(_config.fb);
    _last = now;
  }
  _status = digitalRead(_config.sf);
}
