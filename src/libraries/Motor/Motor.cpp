#include "Arduino.h"
#include "Motor.h"

Motor::Motor(uint8_t fb, uint8_t sf, uint8_t d2, uint8_t in1, uint8_t in2)
{
  pinMode(sf, INPUT_PULLUP);
  pinMode(d2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  analogWrite(d2, 0); //all stop
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  _sf = sf;
  _d2 = d2;
  _in1 = in1;
  _in2 = in2;
  _fb = fb;
  _speed = 0;
  _direction = 1;
  _enabled = false;
  _error = false;
  _current = 0;
  _changed = false;
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
  _speed = constrain(value, 0, 255);
  if (_enabled) {
    analogWrite(_d2, _speed);
  }
}


uint8_t Motor::getDirection() {
  return _direction;
}

void Motor::setDirection(uint8_t value) {
  _direction = constrain(value, 0, 3);
  // uint8_t speed = _speed;
  // setSpeed(0);
  digitalWrite(_in1, bitRead(_direction, 0));
  digitalWrite(_in2, bitRead(_direction, 1));
  // setSpeed(speed);
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
  _enabled = value;
  if (!_enabled) {
    analogWrite(_d2, 0);
  }
  else {
    analogWrite(_d2, _speed);
  }
}

bool Motor::enabled() {
  return _enabled;
}

void Motor::loop() {
  _current = analogRead(_fb);
  _error = digitalRead(_sf);
}