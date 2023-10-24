/*
  Arduino Wireless Communication Tutorial
        Example 1 - Receiver Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Stepmot.h>

Stepmot motor;
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  motor.init(4096, 2, 3, 4, 5);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

int x;
int poz;
void loop() {
  if (radio.available()) {
    //char text[32] = "";
    radio.read(&x, sizeof(x));
    Serial.println(x);
  }
  if (x > 3000) {
    motor.angle(1);
  }
  if (x < -3000) {
    motor.angle(-1);
  }
}
