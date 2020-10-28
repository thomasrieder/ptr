#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <inttypes.h>

#define WAIT_SEC    1
#define WAIT_USEC   0

int main(void) {

    struct timespec waitInt;

    waitInt.tv_nsec = WAIT_USEC;
    waitInt.tv_sec = WAIT_SEC;

    struct timeval start_time;
    struct timeval end_time;
    struct timeval diff;

    for(int i = 0; i < 30; i++) {

        //get start time
        gettimeofday(&start_time, NULL);

        //wait
        nanosleep(&waitInt, NULL);

        //get end time
        gettimeofday(&end_time, NULL);

        //calcul difference (retard)
        diff.tv_sec = end_time.tv_sec - start_time.tv_sec - WAIT_SEC;
        diff.tv_usec = end_time.tv_usec - start_time.tv_usec - WAIT_USEC;

        printf("%ld\n", diff.tv_usec);
    }

    return EXIT_SUCCESS;
}
