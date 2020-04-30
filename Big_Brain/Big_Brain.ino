#include <PWMServo.h>

#define IR_A 32
#define IR_D  28
#define STEPPER1 27
#define STEPPER2 26
#define STEPPER3 25
#define STEPPER4 24

PWMServo servo;
int ir_analog;
bool ir_digital;
int stepperPins[4] = {STEPPER1,STEPPER2,STEPPER3,STEPPER4};
int seq[8][4] = {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,1,1},{0,0,0,1},{1,0,0,1}};
void setup() {
  pinMode(IR_A, INPUT);
  pinMode(IR_D, INPUT);
  pinMode(STEPPER1, OUTPUT);
  pinMode(STEPPER2, OUTPUT);
  pinMode(STEPPER3, OUTPUT);
  pinMode(STEPPER4, OUTPUT);
  servo.attach(2);
  Serial.begin(9600);
}

void loop() {
  // check ir 
  // if object is present, set object state to true ,servo rotate for given time
  // check ir
  // if object is gone, back servo would dispense
  // stepper motor rotates quarter rotation
  stepperController();
  getIR();
}

void getIR(){
  ir_analog = analogRead(IR_A);
  Serial.println(ir_analog);
  ir_digital = digitalRead(IR_D);
  }

void stepperController(){
  for(int i = 0; i < 128; i++){
    for(int s = 0; s < 8; s++){
      for(int p = 0; p < 4; p++){
        delay(1);
        digitalWrite(stepperPins[p],seq[s][p]);
        }
      }
    }
  }







  
