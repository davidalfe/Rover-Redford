#include <Arduino.h>
#include "PinDefinition.h"
#include "UltrasonicSensors.h"

#define MINIMUM_DELAY  60 // In milliseconds. Minimum delay between measurements.
#define SPEED_OF_SOUND 0.034029 // In centimeters per microsecond.

unsigned long time1, time2;
unsigned long currentTime, lastMeasured = 0;
unsigned short UltrasonicSensors::frontDistance;
unsigned short UltrasonicSensors::leftDistance;
unsigned short UltrasonicSensors::rightDistance;

void UltrasonicSensors::init2() {
	pinMode(kpUEchFront, INPUT);
	pinMode(kpUTrgFront, OUTPUT);
	pinMode(kpUEchLeft, INPUT);
	pinMode(kpUTrgLeft, OUTPUT);
	pinMode(kpUEchRight, INPUT);
	pinMode(kpUTrgRight, OUTPUT);
}

// Accoording to the datasheet there is a minimum separation between measurements of 60ms.
void WaitUntilReady() {
	currentTime = millis();

	if (currentTime - lastMeasured < MINIMUM_DELAY) {
		delay(currentTime - lastMeasured);
	}
}

void UltrasonicSensors::ReadDistances() {
	WaitUntilReady();
	UltrasonicSensors::frontDistance = ReadDistance(kpUTrgFront, kpUEchFront);
	UltrasonicSensors::leftDistance = ReadDistance(kpUTrgLeft,  kpUEchLeft);
	UltrasonicSensors::rightDistance = ReadDistance(kpUTrgRight, kpUEchRight);
	lastMeasured = millis();
}

unsigned short UltrasonicSensors::ReadDistance(unsigned long pinTrigger, unsigned long pinEcho) {
	// According to the data sheet, it is needed to have a HIGH signal in the trigger during 10uS.
	// for generating a ultrasonic burst. Then it is needed to wait until the echo signal goes
	// HIGH and measure the echo pulse width. With its length and the speed of sound it is possible
	// to calculate the distance.

	// TODO:  As an improvement, at least a termistor should be added for compensating the speed of
	// sound with the current temperature. If an even higher precision is needed, humidity should also
	// be measured.
	digitalWrite(pinTrigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(pinTrigger, LOW);

	while (digitalRead(pinEcho) == 0);

	time1 = micros();
	while (digitalRead(pinEcho) == 1);
	time2 = micros();

	// The speed of sound is divided by two since the distance is measured twice (go and return).
	return (time2 - time1) * (SPEED_OF_SOUND / 2);
}

unsigned short UltrasonicSensors::GetFrontDistance() {
	return frontDistance;
}

unsigned short UltrasonicSensors::GetLeftDistance() {
	return leftDistance;
}

unsigned short UltrasonicSensors::GetRightDistance() {
	return rightDistance;
}