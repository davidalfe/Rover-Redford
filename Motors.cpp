/*
* Motors.cpp
*
*  Created on: 16 mar. 2017
*      Author: david
*/

#include <Arduino.h>
#include "PinDefinition.h"
#include "Motors.h"

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega32U4__)
#define USE_20KHZ_PWM
#endif

// constructor (doesn't do anything)
Motors::Motors()
{
}

// initialize timer1 to generate the proper PWM outputs to the motor drivers
void Motors::init2()
{
	pinMode(kpMDirLeft, OUTPUT);
	pinMode(kpMDirRight, OUTPUT);
	pinMode(kpMPwmLeft, OUTPUT);
	pinMode(kpMPwmRight, OUTPUT);

#ifdef USE_20KHZ_PWM
	// Timer 1 configuration
	// prescaler: clockI/O / 1
	// outputs enabled
	// phase-correct PWM
	// top of 400
	//
	// PWM frequency calculation
	// 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
	TCCR1A = 0b10100000;
	TCCR1B = 0b00010001;
	ICR1 = 400;
#endif
}

static void setMotorSpeed(int pinDirection, int pinPwm, int speed) {
	bool reverse = false;

	if (speed < 0) {
		speed = -speed;
		reverse = true;
	}

	if (speed > MOTORS_MAX_SPEED) speed = MOTORS_MAX_SPEED;

	analogWrite(pinPwm, map(speed, 0, MOTORS_MAX_SPEED, 0, 255));
	digitalWrite(pinDirection, reverse ? HIGH : LOW);
}

void Motors::setSpeedLeft(int speed) {
	setMotorSpeed(kpMDirLeft, kpMPwmLeft, speed);
}

void Motors::setSpeedRight(int speed) {
	setMotorSpeed(kpMDirRight, kpMPwmRight, speed);
}

void Motors::setSpeed(int speedLeft, int speedRight) {
	setSpeedLeft(speedLeft);
	setSpeedRight(speedRight);
}
