
struct motor {
  uint8_t fb;
  uint8_t sf;
  uint8_t d2;
  uint8_t in1;

  bool error;
  int current;
  uint8_t speed;
};

typedef struct motor Motor;


static const uint8_t M1FB = A0;
static const uint8_t M1SF = 7;
static const uint8_t M1D2 = 6;
static const uint8_t M1IN1 = 5;

static const uint8_t M2FB = A1;
static const uint8_t M2SF = 12;
static const uint8_t M2D2 = 11;
static const uint8_t M2IN1 = 10;

static const uint8_t M_EN = 8;

Motor m1;
Motor m2;


bool BLINK_STATE = false;


void setup() {
  pinMode(M_EN, OUTPUT);
  digitalWrite(M_EN, LOW);
  setup_motor(&m1, M1FB, M1SF, M1D2, M1IN1);
  setup_motor(&m2, M2FB, M2SF, M2D2, M2IN1);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
}


void setup_motor(Motor* m, uint8_t FB, uint8_t SF, uint8_t D2, uint8_t IN1) {
  m->fb = FB;
  m->sf = SF;
  m->d2 = D2;
  m->in1 = IN1;
  m->error = false;
  m->current = 0;
  m->speed = 0;
  pinMode(m->sf, INPUT);
  pinMode(m->d2, OUTPUT);
  pinMode(m->in1, OUTPUT);
  analogWrite(m->speed, m->d2); //all stop
  while(!Serial) {
    ; //wait
  }
  Serial.println("welcome");
  digitalWrite(M_EN, HIGH);
  m1.speed = 150;
  
}


void loop () {
  BLINK_STATE = !BLINK_STATE;
  digitalWrite(LED_BUILTIN, BLINK_STATE);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  control_motor(&m1);
  show_motor("m1", &m1);
  
}


void show_motor(String text, Motor* m) {
  Serial.print(text);
  Serial.print("(error=");
  Serial.print(m->error);
  Serial.print(", current=");
  Serial.print(m->current);
  Serial.print(", speed=");
  Serial.print(m->speed);
  Serial.println(")");
}

void control_motor(Motor* m) {
  check_status(m);
//  if (m->error == 1 && m->speed > 0) {
//    Serial.print("Error in motor ");
//    Serial.println(m->d2);
//    m->speed = 0;
//    digitalWrite(M_EN, LOW);
//  }
  analogWrite(m->d2, m->speed);
}

void check_status(Motor* m) {
  m->current = analogRead(m->fb);
  m->error = digitalRead(m->sf);
}






