#include <Stepmot.h>

Stepmot motor;

const int buttonP1 = 8;
const int buttonP5 = 9;
const int buttonM1 = 10;
const int buttonM5 = 11;
const int buttonSpeedPlus = 7;
const int buttonSpeedMinus = 7;
//const int speedPin = A1; 
//int sensorValue = 0;

void setup() {
  //Serial.begin(9600);
  motor.init(4096, 2, 3, 4, 5);
  pinMode(buttonP1, INPUT);
  pinMode(buttonP5, INPUT);
  pinMode(buttonM1, INPUT);
  pinMode(buttonM5, INPUT);
  pinMode(buttonSpeedPlus, INPUT);
  pinMode(buttonSpeedMinus, INPUT);
  //void mot_mod(int number_of_steps);
  //void setSpeed(float time360);
  //void step(int this_step, int mod); // set position motor
  //void angle(float val); // 
  //void off();
}
int speedMot = 1;

void loop() {
  //speedMot = map(analogRead(speedPin), 0, 1023, 1, 30);
  //motor.setSpeed(speedMot);
  
  if (digitalRead(buttonP1) == HIGH) {
    motor.angle(1);
  }
  if (digitalRead(buttonP5) == HIGH) {
    motor.angle(5);
  }
  if (digitalRead(buttonM1) == HIGH) {
    motor.angle(-1);
  }
  if (digitalRead(buttonM5) == HIGH) {
    motor.angle(-5);
  }
  if (digitalRead(buttonSpeedPlus) == HIGH) {
    speedMot += 10;
    if (speedMot > 31) speedMot = 31;
    motor.setSpeed(speedMot);
  }
  if (digitalRead(buttonSpeedMinus) == HIGH) {
    speedMot -= 10;
    if (speedMot < 1) speedMot = 1;
    motor.setSpeed(speedMot);
  }
  
  //sensorValue = analogRead(sensorPin);
  //Serial.println(analogRead(speedPin));
  //Serial.println(speedMot);
  
}
