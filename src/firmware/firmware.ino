
#define SHOW_UI 1

#include <Motor.h>
#include <Screen.h>

static const uint8_t M_EN = 13;
static const uint8_t SPEED_DELTA = 10;

#define M1SF 8
#define M1IN1 10
#define M1IN2 9
#define M2SF 20
#define M2IN1 23
#define M2IN2 22

Motor m1(A0, M1SF, M1IN1, M1IN2);
Motor m2(A1, M2SF, M2IN1, M2IN2);

IntervalTimer uiTimer;

Motor * selectedMotor;
Screen screen;

bool BLINK_STATE = false;
bool ENABLE_STATE = LOW;


void setup() {
  pinMode(M_EN, OUTPUT);
  digitalWrite(M_EN, ENABLE_STATE);   
  uiSetup();

  uiTimer.begin(uiLoop, 5000);

  m1.setSpeed(100);
  m1.setDirection(2);
  m2.setSpeed(100);
  m2.setDirection(2);
}



void loop () {
  noInterrupts();
  m1.loop();
  m2.loop();
  interrupts();
}



#ifdef SHOW_UI

void uiSetup() {
  Serial.begin(38400);
  while(!Serial) {
    ; //wait
  }
  screen.init();
  Serial.setTimeout(100);

  screen.pos(1,1, "X   Motor  Enabled  Error  Current  Speed Direction");
  screen.pos(2,1, "=================================================");
  screen.pos(3, 5, "m1");
  screen.pos(4, 5, "m2");
  screen.pos(10, 1, "All Enabled=0");
}

void uiLoop() {
  check_ui();
  show_motor(3, m1);
  show_motor(4, m2);
}

void check_ui() {
  char c;
  if (Serial.available() > 0) {
    
    c = char(Serial.read());
    if (c == '9') {
      ENABLE_STATE = !ENABLE_STATE;
      digitalWrite(M_EN, ENABLE_STATE);
      screen.pos(10, 13, ENABLE_STATE);
    }
    else if (c == '1') {
      // m1.enable(!m1.enabled());
      selectedMotor = &m1;
      screen.pos(3, 1, ">");
      screen.pos(4, 1, " ");
    }
    else if (c == '2') {
      // m2.enable(!m2.enabled());
      selectedMotor = &m2;
      screen.pos(3, 1, " ");
      screen.pos(4, 1, ">");
    }
    else if (c == 'a') {
      selectedMotor = NULL;
      screen.pos(3, 1, " ");
      screen.pos(4, 1, " ");
    }
    else if (c == '+') {
      if (selectedMotor != NULL) {
        speed_change(selectedMotor, SPEED_DELTA);
      }
      else {
        speed_change(&m1, SPEED_DELTA);
        speed_change(&m2, SPEED_DELTA);
      }
    }
    else if (c == '-') {
      if (selectedMotor != NULL) {
        speed_change(selectedMotor, SPEED_DELTA * -1);
      }
      else {
        speed_change(&m1, SPEED_DELTA * -1);
        speed_change(&m2, SPEED_DELTA * -1);
      }
    }
    else if (c == 'd') {
      if (selectedMotor != NULL) {
        selectedMotor->flipDirection();
      }
      else {
        m1.flipDirection();
        m2.flipDirection();
      }
    }
    else if (c == ' ') {
      if (selectedMotor != NULL) {
        selectedMotor->enable(!selectedMotor->enabled());
      }
      else {
        m1.enable(!m1.enabled());
        m2.enable(!m2.enabled());
      }
    }
  }
}


void speed_change(Motor * m, uint8_t delta) {
  m->setSpeed(m->getSpeed() + delta);
}


void show_motor(uint8_t line, Motor &m) {
  
  screen.pos(line, 12, m.enabled());
  screen.pos(line, 21, m.getError());
  screen.pos(line, 28, m.getCurrent());
  screen.pos(line, 37, m.getSpeed());
  screen.pos(line, 43, m.getDirection());
}
#endif
