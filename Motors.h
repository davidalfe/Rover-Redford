/*
* Motors.h
*
*  Created on: 16 mar. 2017
*      Author: david
*/

#pragma once

#define MOTORS_MAX_SPEED 100

class Motors {
public:
	Motors(); // Nothing to do

	static void setSpeedLeft(int speed);
	static void setSpeedRight(int speed);
	static void setSpeed(int speedLeft, int speedRight);

private:
	static inline void init()
	{
		static boolean initialized = false;

		if (!initialized)
		{
			initialized = true;
			init2();
		}
	}

	// initializes timer1 for proper PWM generation
	static void init2();
};

