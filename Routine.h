#ifndef ROUTINE_H
#define ROUTINE_H

#include "Servo.h"

using namespace std;

// Ports for servos
const int BASE_PORT = 13;
const int BICEP_PORT = 10;
const int ELBOW_PORT = 11;
const int WRIST_PORT = 12;
const int GRIPPER_PORT = 0;

// Period of duty cycle in microseconds
const int PERIOD_MICROSEC = 20000;

// Arrays used throughout routine
int servoPulse[5];
int sortedPulseIndex[5];

// Reads routine and performs from file
void performRoutine();

// Writes routine to file
void createRoutine(Servo servos[5]);

// Writes initial routine to file
void createInitRoutine(Servo servos[5]);

#endif



