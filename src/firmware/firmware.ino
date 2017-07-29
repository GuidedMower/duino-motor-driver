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


// template< typename T >
//  union Serialize{
//    T data;
//    uint8_t bytes[ sizeof( T ) ];
   
//    const uint8_t *begin(){ return bytes; }
//    const uint8_t *end(){ return bytes + sizeof( T ); }
// };


typedef struct  {
  uint8_t speed;
  int16_t direction;
} InboundControlMessage;

typedef struct  {
  uint8_t cmd;
  uint8_t status;
  uint16_t current1;
  uint16_t current2;
} outbound_t;


// typedef Serialize< outbound_t > outboundframe_t;



static const uint8_t SPEED_DELTA = 10;
static const MotorConfig configs[] = {{A0, M1SF, M1IN1, M1IN2}, {A1, M2SF, M2IN1, M2IN2}};
DualMotor dm(M_EN, configs);
// Motor m1({A0, M1SF, M1IN1, M1IN2});
// Motor m2({A1, M2SF, M2IN1, M2IN2});


