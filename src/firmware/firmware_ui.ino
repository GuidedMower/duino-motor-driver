
#ifdef SHOW_UI

unsigned long ui_last_millis;

void setup_ui() {
  Serial.begin(38400);
  while(!Serial) {
    ; //wait
  }
  screen.init();
  Serial.setTimeout(100);

  screen.pos(1,1, "X   Motor  Enabled  Status  Current  Speed Direction");
  screen.pos(2,1, "====================================================");
  screen.pos(3, 5, "m1");
  screen.pos(4, 5, "m2");
  screen.pos(6, 5, "ALL");
  

}

void loop_ui() {
  if (now_millis - ui_last_millis > 500) {
    check_ui_inputs();
    draw_ui();
    ui_last_millis = now_millis;
  }
}

void draw_ui() {
  show_motor(3, dm.motor1);
  show_motor(4, dm.motor2);
  screen.pos(6, 12, dm.getEnable());
  screen.pos(6, 38, dm.getSpeed());
  screen.pos(6, 44, dm.getDirection());
}


void show_motor(uint8_t line, Motor *m) {
  screen.pos(line, 12, m->enabled());
  screen.pos(line, 21, m->getStatus());
  screen.pos(line, 29, m->getCurrent());
  screen.pos(line, 38, m->getSpeed());
}


void check_ui_inputs() {
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



#endif
