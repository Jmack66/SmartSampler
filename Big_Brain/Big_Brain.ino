#include <Servo.h>
#define FRONT_PIN 3
#define BACK_PIN 3
#define STEPPER1 27
#define STEPPER2 26
#define STEPPER3 25
#define STEPPER4 24

Servo servo;
int ir_analog;
bool ir_digital;
int stepperPins[4] = {STEPPER1, STEPPER2, STEPPER3, STEPPER4};
int seq[8][4] = {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}};

class IR{
  private:
    int ir_d;
  public:
    int pin;
  void set(int inpin){
      pin = inpin;
      pinMode(pin, INPUT);
    }
  int getIR(){
    ir_d = digitalRead(pin);
    return ir_d;
    }
  };
struct state{
  bool drop = false;
  bool rotate = false;
  bool collect = false;
  bool pour = false;
  bool error = false; 
  bool startup = false;
  
  }sampler;
  
void setup() {
  pinMode(STEPPER1, OUTPUT);
  pinMode(STEPPER2, OUTPUT);
  pinMode(STEPPER3, OUTPUT);
  pinMode(STEPPER4, OUTPUT);
  servo.attach(2);
  IR frontSensor;
  IR backSensor;
  frontSensor.set(FRONT_PIN);
  backSensor.set(BACK_PIN);
}

void loop() {

}


//int getIRA() {
//  ir_analog = analogRead(IR_A);
//  return ir_analog;
//}
//bool getIRD() {
//  ir_digital = digitalRead(IR_D);
//  return ir_digital;
//}
//
//
//void stepperController() {
//    for (int s = 0; s < 8; s++) {
//      for (int p = 0; p < 4; p++) {
//        delay(1);
//        digitalWrite(stepperPins[p], seq[s][p]);
//      }
//    }
//}
