/*
  Arduino Wireless Communication Tutorial
      Example 1 - Transmitter Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <MPU6050_master.h>

MPU6050 mpu;

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
int x = 0, y = 0, z = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}
void loop() {
  Vector rawAccel = mpu.readRawAccel();
  x = rawAccel.XAxis;
  y = rawAccel.YAxis;
  z = rawAccel.ZAxis;
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(z);
  Serial.println("");

  //const char text[] = "Hello World";
  //radio.write(&text, sizeof(text));
  radio.write(&x, sizeof(x));
  delay(500);
}
