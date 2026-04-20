#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "randutils.h"

/**
 * Return the number of microseconds currently on
 * the system clock
 */
int getMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (int)tv.tv_usec;
}

RandFloat::RandFloat() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    srand(tv.tv_usec);
}

/**
 * @brief Return a random number between 0 and 1
 * 
 * @return float 
 */
#define MAX_RANGE 1000
float RandFloat::nextFloat() {
    return ((float)(rand()%MAX_RANGE))/MAX_RANGE;
}