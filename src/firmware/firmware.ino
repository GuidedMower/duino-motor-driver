#include <Wire.h>
#include <WireKinetis.h>
#include <DualMotor.h>
#include <Screen.h>

#define SHOW_UI 1

#define M_EN 13
#define M1SF 8
#define M1IN1 9
#define M1IN2 10
#define M2SF 20
#define M2IN1 23
#define M2IN2 22

#define SLAVE_ADDRESS 0x04 


typedef struct  {
  int16_t speed;
  int16_t direction;
} inbound_t;

typedef struct  {
  uint8_t cmd;
  uint8_t status;
  uint16_t current1;
  uint16_t current2;
} outbound_t;



static const uint8_t SPEED_DELTA = 10;
static const MotorConfig configs[] = {{A0, M1SF, M1IN1, M1IN2}, {A1, M2SF, M2IN1, M2IN2}};
DualMotor dm(M_EN, configs);


unsigned long now_millis;
unsigned long em_brake_millis;
Screen screen;

bool BLINK_STATE = false;
bool ENABLE_STATE = LOW;
uint8_t current_cmd = 0;
outbound_t outbound;


void setup() {
  setup_i2c();
  now_millis = millis();
  em_brake_millis = now_millis + 1000;
  dm.setDirection(0);
  dm.setSpeed(0);

#ifdef SHOW_UI   
  setup_ui();
#endif
}



void loop () {
  now_millis = millis();
  if (now_millis > em_brake_millis) {
    dm.setEnable(false);
  }
  dm.loop();
  // m1.loop();
  // m2.loop();
#ifdef SHOW_UI
  loop_ui();
#endif
}