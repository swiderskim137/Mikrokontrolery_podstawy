/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Simple Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup()
{
  Serial.begin(115200);

  //Serial.println("Initialize MPU6050");

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // If you want, you can set accelerometer offsets
  // mpu.setAccelOffsetX();
  // mpu.setAccelOffsetY();
  // mpu.setAccelOffsetZ();
}

float x = 0, y = 0, z = 0;
int sample = 100;

void loop()
{
  for (int i = 1; i <= sample; i++) {
    Vector rawAccel = mpu.readRawAccel();
    //Vector normAccel = mpu.readNormalizeAccel();
    x += rawAccel.XAxis;
    y += rawAccel.YAxis;
    //z += rawAccel.ZAxis;
  }
  x = x / sample;
  y = y / sample;
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.println("");
  x = 0; y = 0;
  //delay(10);
}
