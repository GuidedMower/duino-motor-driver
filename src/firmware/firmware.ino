#include <Wire.h>
#include <WireKinetis.h>

#define SHOW_UI 1

#include <DualMotor.h>

#include <Screen.h>


#define M_EN 13
#define M1SF 8
#define M1IN1 10
#define M1IN2 9
#define M2SF 20
#define M2IN1 23
#define M2IN2 22

#define SLAVE_ADDRESS 0x04 

struct MasterMessage {
  uint8_t speed;
  int16_t direction;
};

static const uint8_t SPEED_DELTA = 10;
static const MotorConfig configs[] = {{A0, M1SF, M1IN1, M1IN2}, {A1, M2SF, M2IN1, M2IN2}};
DualMotor dm(M_EN, configs);
// Motor m1({A0, M1SF, M1IN1, M1IN2});
// Motor m2({A1, M2SF, M2IN1, M2IN2});

unsigned long ui_last_millis;
unsigned long now_millis;

Screen screen;

bool BLINK_STATE = false;
bool ENABLE_STATE = LOW;


void setup() {
  
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveHandler);
  Wire.onRequest(requestHandler);
#ifdef SHOW_UI   
  uiSetup();
#endif
  dm.setDirection(0);
  dm.setSpeed(100);
  // m1.setSpeed(100);
  // m1.setDirection(2);
  // m2.setSpeed(100);
  // m2.setDirection(2);
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
  int cmd = 0;
  MasterMessage m;
  screen.pos(6, 1);
  if(Wire.available()) {
    cmd = Wire.read();
    Serial.print(cmd);
    Serial.print(">");
  }
  if (cmd == 5) { //speed + direction
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
  else if (cmd == 9) { //toggleEnable
    toggleEnable();
    dm.setRunning(ENABLE_STATE); //toggleRunning
  }
}

void requestHandler() {
  Wire.write("hello");
}

void toggleEnable() {
  ENABLE_STATE = !ENABLE_STATE;
  dm.setEnable(ENABLE_STATE);
#ifdef SHOW_UI
  screen.pos(10, 15, ENABLE_STATE);
#endif
}



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
