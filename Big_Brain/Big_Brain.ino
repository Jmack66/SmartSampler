#include <Servo.h>
#include <Stepper.h>
#define STEPS 32
#define FRONT_PIN 2
#define BACK_PIN 4
#define SPEED 640
#define S11 9
#define S12 10
#define S13 11
#define S14 12
#define S21 5
#define S22 6
#define S23 7
#define S24 8
#define POUR_TIME 10 //time in miliseconds

Servo nozzle;
Stepper disc(STEPS, S11, S12, S13, S14);
Stepper drop(STEPS, S21, S22, S23, S24);

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
  pinMode(FRONT_PIN,INPUT);
  pinMode(BACK_PIN,INPUT);
  sampler.startup = true;
}

void dropCup() {
  while (backSensor()) {
    Serial.println(backSensor());
    //Serial.println(frontSensor());
    drop.step(1);
  }
  Serial.println("cup dropped stopping");
  //drop.step(10);//prime the next cup
}

void rotate() {
  while (frontSensor()) {
    Serial.println("now rotating");
    disc.step(1);
  }
}

bool frontSensor(){
  return digitalRead(FRONT_PIN);
  }
bool backSensor(){
  return digitalRead(BACK_PIN);
  }
void dispense(int pour_time) {
  nozzle.write(90);
  delay(pour_time);
  nozzle.write(0);
}

void startup(bool check) {
  if (check) {
    dropCup();
    disc.step(160);
    Serial.println("priming next cup");
    delay(5000);
    dropCup();
    rotate();
    Serial.println("Startup complete");
    sampler.startup = false;
  }
}

void loop() {
  startup(sampler.startup);
  
}
