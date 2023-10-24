/*
===========================
+++	01.08.2021 			+++
+++ SciTech    			+++
+++ N.TeCh     			+++
+++ Michał Świderski 	+++
===========================
*/
#include "Arduino.h"
#include "StepmotST.h"

// unsigned long aktualnyCzas = 0;
// unsigned long zapamietanyCzas = 0;

StepmotST::StepmotST(int steps360, int motor_pin_step, int motor_pin_dir)
{
	this->step_number = 0;	   // which step the motor is on
	this->direction = 1;	   // motor direction
	this->steps360 = steps360; // total number of steps for this motor
	this->step_to_angle = 2.0 * M_PI / steps360;
	this->steps_to_do = 0;
	this->err_step = 0;
	this->step_interval = 100;
	this->step_interval_delay = 100;
	this->step_min_interval = 100;
	this->gear = 1.0;

	// Arduino pins for the motor control connection:
	this->motor_pin_step = motor_pin_step;
	this->motor_pin_dir = motor_pin_dir;

	// setup the pins on the microcontroller:
	pinMode(this->motor_pin_step, OUTPUT);
	pinMode(this->motor_pin_dir, OUTPUT);

	// set dir
	digitalWrite(motor_pin_dir, HIGH);
}

StepmotST::StepmotST(int steps360, int motor_pin_step, int motor_pin_dir, int motor_res, int motor_pin_ms1, int motor_pin_ms2, int motor_pin_ms3)
{
	this->step_number = 0;				   // which step the motor is on
	this->direction = 1;				   // motor direction
	this->steps360 = steps360 * motor_res; // total number of steps for this motor
	this->step_to_angle = 2.0 * M_PI / steps360;
	this->steps_to_do = 0;
	this->err_step = 0;
	this->step_interval = 100;
	this->step_interval_delay = 100;
	this->step_min_interval = 100;
	this->gear = 1.0;

	// Arduino pins for the motor control connection:
	this->motor_pin_step = motor_pin_step;
	this->motor_pin_dir = motor_pin_dir;
	this->motor_pin_ms1 = motor_pin_ms1;
	this->motor_pin_ms2 = motor_pin_ms2;
	this->motor_pin_ms3 = motor_pin_ms3;

	// setup the pins on the microcontroller:
	pinMode(this->motor_pin_step, OUTPUT);
	pinMode(this->motor_pin_dir, OUTPUT);
	pinMode(this->motor_pin_ms1, OUTPUT);
	pinMode(this->motor_pin_ms2, OUTPUT);
	pinMode(this->motor_pin_ms3, OUTPUT);

	// set dir
	digitalWrite(motor_pin_dir, HIGH);

	// resolution
	setResolutionPin(motor_res);
}

void StepmotST::setResolutionPin(int motor_res)
{
	if (motor_res == 1)
	{
		digitalWrite(motor_pin_ms1, LOW);
		digitalWrite(motor_pin_ms2, LOW);
		digitalWrite(motor_pin_ms3, LOW);
	}
	else if (motor_res == 2)
	{
		digitalWrite(motor_pin_ms1, HIGH);
		digitalWrite(motor_pin_ms2, LOW);
		digitalWrite(motor_pin_ms3, LOW);
	}
	else if (motor_res == 4)
	{
		digitalWrite(motor_pin_ms1, LOW);
		digitalWrite(motor_pin_ms2, HIGH);
		digitalWrite(motor_pin_ms3, LOW);
	}
	else if (motor_res == 8)
	{
		digitalWrite(motor_pin_ms1, HIGH);
		digitalWrite(motor_pin_ms2, HIGH);
		digitalWrite(motor_pin_ms3, LOW);
	}
	else if (motor_res == 16)
	{
		digitalWrite(motor_pin_ms1, HIGH);
		digitalWrite(motor_pin_ms2, HIGH);
		digitalWrite(motor_pin_ms3, HIGH);
	}
	else
	{
		digitalWrite(motor_pin_ms1, HIGH);
		digitalWrite(motor_pin_ms2, HIGH);
		digitalWrite(motor_pin_ms3, HIGH);
	}
}

void StepmotST::setGear(double val)
{
	gear = val;
	step_to_angle = 2.0 * M_PI / steps360 / val;
}

void StepmotST::setResolution(int motor_res)
{
	setResolutionPin(motor_res);
	steps360 = steps360 * motor_res;
	step_to_angle = 2.0 * M_PI / steps360 / gear;
}

void StepmotST::setTime360(double time360)
{
	// time360 = val;
	step_interval = (time360 * 1000000) / (steps360 * gear); // the high state which is initiated by the step lasts 10 us, therefore there is some subtraction
	if (step_interval < 50)
		step_interval = 50;
}

void StepmotST::setSpeed(double val)
{
	step_interval = (1000000) / val;
	if (step_interval < 50)
		step_interval = 50;
}

void StepmotST::setTime360Delay(double time360)
{
	// time360 = val;
	step_interval_delay = (time360 * 1000000) / (steps360 * gear) - (step_real_interval + step_min_interval);
	// if (((time360 * 1000000) / (steps360 * gear)) < (step_real_interval + step_min_interval))
	if (step_interval_delay < 0)
		step_interval_delay = 0;
}

void StepmotST::setSpeedDelay(double val)
{
	step_interval_delay = (1000000) / val - (step_real_interval + step_min_interval);
	if (step_interval_delay < 0)
		step_interval_delay = 0;
}

void StepmotST::setDirection(int val)
{
	if (val >= 0)
	{
		direction = 1;
		digitalWrite(motor_pin_dir, HIGH);
	}
	else
	{
		direction = -1;
		digitalWrite(motor_pin_dir, LOW);
	}
}

void StepmotST::calculateStep(double val)
{
	num_stepf = (val / step_to_angle) + err_step; // number step in double
	num_step = (int)num_stepf;					  // number step in int
	err_step = num_stepf - num_step;
}

void StepmotST::makeAngleDelay(double val)
{
	calculateStep(val);
	setDirection(num_step);
	for (int i = 0; i < num_step * direction; i++)
	{
		oneStep(step_interval_delay);
	}
}

void StepmotST::makeStepsDelay(int n)
{
	setDirection(n);
	for (int i = 0; i < abs(n); i++)
	{
		oneStep(step_interval_delay);
	}
}

void StepmotST::addStepsToDo(int n)
{
	steps_to_do += n;
}

void StepmotST::angle(double val)
{
	calculateStep(val);
	steps_to_do += num_step;
}

void StepmotST::motorOn()
{
	if (steps_to_do != 0)
	{
		unsigned long time = micros();
		if (time - last_step_time >= step_interval)
		{
			setDirection(steps_to_do);
			oneStep();
			steps_to_do -= direction;
			last_step_time = time;
		}
	}
}

void StepmotST::motorOn(int k)
{
	if (steps_to_do != 0)
	{
		if (steps_to_do < k)
			k = steps_to_do;
		unsigned long time = micros();
		if (time - last_step_time >= step_interval)
		{
			for (int i = 0; i < k; i++)
			{
				setDirection(steps_to_do);
				oneStep();
			}
			steps_to_do -= k * direction;
			last_step_time = time;
		}
	}
}

void StepmotST::oneStep(int t)
{
	digitalWrite(motor_pin_step, HIGH);
	digitalWrite(motor_pin_step, LOW);
	delayMicroseconds(step_min_interval + t);
}

void StepmotST::oneStep()
{
	digitalWrite(motor_pin_step, HIGH);
	digitalWrite(motor_pin_step, LOW);
}

void StepmotST::testSpeed()
{
	unsigned long ts, tk;
	ts = micros();
	for (int i = 0; i < 1000; i++)
	{
		oneStep(0);
	}
	tk = micros();
	step_real_interval = (tk - ts) / 1000 - step_min_interval;
	step_min_interval = 50 - step_real_interval; // 50us min time to allow work stepmotor
	setTime360Delay(1 * gear);
	ts = micros();
	makeAngleDelay(2 * M_PI / gear);
	tk = micros();
	Serial.println(tk - ts - 1e6);
	step_real_interval = step_real_interval + ((tk - ts - 1e6) / (num_step));
	setTime360Delay(1 * gear);
	ts = micros();
	makeAngleDelay(2 * M_PI / gear);
	tk = micros();
	Serial.println(tk - ts - 1e6);
}
