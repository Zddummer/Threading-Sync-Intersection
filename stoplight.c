/*
 * Zach Dummer
 *
 * CS 441/541 : Synchronization Project
 *
 */
#include "stoplight.h"


int main(int argc, char * argv[]) {
    int ret;

    /*
     * Parse Command Line arguments
     */
    if( 0 != (ret = parse_args(argc, argv)) ) {
        return -1;
    }

    printArgs();

    /*
     * Initialize:
     * - random number generator
     */
    srand(time(NULL));

    /*
     * Create Car Thread(s)
     * 
     */


    /*
     * Wait for the TTL to expire
     */
    // sleep specified amount of time
    // set time_to_exit to TRUE

    /*
     * Reap threads
     */


    /*
     * Print timing information
     */


    /*
     * Cleanup
     * 
     */


    /*
     * Finalize support library
     */
    support_finalize();

    return 0;
}

int parse_args(int argc, char **argv)
{
    if( argc != 3 || !isNumber(argv[1]) || !isNumber(argv[2]))
    {
    	printf("ERROR: Please supply two arguments\n");
    	printf("\t- <integer> (greater than zero) : Time in seconds the program should run for.\n");
    	printf("\t- <integer> (greater than zero) : Number of cars in simulation.\n");

    	return -1;
    }

    ttl = atoi(argv[1]);
    num_cars = atoi(argv[2]);

    if( ttl < 1 || num_cars < 1)
    {
    	printf("ERROR: Please supply two arguments\n");
    	printf("\t- <integer> (greater than zero) : Time in seconds the program should run for.\n");
    	printf("\t- <integer> (greater than zero) : Number of cars in simulation.\n");

    	return -1;
    }

    /*
     * Initialize support library
     */
    support_init();

    return 0;
}

/*
* Checks the string passed in can be converted to a number
*/
bool isNumber (const char *strToCheck) { 
    while (*strToCheck) { 
		if (*strToCheck < '0' || *strToCheck > '9')
		{
			return 0;
		} 
		strToCheck++; 
    } 
    return 1; 
}

void printArgs()
{
	printf("--------------------\n");
	printf("Time to live  :   %d\n", ttl);
	printf("Number of cars:   %d\n", num_cars);
	printf("--------------------\n");

	print_header();
}

/*
 * Approach intersection
 * param = Car Number (car_id)
 */
void *start_car(void *param) {
    int car_id = (intptr_t)param;
    car_t this_car;
    this_car.car_id = car_id;

    /*
     * Keep cycling through
     */
    while( time_to_exit == FALSE ) {

        /*
         * Sleep for a bounded random amount of time before approaching the
         * intersection
         */
        usleep(random()%TIME_TO_APPROACH);


        /*
         * Setup the car's direction, where it is headed, set its state
         */


        /*
         * Mark start time for car
         */
        gettimeofday(&this_car.start_time, NULL);
        gettimeofday(&this_car.end_time, NULL);
        print_state(this_car, NULL);

        /*
         * Move the car in the direction and change its state accordingly
         */


        /*
         * Mark leave time for car
         */

        gettimeofday(&this_car.end_time, NULL);
        print_state(this_car, NULL);

        /*
         * Save statistics about the cars travel
         */

    }

    /*
     * All done
     */
    pthread_exit((void *) 0);

    return NULL;
}


