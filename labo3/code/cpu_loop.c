#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define n_sec   1
#define n_op    80

int main(void) {

    time_t start_time;
    int nb_it;
    float data;
    double nb_it_avg = 0;


    //répète n_op x afin de faire une moyenne
    for (int i = 0; i < n_op; i++) {

        nb_it = 0;
        data = 1000;
        
        start_time = time(NULL);



        while(time(NULL) < (start_time + n_sec)) {

            data = data * 2;

            ++nb_it;
        }

        nb_it_avg += (double)nb_it;


        printf("%d\n", nb_it);

    }

    nb_it_avg /= n_op;

    //printf("avg nb de multiplication: %f\n", nb_it_avg);

    return EXIT_SUCCESS;
}
