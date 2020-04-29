#include <Servo.h>

#define IR_A 32
#define IR_D  28
#define STEPPER1 27
#define STEPPER2 26
#define STEPPER3 25
#define STEPPER4 24

Servo servo;
int ir_analog;
bool ir_digital;

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
  // check ir 
  // if object is present, set object state to true ,servo rotate for given time
  // check ir
  // if object is gone, back servo would dispense
  // stepper motor rotates quarter rotation

}

void getIR(){
  ir_analog = analogRead(IR_A);
  ir_digital = digitalRead(IR_D);
  }

void stepperController(){
  int seq[8][4] = {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,1,1},{0,0,0,1},{1,0,0,1}};
  
  }







  
