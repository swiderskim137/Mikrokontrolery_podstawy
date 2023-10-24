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

  //checkSettings();
}

void checkSettings()
{
  Serial.println();

  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Clock Source:          ");
  switch (mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }

  Serial.print(" * Accelerometer:         ");
  switch (mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());

  Serial.println();
}
float x = 0, y = 0, z = 0, minx = 10000, maxx = -10000;
int sample = 100, n = 1, res = 0;
float sum = 0, sr = 0;
float odchylenie = 0, srodch = 0;

void loop()
{
  res++;
  for (int i = 1; i <= sample; i++) {
    Vector rawAccel = mpu.readRawAccel();
    //Vector normAccel = mpu.readNormalizeAccel();
    x += rawAccel.XAxis;
    y += rawAccel.YAxis;
    z += rawAccel.ZAxis;
  }
  x = x / sample;
  if (x < minx) minx = x;
  if (x > maxx) maxx = x;
  sum += x;
  sr = sum / n;
  srodch += pow(sr - x, 2);
  odchylenie = sqrt((srodch) / ((n - 1)));
  n++;
  Serial.print(" Xraw= ");
  //Serial.print(rawAccel.XAxis);
  Serial.print(x);
  //Serial.print(" ");
  //Serial.print(minx);
  //Serial.print(" ");
  //Serial.print(maxx);
  Serial.print(" m+m/2 ");
  Serial.print((maxx + minx) / 2);
  Serial.print(" sr ");
  Serial.print(sr);
  //Serial.print(" +o ");
  //Serial.print(x+odchylenie);
  //Serial.print(" -o ");
  //Serial.print(x-odchylenie);
  //Serial.print(" ");
  //Serial.print(n);


  //Serial.print(" Yraw = ");
  //Serial.print(y / sample);
  //Serial.print(rawAccel.YAxis);
  //Serial.print(" Zraw = ");
  //Serial.print(z / sample);
  //Serial.println(rawAccel.ZAxis);
  Serial.println();
  x = 0; y = 0; z = 0;
  if (res > 10){
    minx = 10000;
    maxx = -10000;
    sum = 0;
    n = 1;
    res = 0;
  }
  /*
    Serial.print(" Xnorm = ");
    Serial.print(normAccel.XAxis);
    Serial.print(" Ynorm = ");
    Serial.print(normAccel.YAxis);
    Serial.print(" Znorm = ");
    Serial.println(normAccel.ZAxis);
  */

  delay(10);
}
