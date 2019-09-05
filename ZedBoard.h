#ifndef ZEDBOARD_H
#define ZEDBOARD_H

using namespace std;

// Offset for center push button
const int gpio_pbtnc_offset = 0x17C;

// Physical base of address of GPIO
const unsigned gpio_address = 0x400d0000;

// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

class ZedBoard {

public:

	// File descriptor and pBase have to be accessible for Routine.cpp
	int fd;
	char *pBase;

	ZedBoard();

	~ZedBoard();

	// Reads memory value  at specified offset
	int RegisterRead(int offset);

};

// Initialize and finalize correctly start and complete the ZedBoard operations
char *Initialize(int *fd);
void Finalize(char *pBase, int fd);

#endif


