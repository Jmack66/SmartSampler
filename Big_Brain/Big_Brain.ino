#include <Servo.h>

#define IR_A 32
#define IR_D  28
#define STEPPER1 27
#define STEPPER2 26
#define STEPPER2 25
#define STEPPER2 24


Servo servo;

void setup() {
  pinMode(IR_A, INPUT);
  pinMode(IR_D, INPUT);
  pinMode(STEPPER1, OUTPUT);
  pinMode(STEPPER2, OUTPUT);
  pinMode(STEPPER3, OUTPUT);
  pinMode(STEPPER4, OUTPUT);
  servo.attach(2);
}

void loop() {


}
