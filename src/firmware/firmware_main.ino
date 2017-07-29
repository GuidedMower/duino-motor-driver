unsigned long ui_last_millis;
unsigned long now_millis;

Screen screen;

bool BLINK_STATE = false;
bool ENABLE_STATE = LOW;
uint8_t current_cmd = 0;
outbound_t outbound;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveHandler);
  Wire.onRequest(requestHandler);
#ifdef SHOW_UI   
  uiSetup();
#endif
  dm.setDirection(0);
  dm.setSpeed(100);
}



void loop () {

  dm.loop();
  // m1.loop();
  // m2.loop();
  now_millis = millis();
#ifdef SHOW_UI
  if (now_millis - ui_last_millis > 500) {
    uiLoop();
    ui_last_millis = now_millis;
  }
#endif
}

void receiveHandler(int byteCount) {
  char buf[byteCount-1];

  InboundControlMessage m;
  screen.pos(6, 1);
  if(Wire.available()) {
    current_cmd = Wire.read();
    Serial.print(current_cmd);
    Serial.print(">");
  }
  outbound.cmd = current_cmd;
  if (current_cmd == 5) { //speed + direction
    while(Wire.available()) {
      Wire.readBytes(buf, sizeof(buf));
    }
    memcpy(&m, buf, sizeof(m));
    screen.pos(7,1,"speed=");
    Serial.print(m.speed);
    Serial.print(" direction=");
    Serial.print(m.direction);
    Serial.print(" factor=");
    Serial.print(dm.factor);
    Serial.print("              ");
    dm.setDirection(m.direction); 
    dm.setSpeed(m.speed);
  }
  else if (current_cmd == 9) { //toggleEnable
    toggleEnable();
    dm.setRunning(ENABLE_STATE); //toggleRunning
  }
}

void requestHandler() {
  outbound.cmd = current_cmd;
  outbound.status = dm.getStatus();
  outbound.current1 = dm.motor1->getCurrent();
  outbound.current2 = dm.motor2->getCurrent();
  Wire.write((char *)&outbound, sizeof(outbound));
  // Wire.write(outbound.current1);
  
}

void toggleEnable() {
  ENABLE_STATE = !ENABLE_STATE;
  dm.setEnable(ENABLE_STATE);
#ifdef SHOW_UI
  screen.pos(10, 15, ENABLE_STATE);
#endif
}
