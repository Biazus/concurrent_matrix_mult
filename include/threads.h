#include "parser.h"
#include <pthread.h>
#include <time.h>

#define SETUP_ERROR 0
#define SETUP_OK 1

time_t startClock, endClock;

int setup(int nthr); 
