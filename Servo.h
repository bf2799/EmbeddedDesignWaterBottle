#ifndef SERVO_H
#define SERVO_H

#include <string>
#include <fstream>

using namespace std;

class Servo{

private:

	// File name and file descriptor only accessible to individual classes
	string fileName;
	int fd;

public:

	Servo(int portNum, string fileNm);

	~Servo();

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
	void WriteVariablePWM(int first_angle, int last_angle, double seconds);

	/**
    	* Turns servo on by writing to file directory
    	**/
    	void on();

    	/**
    	* Turns servo on by writing to file directory
    	**/
    	void off();

	/**
	* Reads next value from file
	*
	* @return nextPulse
	*		The next pulse line in the file
	**/
	int readPWM(int line);
};

/**
* Takes angle and converts to pulse
**/
int degreeToPulse(int angle);

#endif




