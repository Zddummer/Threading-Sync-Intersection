/*
 * This program is a simulation of a four way intersection which uses threading
 * and syncronization to decrease traffic. If only real life could be this good.
 *
 * Zach Dummer
 *
 * CS 441/541 : Synchronization Project
 *
 */
#include "stoplight.h"

/*
 * Starting point for the program
 */
int main(int argc, char * argv[]) {
    int ret;

    /*
     * Parse Command Line arguments
     */
    if( 0 != (ret = parse_args(argc, argv)) ) {
        return -1;
    }

    printArgs();
    init();

    /*
     * Initialize:
     * - random number generator
     */
    srand(time(NULL));

    /*
     * Create Car Thread(s)
     * 
     */
    pthread_t arrThreads[num_cars];
    int intReturnCode;
    int index;

    for(index = 0; index < num_cars; index++)
    {
        intReturnCode = pthread_create(&arrThreads[index], NULL, start_car, (void *)(intptr_t)index);

        if(0 != intReturnCode)
        {
            printf("ERROR when creating thread!\n");
            exit(-1);
        }
    }

    /*
     * Wait for the TTL to expire
     */
    // sleep specified amount of time
    // set time_to_exit to TRUE
    sleep(ttl);
    time_to_exit = TRUE;

    /*
     * Reap threads
     */
    for(index = 0; index < num_cars; index++)
    {
        pthread_join(arrThreads[index], (void*)0);
    }

    /*
     * Print timing information
     */
    print_footer();

    printf("Min.  Time :%12.3f msec\n", g_dblMinTime * TIME_MSEC);
    printf("Avg.  Time :%12.3f msec\n", (g_dblTotalTime / g_intNumPasses) * TIME_MSEC);
    printf("Max.  Time :%12.3f msec\n", g_dblMaxTime * TIME_MSEC);
    printf("Total Time :%12.3f msec\n", g_dblTotalTime * TIME_MSEC);

    print_footer();

    /*
     * Finalize support library
     */
    support_finalize();

    return 0;
}

/*
 * Validate for arguments passed in throught the CLI
 */
int parse_args(int argc, char **argv)
{

    /*
     * Checks if the arguments are numbers
     */
    if( argc != 3 || !isNumber(argv[1]) || !isNumber(argv[2]))
    {
    	printf("ERROR: Please supply two arguments\n");
    	printf("\t- <integer> (greater than zero) : Time in seconds the program should run for.\n");
    	printf("\t- <integer> (greater than zero) : Number of cars in simulation.\n");

    	return -1;
    }

    /*
     * Set global variable
     */
    ttl = atoi(argv[1]);
    num_cars = atoi(argv[2]);

    /*
     * Validate the variables
     */
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

/*
 * Print the starting state of the program
 */
void printArgs()
{
	printf("--------------------\n");
	printf("Time to live  :   %d\n", ttl);
	printf("Number of cars:   %d\n", num_cars);
	printf("--------------------\n");

	print_header();
}

/*
 * Initalize the mutex for the program
 */
void init()
{
    semaphore_create(&g_MutexNW, 1);
    semaphore_create(&g_MutexNE, 1);
    semaphore_create(&g_MutexSW, 1);
    semaphore_create(&g_MutexSE, 1);

    semaphore_create(&g_NextFromNorth, 1);
    semaphore_create(&g_NextFromSouth, 1);
    semaphore_create(&g_NextFromEast, 1);
    semaphore_create(&g_NextFromWest, 1);
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
        this_car.state = STATE_WAITING_I1;


        /*
         * Setup the car's direction, where it is headed, set its state
         */
        this_car.appr_dir = get_random_direction(DIRMAX);
        this_car.dest_dir = get_random_direction(this_car.appr_dir);

        /*
         * Mark start time for car
         */
        gettimeofday(&this_car.start_time, NULL);
        gettimeofday(&this_car.end_time, NULL);
        print_state(this_car, NULL);

        /*
         * Make sure the first car to arrive at the line goes first
         */
        switch(this_car.appr_dir)
        {
            case NORTH1 :
                semaphore_wait(&g_NextFromNorth);
                break;
            case SOUTH1 :
                semaphore_wait(&g_NextFromSouth);
                break;
            case EAST :
                semaphore_wait(&g_NextFromEast);
                break;
            case WEST :
                semaphore_wait(&g_NextFromWest);
                break;
            default :
                break;
        }

        /*
         * This car can star going through the intersection
         */
        this_car.state = STATE_APPROACH_I1;
        print_state(this_car,NULL);

        /*
         * Move the car in the direction and change its state accordingly
         */

        /* Check if turning right */
        if(this_car.appr_dir == NORTH1 && this_car.dest_dir == WEST)
        {
            semaphore_wait(&g_MutexNW);

            this_car.state = STATE_GO_RIGHT_I1;
            print_state(this_car, NULL);

            usleep(TIME_TO_CROSS);

            this_car.state = STATE_LEAVE_I1;

            semaphore_post(&g_MutexNW);
        }
        if(this_car.appr_dir == SOUTH1 && this_car.dest_dir == EAST)
        {
            semaphore_wait(&g_MutexSE);

            this_car.state = STATE_GO_RIGHT_I1;
            print_state(this_car, NULL);

            usleep(TIME_TO_CROSS);

            this_car.state = STATE_LEAVE_I1;

            semaphore_post(&g_MutexSE);
        }
        if(this_car.appr_dir == EAST && this_car.dest_dir == NORTH1)
        {
            semaphore_wait(&g_MutexNE);

            this_car.state = STATE_GO_RIGHT_I1;
            print_state(this_car, NULL);

            usleep(TIME_TO_CROSS);

            this_car.state = STATE_LEAVE_I1;

            semaphore_post(&g_MutexNE);
        }
        if(this_car.appr_dir == WEST && this_car.dest_dir == SOUTH1)
        {
            semaphore_wait(&g_MutexSW);

            this_car.state = STATE_GO_RIGHT_I1;
            print_state(this_car, NULL);
            
            usleep(TIME_TO_CROSS);

            this_car.state = STATE_LEAVE_I1;

            semaphore_post(&g_MutexSW);
        }

        /* Check if going straight */
        if(this_car.appr_dir == NORTH1 && this_car.dest_dir == SOUTH1)
        {
            semaphore_wait(&g_MutexNW);
            this_car.state = STATE_GO_STRAIGHT_I1;
            print_state(this_car, NULL);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexNW);

            semaphore_wait(&g_MutexSW);
            usleep(TIME_TO_CROSS);
            this_car.state = STATE_LEAVE_I1;
            semaphore_post(&g_MutexSW);
        }
        if(this_car.appr_dir == SOUTH1 && this_car.dest_dir == NORTH1)
        {
            semaphore_wait(&g_MutexSE);
            this_car.state = STATE_GO_STRAIGHT_I1;
            print_state(this_car, NULL);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexSE);

            semaphore_wait(&g_MutexNE);
            usleep(TIME_TO_CROSS);
            this_car.state = STATE_LEAVE_I1;
            semaphore_post(&g_MutexNE);
        }
        if(this_car.appr_dir == EAST && this_car.dest_dir == WEST)
        {
            semaphore_wait(&g_MutexNE);
            this_car.state = STATE_GO_STRAIGHT_I1;
            print_state(this_car, NULL);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexNE);
            
            semaphore_wait(&g_MutexNW);
            usleep(TIME_TO_CROSS);
            this_car.state = STATE_LEAVE_I1;
            semaphore_post(&g_MutexNW);
        }
        if(this_car.appr_dir == WEST && this_car.dest_dir == EAST)
        {
            semaphore_wait(&g_MutexSW);
            this_car.state = STATE_GO_STRAIGHT_I1;
            print_state(this_car, NULL);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexSW);

            semaphore_wait(&g_MutexSE);
            usleep(TIME_TO_CROSS);
            this_car.state = STATE_LEAVE_I1;
            semaphore_post(&g_MutexSE);
        }

        /* Check if turning left */
        if(this_car.appr_dir == NORTH1 && this_car.dest_dir == EAST)
        {
            semaphore_wait(&g_MutexNW);
            this_car.state = STATE_GO_LEFT_I1;
            print_state(this_car, NULL);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexNW);

            semaphore_wait(&g_MutexSW);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexSW);
            
            semaphore_wait(&g_MutexSE);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexSE);

            this_car.state = STATE_LEAVE_I1;

        }
        if(this_car.appr_dir == SOUTH1 && this_car.dest_dir == WEST)
        {
            semaphore_wait(&g_MutexSE);
            this_car.state = STATE_GO_LEFT_I1;
            print_state(this_car, NULL);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexSE);

            semaphore_wait(&g_MutexNE);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexNE);
            
            semaphore_wait(&g_MutexNW);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexNW);

            this_car.state = STATE_LEAVE_I1;
        }
        if(this_car.appr_dir == EAST && this_car.dest_dir == SOUTH1)
        {
            semaphore_wait(&g_MutexNE);
            this_car.state = STATE_GO_LEFT_I1;
            print_state(this_car, NULL);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexNE);

            semaphore_wait(&g_MutexNW);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexNW);
            
            semaphore_wait(&g_MutexSW);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexSW);

            this_car.state = STATE_LEAVE_I1;
        }
        if(this_car.appr_dir == WEST && this_car.dest_dir == NORTH1)
        {
            semaphore_wait(&g_MutexSW);
            this_car.state = STATE_GO_LEFT_I1;
            print_state(this_car, NULL);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexSW);

            semaphore_wait(&g_MutexSE);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexSE);
            
            semaphore_wait(&g_MutexNE);
            usleep(TIME_TO_CROSS);
            semaphore_post(&g_MutexNE);

            this_car.state = STATE_LEAVE_I1;
        }

        /*
         * Let the next car behind you go
         */
        switch(this_car.appr_dir)
        {
            case NORTH1 :
                semaphore_post(&g_NextFromNorth);
                break;
            case SOUTH1 :
                semaphore_post(&g_NextFromSouth);
                break;
            case EAST :
                semaphore_post(&g_NextFromEast);
                break;
            case WEST :
                semaphore_post(&g_NextFromWest);
                break;
            default :
                break;
        }

        /*
         * Mark leave time for car
         */

        gettimeofday(&this_car.end_time, NULL);
        print_state(this_car, NULL);

        /*
         * Save statistics about the cars travel
         */
        double dblTime = get_timeval_diff_as_double(this_car.start_time, &this_car.end_time);

        if(dblTime < g_dblMinTime)
        {
            g_dblMinTime = dblTime;
        }
        if(dblTime > g_dblMaxTime)
        {
            g_dblMaxTime = dblTime;
        }

        g_dblTotalTime += dblTime;
        g_intNumPasses++;
    }
    /*
     * All done
     */
    pthread_exit((void *) 0);

    return NULL;
}


