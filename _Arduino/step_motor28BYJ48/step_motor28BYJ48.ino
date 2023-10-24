#include <Stepmot.h>

Stepmot motor;

int st = 0;
int i = 1;

void setup() {
  Serial.begin(9600);
  motor.init(4096, 2, 3, 4, 5);
  //for (int i = 1; i <= 1024; i++) {
  //  motor.step(i,1);
  //  delay(2);}
  //for (int i = 1; i <= 1000; i++) {
  //  motor.angle(-0.087);}
  //motor.angle(360);
  //Serial.println(motor.time_step);
  //motor.setSpeed(86164);
  //Serial.println(motor.info[1]);
  //motor.mot_mod(4096););
  //motor.setSpeed(10);
  Serial.println(motor.time_step);
  for (int i=0;i<360;i++){
    motor.angle(1);
  }
  delay(5000);
  for (int i=0;i<360;i++){
    motor.angle(-1);
  }
  //motor.angle(-360);
  //motor.angle(-90);
  delay(1000);
  //motor.mot_mod(2048);
  //motor.setSpeed(100);
  //Serial.println(motor.time_step);
  //motor.angle(-360);
  //motor.off();
}

void loop() {

}
