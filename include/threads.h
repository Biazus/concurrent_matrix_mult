#include "parser.h"
#include <pthread.h>
#include <time.h>

#define SETUP_ERROR 1
#define SETUP_OK 0

time_t startClock, endClock;

int setup(int nthr); 
