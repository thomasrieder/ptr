#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NB_MESURES 30


int main (int argc, char **argv)
{
    struct timespec tv;
    struct timespec tv_res;
    int i;

    //get la résolution de cette clock
    clock_getres(CLOCK_REALTIME, &tv_res);

    printf("Resolution : %ld.%06ld\n", tv_res.tv_sec, tv_res.tv_nsec);

    for (i = 0; i < NB_MESURES; ++i) {

        //get current time
        clock_gettime(CLOCK_REALTIME, &tv);
        printf("%2d : %ld.%06ld\n", i, tv.tv_sec, tv.tv_nsec);
    }

    return EXIT_SUCCESS;
}