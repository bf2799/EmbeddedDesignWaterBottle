#include "Servo.h"
#include "Routine.h"
#include "ZedBoard.h"

#include <iostream>
#include <sys/mman.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

/**
* Takes angle and converts to pulse
**/
int degreeToPulse(int angle) {
	return angle * 10 + 600;
}

/**
* Performs routine of servos
* For each period,
* 	Sorts values of pulses low to high and which servo they belong to
*	Turns on servos
*	Sleeps for certain calculated amount of time between each pulse and turns off desired servos
*	Sleep remaining time to finish duty cycle
**/
void performRoutine(Servo servos[5], int num_periods) {

	// Run while there are still periods
	for (int period = 0; period < num_periods; period++) {

		// Read all periods from the servo files
		// Reset sorted pulse index to be 0-4
		for (int i = 0; i < 5; i++) { // 5 is length of servo arrays
			servoPulse[i] = servos[i].readPWM(period + 1);
			sortedPulseIndex[i] = i;
		}

		// Integer used to store values temporarily for sorting arrays
		int tempNum;
		int tempIndex;

		// Maximum of 4 possible loops of switches in array of 5 for sorting them
		for (int i = 0; i < 4; i++) {

			// Switch 4 numbers if applicable each loop
			// Also switch the indices in the same way
			for (int i = 0; i < 4; i++) {

				if (servoPulse[i] > servoPulse[i + 1]) {
					tempNum = servoPulse[i];
					servoPulse[i] = servoPulse[i + 1];
					servoPulse[i + 1] = tempNum;

					tempIndex = sortedPulseIndex[i];
					sortedPulseIndex[i] = sortedPulseIndex[i + 1];
					sortedPulseIndex[i + 1] = tempIndex;

				}
			}

		}

		// Turn on all servos
		for (int servo = 0; servo < 5; servo++) {
			servos[servo].on();
		}

		// Initialize microSecs already slept
		int microSecSlept = 0;


		// For every servo from minimum time to maximum time
		// 		Sleep, turn servo off
		//		Add to time slept so far
		for (int i = 0; i < 5; i++) {
			usleep(servoPulse[i] - microSecSlept);
			servos[sortedPulseIndex[i]].off();
			microSecSlept = servoPulse[i];
		}

		// Sleep for remaining period
		usleep(PERIOD_MICROSEC - microSecSlept);

	}
}

/**
*  Writes PWM routine to files for later reading
**/
void createRoutine(Servo servos[5]) {

	// 0 = Base
	// 1 = Bicep
	// 2 = Elbow
	// 3 = Wrist
	// 4 = Gripper

	// Rotate Base
	servos[0].WriteVariablePWM(65, 30, .5);
	servos[1].WriteVariablePWM(65, 65, .5);
	servos[2].WriteVariablePWM(70, 70, .5);
	servos[3].WriteVariablePWM(60, 60, .5);
	servos[4].WriteVariablePWM(10, 120, .5);

	// Move To Water Bottle
	servos[0].WriteVariablePWM(30, 30, 1);
    servos[1].WriteVariablePWM(65, 55, 1);
    servos[2].WriteVariablePWM(70, 12, 1);
    servos[3].WriteVariablePWM(60, 50, 1);
    servos[4].WriteVariablePWM(120, 120, 1);

    // Grab Water Bottle
    servos[0].WriteVariablePWM(30, 30, 1);
    servos[1].WriteVariablePWM(55, 55, 1);
    servos[2].WriteVariablePWM(12, 12, 1);
    servos[3].WriteVariablePWM(50, 50, 1);
    servos[4].WriteVariablePWM(120, 10, 1);

	// Cock Back
	servos[0].WriteVariablePWM(30, 45, 1);
    servos[1].WriteVariablePWM(55, 15, 1);
    servos[2].WriteVariablePWM(12, 170, 1);
    servos[3].WriteVariablePWM(50, 75, 1);
    servos[4].WriteVariablePWM(10, 10, 1);

	// Destroy
    servos[0].WriteVariablePWM(45, 45, .5);
    servos[1].WriteVariablePWM(15, 15, .5);
    servos[2].WriteVariablePWM(170, 50, .5);
    servos[3].WriteVariablePWM(75, 50, .5);
    servos[4].WriteVariablePWM(10, 120, .5);

    // Initial Position
    servos[0].WriteVariablePWM(45, 65, 1);
    servos[1].WriteVariablePWM(15, 65, 1);
    servos[2].WriteVariablePWM(50, 70, 1);
    servos[3].WriteVariablePWM(50, 60, 1);
    servos[4].WriteVariablePWM(80, 120, 1);

	// Rotate Base
	servos[0].WriteVariablePWM(65, 75, .5);
    servos[1].WriteVariablePWM(65, 65, .5);
    servos[2].WriteVariablePWM(70, 70, .5);
    servos[3].WriteVariablePWM(60, 60, .5);
    servos[4].WriteVariablePWM(120, 120, .5);

    // Move to Water Bottle
    servos[0].WriteVariablePWM(75, 75, 1);
    servos[1].WriteVariablePWM(65, 55, 1);
    servos[2].WriteVariablePWM(70, 25, 1);
    servos[3].WriteVariablePWM(60, 55, 1);
    servos[4].WriteVariablePWM(120, 120, 1);

    // Grab Water Bottle
    servos[0].WriteVariablePWM(75, 75, 1);
    servos[1].WriteVariablePWM(55, 55, 1);
    servos[2].WriteVariablePWM(25, 25, 1);
    servos[3].WriteVariablePWM(55, 55, 1);
    servos[4].WriteVariablePWM(120, 10, 1);

    // Cock Back
    servos[0].WriteVariablePWM(75, 70, 1);
    servos[1].WriteVariablePWM(55, 15, 1);
    servos[2].WriteVariablePWM(25, 170, 1);
    servos[3].WriteVariablePWM(55, 75, 1);
    servos[4].WriteVariablePWM(10, 10, 1);

    // Destroy
    servos[0].WriteVariablePWM(70, 70, .5);
    servos[1].WriteVariablePWM(15, 15, .5);
    servos[2].WriteVariablePWM(170, 50, .5);
    servos[3].WriteVariablePWM(75, 55, .5);
    servos[4].WriteVariablePWM(10, 120, .5);

    // Initial Position
    servos[0].WriteVariablePWM(70, 65, 1);
    servos[1].WriteVariablePWM(15, 65, 1);
    servos[2].WriteVariablePWM(50, 70, 1);
    servos[3].WriteVariablePWM(55, 60, 1);
	servos[4].WriteVariablePWM(120, 10, 1);

}

/**
* Creates short routine at initial position to keep adding to file
**/
void createInitRoutine(Servo servos[5]) {

	// Initial Position, hold for 0.1 seconds each loop
	servos[0].WriteVariablePWM(65, 65, 0.1);
	servos[1].WriteVariablePWM(65, 65, 0.1);
  	servos[2].WriteVariablePWM(70, 70, 0.1);
  	servos[3].WriteVariablePWM(60, 60, 0.1);
  	servos[4].WriteVariablePWM(10, 10, 0.1);
}

/**
 * Creates servos
 * Creates routine for servos
 * Waits for button press while holding servos
 * Performs servo routine
**/
int main() {

	// Create servos with specific port
	Servo servos[5] = {	Servo(BASE_PORT, "Base.txt"),
						Servo(BICEP_PORT, "Bicep.txt"),
						Servo(ELBOW_PORT, "Elbow.txt"),
						Servo(WRIST_PORT, "Wrist.txt"),
						Servo(GRIPPER_PORT, "Gripper.txt")};


	// Create servos with specific ports for initial position
	Servo initServos[5] = {	Servo(BASE_PORT, "BaseInit.txt"),
						Servo(BICEP_PORT, "BicepInit.txt"),
						Servo(ELBOW_PORT, "ElbowInit.txt"),
						Servo(WRIST_PORT, "WristInit.txt"),
						Servo(GRIPPER_PORT, "GripperInit.txt")};

	// Create routine for init and routine
	createRoutine(servos);
	int num_periods = 500; // Keeps track of number of periods of routine

	// Create new ZedBoard object
	ZedBoard *board = new ZedBoard();

	// Check for errors in creating
	if(board -> pBase == MAP_FAILED) {
		cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
		exit(1);
	}

	// Create short initial routine
	createInitRoutine(initServos);

	// Try the routine 3 times
	for (int tries = 1; tries <= 3; tries++) {

		// Wait for button press of center button before continuing
		while (board->RegisterRead(gpio_pbtnc_offset) == 0) {

			// Perform short initial routine until button pressed
			performRoutine(initServos, 5);
		}

		// Perform normal routine
		performRoutine(servos, num_periods);

	}


}




