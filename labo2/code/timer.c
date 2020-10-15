#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

timer_t timer;
int nbr_mesure;

void timer_handler (int signum) {
    
    static int count = 0;

    struct itimerspec currSpec;

    timer_gettime(timer, &currSpec);

    //print s:ms:ns
    //printf ("%d:%d:%d\n", currSpec.it_value.tv_sec, ((currSpec.it_value.tv_nsec / 1000) % 1000), (currSpec.it_value.tv_nsec % 1000));

    //print s.ns for summary1.c
    printf("%d.%d\n", currSpec.it_value.tv_sec, currSpec.it_value.tv_nsec);

    count++;

    if(count == nbr_mesure) {
        //printf("END\n");
        exit(EXIT_SUCCESS);
    }
}


int main (int argc, char **argv) {

    long int sec;
    long int msec;
    long int nsec;

    struct sigevent event;
    struct itimerspec spec;

    if (argc < 3) {
        
        printf("Usage : %s <nbr mesure> <ms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    nbr_mesure = strtol(argv[1], NULL, 10);
    //msec = strtol(argv[2], NULL, 10);
    msec = strtod(argv[2], NULL);

    //printf("RUN WITH : %d - %d\n", nbr_mesure, msec);


    //sigevent initialisation
    signal(SIGRTMIN, timer_handler);

    //signifie qu'un signal (SIGRTMIN) sera déclencher
    //à la fin du timer
    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = SIGRTMIN;
    
    sec = msec / 1000;
    nsec = (msec * 1000) % 1000000;
    
    //initie l'intervale
    spec.it_interval.tv_sec = sec;
    spec.it_interval.tv_nsec = nsec;
    spec.it_value = spec.it_interval;


    //printf("%dsec, %dnsec\n", spec.it_interval.tv_sec, spec.it_interval.tv_nsec);

    //printf("[s:ms:ns]\n");

    //crée le timer
    if(timer_create(CLOCK_REALTIME, &event, &timer) < 0) {

        printf("FAILDE CREATE TIMER\n");
        //return EXIT_FAILURE;
    }

    //programme le timer
    if(timer_settime(timer, 0, &spec, NULL) < 0) {

        printf("FAILDE SET TIMER\n");
        //return EXIT_FAILURE;
    }

    while(1);

    return EXIT_SUCCESS;

}
