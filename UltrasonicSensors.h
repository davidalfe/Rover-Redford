#pragma once

class UltrasonicSensors {
public:
	static void ReadDistances();
	static unsigned short GetFrontDistance();
	static unsigned short GetLeftDistance();
	static unsigned short GetRightDistance();

private:
	static unsigned short frontDistance;
	static unsigned short leftDistance;
	static unsigned short rightDistance;

	static unsigned short ReadDistance(unsigned long pinTrigger, unsigned long pinEcho);

	static inline void init() {
		static bool initialized = false;

		if (!initialized) {
			initialized = true;
			init2();
		}
	}

	static void init2();

};