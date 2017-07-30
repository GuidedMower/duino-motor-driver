void setup_i2c() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveHandler);
  Wire.onRequest(requestHandler);
}

void receiveHandler(int byteCount) {
  char buf[byteCount-1];

  inbound_t m;
  if(Wire.available()) {
    current_cmd = Wire.read();
#ifdef SHOW_UI
    screen.pos(7, 1, "i2c>cmd=");
    Serial.print(current_cmd);
#endif
  }
  outbound.cmd = current_cmd;
  if (current_cmd == 5) { //speed + direction
    em_brake_millis = now_millis + 1000;
    while(Wire.available()) {
      Wire.readBytes(buf, sizeof(buf));
    }
    memcpy(&m, buf, sizeof(m));
    dm.setDirection(m.direction); 
    dm.setSpeed(m.speed);
#ifdef SHOW_UI
    screen.pos(8,1,"i2c>speed=");
    Serial.print(m.speed);
    Serial.print(" direction=");
    Serial.print(m.direction);
    Serial.print("                   ");
#endif
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