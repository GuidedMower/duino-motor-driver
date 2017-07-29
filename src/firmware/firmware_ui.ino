
#ifdef SHOW_UI

void uiSetup() {
  Serial.begin(38400);
  while(!Serial) {
    ; //wait
  }
  screen.init();
  Serial.setTimeout(100);

  screen.pos(1,1, "X   Motor  Enabled  Status  Current  Speed Direction");
  screen.pos(2,1, "=================================================");
  screen.pos(3, 5, "m1");
  screen.pos(4, 5, "m2");
  
  screen.pos(9, 1,  "Direction =   0");
  screen.pos(10, 1, "All Enabled = 0");


}

void uiLoop() {
  check_ui();
  show_motor(3, dm.motor1);
  show_motor(4, dm.motor2);
  screen.pos(9, 15, dm.getDirection());
}



void check_ui() {
  char c;
  if (Serial.available() > 0) {
    
    c = char(Serial.read());
    if (c == '9') {
      toggleEnable();
    }
    else if (c == 'a') {
      dm.setDirection(dm.getDirection() - 2);
    }
    else if (c == 'd') {
      dm.setDirection(dm.getDirection() + 2);
    }
    else if (c == 'w') {
      dm.setSpeed(dm.getSpeed() + SPEED_DELTA);
    }
    else if (c == 's') { 
      dm.setSpeed(dm.getSpeed() + SPEED_DELTA * -1);
    }
    else if (c == ' ') {
      dm.setRunning(!dm.getRunning());
    }
  }
}



void show_motor(uint8_t line, Motor *m) {
  
  screen.pos(line, 12, m->enabled());
  screen.pos(line, 21, m->getStatus());
  screen.pos(line, 29, m->getCurrent());
  screen.pos(line, 38, m->getSpeed());
  screen.pos(line, 44, m->getDirection());
}
#endif
