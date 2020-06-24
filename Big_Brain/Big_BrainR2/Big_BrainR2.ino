#include <SoftwareSerial.h>
#include <Servo.h>
#include <Stepper.h>
#define STEPS 32
#define FRONT_PIN 0
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
#define PUMP_PIN 2
#define POUR_TIME 1.3
#define ON_PIN 13
#define POUR_PIN 3
#define RED_PIN A0
#define GREEN_PIN A1
#define BLUE_PIN A2
#define RX_PIN 0
#define TX_PIN 1
Stepper disc(STEPS, S11, S12, S13, S14);
Stepper drop(STEPS, S21, S22, S23, S24);
SoftwareSerial bluetooth(RX_PIN, TX_PIN);
int val = 0;
int sampled = 0;
bool on_state = false;
void setup() {
  disc.setSpeed(SPEED);
  drop.setSpeed(SPEED);
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(FRONT_PIN, INPUT);
  pinMode(BACK_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(ON_PIN, INPUT);
  pinMode(POUR_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  delay(100);
  rgbLED(1, 0, 0);
  startup();
}
void dropCup() {
  while (backSensor()) {
    drop.step(-1);
  }
  genRotate(&drop, 400);
}

void rgbLED(int red, int green, int blue) {
  digitalWrite(RED_PIN, red);
  digitalWrite(BLUE_PIN, blue);
  digitalWrite(GREEN_PIN, green);
}


void rotate() {
  int steps_taken = 0;
  if (steps_taken < 511) {
    while (steps_taken <= 511) {
      disc.step(-1);
      drop.step(-1);
      steps_taken++;
    }
  }
}
void bToothWelcome() {
  Serial.println("Welcome to the Smart Sampler :) (Version 0.1.1)");
}
void bToothData(int sampled) {
  Serial.print("Sampled: ");
  Serial.println(sampled);
 
}
bool backSensor() {
  return digitalRead(BACK_PIN);
}
void dispense(float pour_time) {
  int i = 0;
  pour_time *= 1000;
  while (i <= pour_time) {
    digitalWrite(PUMP_PIN, HIGH);
    rgbLED(0, 0, 1);
    delay(1);
    i++;
  }
   //rgbLED(1, 0, 0);
  digitalWrite(PUMP_PIN, LOW);
  delay(100);
}
void genRotate(Stepper* stepper, int turns) {
  int i = 0;
  while (i <= turns) {
    stepper->step(-1);
    i++;
  }
}
void startup() {
  while (!digitalRead(ON_PIN)) {
    //wait for the on button to be pressed
  }
  on_state = true;
  bToothWelcome();
  dropCup();
  genRotate(&disc, 511);
  dropCup();
  Serial.println("Start up completed! Ready to Sample!");
}
void cycle() {
  if (digitalRead(POUR_PIN)) {
    rotate();
    delay(100);
    dispense(POUR_TIME);
    sampled++;
    bToothData(sampled);
    dropCup();
  }
}

void loop() {
  while(on_state){
  cycle();
  if(!digitalRead(ON_PIN)){
    on_state = false;
    }
  }
}
