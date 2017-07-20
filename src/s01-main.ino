const int M1D1 = 1;
const int M1IN1 = 2;
const int M1IN2 = 2;

const int M2D1 = 2;
const int M2IN1 = 3;
const int M2IN2 = 4;




void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop () {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

