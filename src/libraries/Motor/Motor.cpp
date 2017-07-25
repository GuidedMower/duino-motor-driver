#include "Arduino.h"
#include "Motor.h"


Motor::Motor(uint8_t fb, uint8_t sf, uint8_t in1, uint8_t in2)
{
  pinMode(sf, INPUT_PULLUP);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(in1, 0);
  analogWrite(in2, 0);

  _sf = sf;
  _in1 = in1;
  _in2 = in2;
  _fb = fb;
  _speed = 0;
  _direction = 1;
  _pwmPin = in1;
  _enabled = false;
  _error = false;
  _current = 0;
  _changed = false;
  _last = 0;
}


bool Motor::getError() {
  return _error;
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
    _pwmPin = _in1;
    analogWrite(_in2, 0);
    digitalWrite(_in2, LOW);
  } 
  else if (_direction == 2) {
    _pwmPin = _in2;
    analogWrite(_in1, 0);
    digitalWrite(_in1, LOW);
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
  if (now - _last >= CURRENT_SENSE_DELAY) { 
    _current = analogRead(_fb);
    _last = now;
  }
  _error = digitalRead(_sf);
}
