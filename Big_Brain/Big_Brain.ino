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
int stepperPins[4] = {STEPPER1, STEPPER2, STEPPER3, STEPPER4};
int seq[8][4] = {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}};
int setpoint;

void setup() {
  pinMode(IR_A, INPUT);
  pinMode(IR_D, INPUT);
  pinMode(STEPPER1, OUTPUT);
  pinMode(STEPPER2, OUTPUT);
  pinMode(STEPPER3, OUTPUT);
  pinMode(STEPPER4, OUTPUT);
  servo.attach(2);
  Serial.begin(9600);
  setpoint = getIRA();
}

void loop() {
  //rotate until an object is present, allow pourer
  while(getIRD()){
    stepperController();
    }
    servoController();
}

int getIRA() {
  ir_analog = analogRead(IR_A);
  return ir_analog;
}
bool getIRD() {
  ir_digital = digitalRead(IR_D);
  return ir_digital;
}
void servoController(){
  servo.write(90);
  delay(250);
  servo.write(0);
  }

void stepperController() {
    for (int s = 0; s < 8; s++) {
      for (int p = 0; p < 4; p++) {
        delay(1);
        digitalWrite(stepperPins[p], seq[s][p]);
      }
    }
}
