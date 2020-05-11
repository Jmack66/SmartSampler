#include <Servo.h>
#include <Stepper.h>
#define STEPS 513
#define FRONT_PIN 3
#define BACK_PIN 3
#define SPEED 30
#define S11 27
#define S12 26
#define S13 25
#define S14 24
#define S21 27
#define S22 26
#define S23 25
#define S24 24
#define POUR_TIME 10 //time in miliseconds

Servo nozzle;
Stepper disc(STEPS, S11, S12, S13, S14);
Stepper drop(STEPS, S21, S22, S23, S24);



class Infrared {
  private:
    bool ir_d;
    int pin;
  public:
    Infrared(int pin){
      this->pin = pin;
      pinMode(pin,INPUT); 
      }

    bool getIR() {
      ir_d = digitalRead(pin);
      return ir_d;
    }
};
Infrared frontSensor = Infrared(FRONT_PIN);
Infrared backSensor = Infrared(BACK_PIN);
struct state {
  bool drop = false;
  bool rotate = false;
  bool collect = false;
  bool pour = false;
  bool error = false;
  bool startup = false;

} sampler;
void setup() {
  nozzle.attach(2);
  nozzle.write(0);
  disc.setSpeed(SPEED);
  drop.setSpeed(SPEED);
  Serial.begin(9600);
}

void dropCup() {
  while (backSensor.getIR()) {
    drop.step(5);
  }
}

void rotate() {
  while (frontSensor.getIR()) {
    disc.step(5);
  }
}
void dispense(int pour_time) {
  nozzle.write(90);
  delay(pour_time);
  nozzle.write(0);
}

void startup(bool check) {
  if (check) {
    dropCup();
    drop.step(50); //prime the next cup
    rotate();
    Serial.println("Startup complete");
    sampler.startup = false;
  }
}



void loop() {

}
