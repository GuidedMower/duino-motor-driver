static const uint8_t M_EN = 13;


#include <Motor.h>
#include <Screen.h>

Motor m1(A0, 7, 6, 5, 4);
Motor m2(A1, 12, 11, 10, 9);
Motor * selectedMotor;
Screen screen;

bool BLINK_STATE = false;
bool ENABLE_STATE = LOW;

int speed = 100;
int delta = 10;

void setup() {
  pinMode(M_EN, OUTPUT);
  digitalWrite(M_EN, ENABLE_STATE);
   
  
  Serial.begin(9600);
  while(!Serial) {
    ; //wait
  }
  screen.clear();
  Serial.setTimeout(100);

  screen.pos(1,1, "Motor\tEnabled\tError\tCurrent\tSpeed");
  screen.pos(2,1, "========================================");
  screen.pos(10, 1, "Enabled=0");
  m1.setSpeed(100);
  m1.setDirection(2);
  m2.setSpeed(100);
  m2.setDirection(2);
}



void loop () {
  check_ui();
  delay(1000);
  m1.setSpeed(speed);
  m2.setSpeed(speed);
  speed = speed + delta;
  
  if (speed > 240) {
    delta = -10;
    m2.flipDirection();
  }
  if (speed < 70) {
    delta = 10;
    m1.flipDirection();
  }
  m1.loop();
  m2.loop();
 
  show_motor(3, "m1", m1);
  show_motor(4, "m2", m2);
}


void check_ui() {
  int a;
  if (Serial.available() > 0) {
    a = Serial.parseInt();
    // Serial.print("keypress=");
    

    if (a == 9) {
      ENABLE_STATE = !ENABLE_STATE;
      digitalWrite(M_EN, ENABLE_STATE);
      screen.pos(10,9, ENABLE_STATE);
    }
    
    if (a == 1) {
      // m1.enable(!m1.enabled());
      selectedMotor = &m1;
      screen.pos(3, 1, ">");
      screen.pos(4, 1, " ");
    }
    if (a == 2) {
      // m2.enable(!m2.enabled());
      selectedMotor = &m2;
      screen.pos(3, 1, " ");
      screen.pos(4, 1, ">");
    }
    if (a == 5) {
      selectedMotor->enable(!selectedMotor->enabled());
    }
  }
}



void show_motor(uint8_t line, String text, Motor &m) {
  
  screen.pos(line, 2);
  Serial.print(text);
  Serial.print("\t");
  Serial.print(m.getError());
  Serial.print("\t");
  Serial.print(m.getCurrent());
  Serial.print("\t");
  Serial.print(m.getSpeed());
  Serial.print("\t");
  Serial.print(m.getDirection());
}







