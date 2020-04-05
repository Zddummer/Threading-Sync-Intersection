/*
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


/*****************************
 * Function Declarations
 *****************************/
/*
 * Parse command line arguments
 */
int parse_args(int argc, char **argv);

bool isNumber (const char *strToCheck);

void printArgs();

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

