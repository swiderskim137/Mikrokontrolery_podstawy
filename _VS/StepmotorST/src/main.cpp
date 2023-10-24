/*
===========================
+++	28.11.2022 		  	+++
+++ SciTech    			  +++
+++ N.TeCh     			  +++
+++ Michał Świderski 	+++
===========================
*/
#include <Arduino.h>
// #include <TimerOne.h>

#include "StepmotST.h"
// #include "C:\Dropbox\Projekty\Prowadzenie_teleskopu\pt\StepmotST\StepmotST.h"

StepmotST motorx(200 * 16, 2, 5);

//+++ pin enable +++
const int sheldEnable = 8;

//+++ gear +++
// double gx = 822.0 / 20;
double gx = 1.0 * 1;

//+++ time variables +++
unsigned long previousMillis = 0, dt = 0, interval = 1000;
volatile unsigned long t0, ts, tk;
volatile int n = 0;

void fun(void)
{
  // n++;
  motorx.oneStep();
  // if (n == 3205)
  // {
  //   tk = micros();
  //   t0 = ts;
  //   ts = tk;
  //   n = 0;
  // }
}

//===================================================
void setup()
{
  Serial.begin(9600);
  Serial.println("start");

  //+++ actiwate motor +++
  //++++++++++++++++++++++
  pinMode(sheldEnable, OUTPUT);
  digitalWrite(sheldEnable, HIGH);

  //+++ initialize motors +++
  //+++++++++++++++++++++++++
  motorx.setGear(gx);
  // motorx.setSpeedInterrupt(1000);
  // motorx.setTime360Interrupt(0.1);
  // erial.println(motorx.step_to_angle,10);
  motorx.testSpeed();
  Serial.println(motorx.step_real_interval);
  Serial.println(motorx.step_min_interval);
  digitalWrite(sheldEnable, LOW);
  motorx.setTime360(1);
  motorx.setTime360Delay(0.2);
  ts = micros();
  // Timer1.initialize(motorx.step_interval);
  // Timer1.attachInterrupt(fun);
  // Timer1.attachInterrupt(&motorx.oneStep(1));
}

//===================================================
int krokx = 3200;
int i = 1;
//===================================================
void loop()
{
  delay(2000);
  for (int i = 0; i < 40; i++)
  {
    motorx.makeAngleDelay(deg2arc(360));
  }

  // Timer1.initialize(motorx.step_interval);
  // motorx.setTime360Delay(0.1);
  //  motorx.setTime360Interrupt(1);
  //  t0 = micros();
  // motorx.makeAngleDelay(2*M_PI*10);
  //  dt = micros() - t0;
  //  Serial.println(dt-1e6);
  //  motorx.makeStepsInterrupt(krokx);
  //  digitalWrite(3, LOW);
  //  delay(1);
  //  digitalWrite(3, HIGH);
  //  motorx.testSpeed();
  //  Serial.println(motorx.step_interval_delay);
  //  Serial.println(motorx.step_real_interval);
  //  Serial.println(motorx.step_min_interval);
  //  Serial.println("kroki");
  //  //Serial.println(tk - t0- 1e6);
  //  i++;
}
