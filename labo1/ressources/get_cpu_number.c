
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>


void print_time() {
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    printf("[%d:%d:%d] ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

int main(void) {

    int curr_cpu = sched_getcpu();
    int tmp_cpu;

    print_time();
    printf("Start CPU: %d\n", curr_cpu);


    while(1) {

        tmp_cpu = sched_getcpu();

        //si le nouveau cpu à changé
        if(tmp_cpu != curr_cpu) {

            //récupère le nouveau CPU
            curr_cpu = sched_getcpu();

            //print l'heure et le nouvea CPU
            print_time();
            printf("New CPU: %d\n",  curr_cpu);
        }
    }

    return EXIT_SUCCESS;
}
