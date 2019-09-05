#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "ZedBoard.h"

using namespace std;

/**
* Initialize ZedBoard
**/
ZedBoard::ZedBoard() {
	 pBase = Initialize(&fd);
}

/**
* ZedBoard closes memory when program finished
**/
ZedBoard::~ZedBoard() {
	Finalize(pBase, fd);
}

/**
* Initialize general-purpose I/O
* - Opens access to physical memory /dev/mem
* - Maps memory at offset 'gpio_address' into virtual address space
*
* @param fd File descriptor passed by reference, where the result
* of function 'open' will be stored.
* @return Address to virtual memory which is mapped to physical,
* or MAP_FAILED on error.
*/
char *Initialize(int *fd)
{
        *fd = open( "/dev/mem", O_RDWR);
        return (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
        *fd, gpio_address);
}

/**
* Close general-purpose I/O.
*
* @param pBase Virtual address where I/O was mapped.
* @param fd File descriptor previously returned by 'open'.
*/
void Finalize(char *pBase, int fd)
{
        munmap(pBase, gpio_size);
        close(fd);
}


/**
* Read a 4-byte value from the specified general-purpose I/O location.
*
* @param offset Offset where device is mapped.
* @return Value read.
*/
int ZedBoard::RegisterRead(int offset)
{
	return * (int *) (pBase + offset);
}


