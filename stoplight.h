/*
 * Header file for stoplight.c
 *
 * Zach Dummer
 *
 * CS 441/541 : Synchronization Project
 */
#include <stdbool.h>

#include "support.h"


/*****************************
 * Defines
 *****************************/


/*****************************
 * Structures
 *****************************/


/*****************************
 * Global Variables
 *****************************/
/*
 * Time to live (Seconds)
 */
int ttl = 0;

/*
 * Number of cars (threads) in the system
 */
int num_cars = 0;

/*
 * Indicate when for threads to stop processing and exit
 */
int time_to_exit = FALSE;

/*
 * Mutex for the individual sections in the intersection
 */
semaphore_t g_MutexNW;
semaphore_t g_MutexNE;
semaphore_t g_MutexSW;
semaphore_t g_MutexSE;

/*
 * Mutex for the approaching directions
 */
semaphore_t g_NextFromNorth;
semaphore_t g_NextFromSouth;
semaphore_t g_NextFromEast;
semaphore_t g_NextFromWest;

/*
 * Mutex to allow only 3 car in the interection
 */
semaphore_t g_MaxCars;

/*
 * Global variables for the stats
 */
double g_dblMinTime = 1000.0;
double g_dblMaxTime = 0.0;
double g_dblTotalTime = 0.0;
int g_intNumPasses = 0;

/*****************************
 * Function Declarations
 *****************************/
/*
 * Parse command line arguments
 */
int parse_args(int argc, char **argv);

/*
 * Check is a string is a number
 */
bool isNumber (const char *strToCheck);

/*
 * Prints arguments passed in
 */
void printArgs();

/*
 * Initialization for the mutex
 */
void init();

/*
 * Main thread function that picks an arbitrary direction to approach from,
 * and to travel to for each car.
 *
 * Write and comment this function
 *
 * Arguments:
 *   param = The car ID number for printing purposes
 *
 * Returns:
 *   NULL
 */
void *start_car(void *param);

