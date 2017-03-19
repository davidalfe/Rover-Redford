#pragma once

#include "UltrasonicSensors.h"

class FSM {
public:
	static void Output();
	static void Transition(UltrasonicSensors ultrasonicSensors);
};