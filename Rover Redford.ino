#include "FSM.h"
#include "Motors.h"
#include "UltrasonicSensors.h"

// Variable definition
Motors motors;
UltrasonicSensors ultrasonicSensors;
FSM stateMachine;

// Function prototypes
void readSensors();

//The setup function is called once at startup of the sketch
void setup()
{

}

// The loop function is called in an endless loop
void loop()
{
	stateMachine.Output();
	readSensors();
	stateMachine.Transition(ultrasonicSensors);
}

void readSensors() {
	ultrasonicSensors.ReadDistances();
}