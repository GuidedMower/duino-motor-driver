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
  _pwmPin = config.in1;
  _pwmSpeed = 0;
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


int16_t Motor::getSpeed() {
  return _speed;
}


void Motor::setSpeed(int16_t value) {
  if (value == _speed) {
    return; //if no change do nothing
  }
  _speed = constrain(value, -255, 255);

  if (_speed > 0) {
    _pwmPin = _config.in1;
    _pwmSpeed = _speed;
    analogWrite(_config.in2, 0);
    digitalWrite(_config.in2, LOW);
  }
  else if (_speed < 0) {
    _pwmPin = _config.in2;
    _pwmSpeed = _speed * -1;
    analogWrite(_config.in1, 0);
    digitalWrite(_config.in1, LOW);
  }
  else {
    _pwmSpeed = 0;
  }

  if (_enabled) {
    analogWrite(_pwmPin, _pwmSpeed);
  }
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
