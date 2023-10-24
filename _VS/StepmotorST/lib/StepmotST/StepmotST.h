/*
===========================
+++	01.08.2021 			+++
+++ SciTech    			+++
+++ N.TeCh     			+++
+++ Micha� �widerski 	+++
===========================
*/
#ifndef StepmotST_h
#define StepmotST_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

/* A4988 pins

enable 		--|		|--	Vmot (8-35V)
MS1    		--|		|--	GND
MS2    		--|		|--	2B
MS3    		--|		|-- 2A
reset  		--|		|--	1A
sleep  		--|		|-- 1B
STEP   		--|		|--	VDD
DIRECTION	--|		|--	GND

Resolution
The step size is selected by the inputs MS1, MS2, MS3. Inputs MS1, MS2 and MS3 have an internal pull-down resistor (100kOm).

MS1	MS2	MS3
L	L	L	full step
H	L	L	1/2 step
L	H	L	1/4 step
H	H	L	1/8 step
H	H	H 	1/16 step


the library contains two methods of engine control
1) (Delay): while it is running, the program is stopped and the motor is moving
2): one step is performed in each run of the main loop, this allows other functions to be performed during the movement, but the motor runs at maximum speed equal to the run of a single loop.
*/

class StepmotST
{
public:
  // constructors
  //++++++++++++++++++++++++++++++++++++++++++++++++
  // number_of_steps : number of steps per full turn
  // motor_pin_step	 : step pin
  // motor_pin_dir   : direction pin
  // motor_res       : setting microsteps (1,2,4,8,16)
  // motor_pin_msX   : microstep control pins
  // hardware resolution, enter the correct number of steps (number per revolution * resolution)
  StepmotST(int number_of_steps, int motor_pin_step, int motor_pin_dir);
  // resolution pins connected to the microcontroller it can be controlled in the program, the number of total steps per revolution is given
  StepmotST(int number_of_steps, int motor_pin_step, int motor_pin_dir, int motor_res, int motor_pin_ms1, int motor_pin_ms2, int motor_pin_ms3);
  //+++++++++++++++++++++++++++++++++++++++++++++++++

  // variables
  int direction;
  double gear;              // determines the size of the gear, if any
  long step_interval;       // delay between steps, in us, based on speed
  long step_interval_delay; // delay between steps, in us, based on speed
  int step_min_interval;    //[us]
  int step_real_interval;   //[us]

  // add gear
  void setGear(double val); // add gear, change step_to_angle and gear, the speeds must be set again with the command

  //
  void setResolutionPin(int motor_res); // sets the resolution by giving the signal to the appropriate MS pins
  void setResolution(int motor_res);    // //sets the resolution in program and calls to setResolutionPin

  // speed setter method:
  void setTime360(double val);      // time of full rotation (second)
  void setTime360Delay(double val); // time of full rotation (second)
  void setSpeed(double val);        // steps per second
  void setSpeedDelay(double val);   // steps per second

  //
  void setDirection(int val);

  // Delay mover method:
  // all assigned movement is performed at once
  // use delay between consecutive engine steps
  void oneStep(int t);
  void oneStep();
  void makeAngleDelay(double val); // in arc
  void makeStepsDelay(int n);

  // program continues between the steps of the engine
  // other procedures are performed in between engine steps
  void addStepsToDo(int n); // adding the number of steps to be taken, when the sign determines the direction of rotation
  void angle(double val);   // converts degrees to the number of steps to be added when the sign determines the direction of rotation
  void motorOn();           // main motion function, each motor step is performed after a certain time determined by the given speed. Maximum speed is the speed at which the main program loop is executed.
  void motorOn(int k);      // main motion function, each motor "k" step is performed after a certain time determined by the given speed. Maximum speed is the speed at which the main program loop is executed.

  //
  void calculateStep(double val); // executing function converts degrees to the number of steps
  //
  void off();
  //
  void testSpeed();

  // private:
  //
  unsigned long last_step_time;
  int num_step; // calculate step to do
  int steps_to_do;
  double num_stepf; // calculate step to do in double
  // int tot_step;             // total number of steps taken
  // double tot_stepf;   		// total number of steps taken in double
  double err_step;
  double step_to_angle; // angle value per one steps
  int steps360;         // total number of steps this motor can take
  int step_number;      // which step the motor is on

  // motor pin numbers:
  int motor_pin_step;
  int motor_pin_dir;
  int motor_pin_ms1;
  int motor_pin_ms2;
  int motor_pin_ms3;
};

double arc2deg(double val);
double deg2arc(double val);

#endif
