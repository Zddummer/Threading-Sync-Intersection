/*
 * Samantha Foley
 *
 * CS 441/541 : Project 4 Part 2 Template
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
    // TODO - Write me

    /*
     * Initialize support library
     */
    support_init();

    return 0;
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


