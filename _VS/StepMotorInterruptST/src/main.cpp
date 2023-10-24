/*
===========================
+++	28.11.2022 		  	+++
+++ SciTech    			  +++
+++ N.TeCh     			  +++
+++ Michał Świderski 	+++
===========================
*/
#include <Arduino.h>
#include <avr/io.h>
//#include <avr/interrupt.h>

#include "timer.h"
#include "StepmotST.h"
// #include "C:\Dropbox\Projekty\Prowadzenie_teleskopu\pt\StepmotST\StepmotST.h"

StepmotST motorx(200 * 16, 2, 5);
timer T;
//+++ pin enable +++
const int sheldEnable = 8;

//+++ gear +++
// double gx = 822.0 / 20;
double gx = 1.0 * 1;

//+++ time variables +++
unsigned long previousMillis = 0, dt = 0, interval = 1000;
volatile unsigned long t0, ts, tk;
volatile int n = 0;
volatile int period = 25; // Pulse time = 25 * 64 * 0.0625 = 100us

volatile boolean toggle4 = LOW;

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
  pinMode(13, OUTPUT);

  T.timer4(1);
  //T.timer1(1);
  // noInterrupts();
  //   TCCR1A = 0;
  //   TCCR1B = 0;
  //   TCNT1 = 0; // initialize counter value to 0

  //   TCCR1B |= (1 << WGM12);              // CTC mode
  //   TCCR1B |= (1 << CS11) | (1 << CS10); // 64 prescaler
  //   TIMSK1 |= (1 << OCIE1A);             // enable timer compare interrupt
  //   OCR1A = period - 1;
  // interrupts();

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
  motorx.setTime360(0.1);
  motorx.setTime360Delay(0.2);
  ts = micros();
}

// ISR(TIMER1_COMPA_vect)
// {
//     PORTB = 0b00000001;
//     delayMicroseconds(5);
//     PORTB = 0b00000000;
//     OCR1A = period - 1;
// }

ISR(TIMER4_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
 digitalWrite(13,toggle4);
 toggle4 = !toggle4;
 motorx.oneStep();
}

// ISR(TIMER1_COMPA_vect)
// {
//   digitalWrite(13, toggle4);
//   toggle4 = !toggle4;
// }

// ISR(TIMER1_COMPB_vect)
// {
//   digitalWrite(13, toggle4);
//   toggle4 = !toggle4;
// }

//===================================================
int krokx = 3200;
int i = 1;
//===================================================
void loop()
{
  //delay(1000);
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
  // Serial.println(motorx.step_interval_delay);
  // Serial.println(motorx.step_real_interval);
  // Serial.println(motorx.step_min_interval);
  //Serial.println("kroki");
  // Serial.println(tk - t0- 1e6);
  //i++;
}
