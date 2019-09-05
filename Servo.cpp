#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Servo.h"

using namespace std;

/**
* When initialized, the text file of servo pulses  should be overwritten
* The memory space should also be allocated for the I/O
**/
Servo::Servo(int portNum, string fileNm) {

	// GPIO device files will follow the format
	// /sys/class/gpio/gpio<NR>/value
	// <NR> has to be replaced with the actual device number passed as an
	// argument to the class constructor.
	char device_name[128];
	sprintf(device_name, "/sys/class/gpio/gpio%d/value", portNum);

	// Open special device file and store file descriptor in class member.
	fd = open(device_name, O_WRONLY);
	if (fd < 0)
	{
		std::cerr << "Cannot open " << device_name <<
		" - forgot sudo? \n";
		exit(1);
	}

	// Set the servo's file name to the parameter
	fileName = fileNm;

	// Open outfile without appending and check if it exists
        ofstream outFile;
	outFile.open(fileName.c_str());
        if (!outFile) {
            cout << "Unable to open " << fileName << endl;
            exit(1);
        }

}

/**
* The file descriptor should be closed
**/
Servo::~Servo() {
	close(fd);
}

/*
* Writes 1 pulse to file per period to be read for arm later
* This pulse at each period is calculated using the periods
*
* @param first_pulse
* 	The first pulse of the servo movement
* @param last_pulse
*	The last pulse of the servo movement
* @param num_periods
* 	The number of periods it takes to run from first pulse to last pulse
*/
void Servo::WriteVariablePWM(int first_angle, int last_angle, double seconds) {

	// Create out file stream
	ofstream outFile;

	// Number of periods is the number of seconds * 50Hz (20ms period)
	int num_periods = static_cast<int>(seconds * 50);

	// Create first and last pulse from angles
	double first_pulse = degreeToPulse(first_angle);
	double last_pulse = degreeToPulse(last_angle);

        // Open outfile wih appending and check if it exists
        outFile.open(fileName.c_str(), ios_base::app);
        if (!outFile) {
            cout << "Unable to open " << fileName << endl;
            exit(1);
        }

        // The initial pulse is the first pulse
        double pulse = first_pulse;

        // Each step is the pulse change per period
        double step = (last_pulse - first_pulse) / static_cast<double>(num_periods);

        // Generate num_periods of the PWM signal
        for (int i = 0; i < num_periods; i++)
        {

            // Increase the pulse by the step each period
            pulse += step;

            // Write pulse to outfile in new line
            outFile << static_cast<int>(pulse) << endl;
	}

        // Close outfile
        outFile.close();
}

/**
* Turns servo on by writing to file directory
**/
void Servo::on() {
	write(fd, "1", 1);
}

/**
* Turns servo on by writing to file directory
**/
void Servo::off() {
	write(fd, "0", 1);
}

/**
* Reads next value from file
*
* @return nextPulse
*		The next pulse line in the file
**/
int Servo::readPWM(int line) {

	// Open servo file to read from and check if it exists
	ifstream inFile;
	inFile.open(fileName.c_str());
	if (!inFile) {
        	cout << "Unable to open " << fileName << endl;
        	exit(1);
	}

	// Get line where pulse is
	string nextPulse;
	for (int i = 0; i < line; i++) {
		getline(inFile, nextPulse);
	}

	// Convert nextPulse to an integer
	int pulseNext = 0;
	stringstream converter(nextPulse);
	converter >> pulseNext;

	return pulseNext;

}




