#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>
#define EXECUTION_TIME 2 /* In seconds */


/* Barrier variable */
pthread_barrier_t barr;


void *f_thread(void *arg)
{
    time_t start_time;
    long nb_it = 0;
    float data = 1000;
    
    start_time = time(NULL);


    pthread_barrier_wait(&barr);
    while(time(NULL) < (start_time + EXECUTION_TIME)) {

        data = data * 2;

        ++nb_it;
    }

    *((long*)arg) = nb_it;
}

int main(int argc, char **argv)
{

    //set rand seed
    srand(time(NULL));

    //dynamic array
    pthread_t *threads;
    int *prio_value;
    long *nb_iterations;

    //total iteration of all threads
    long total_iterations = 0;

    /* Parse input */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s NB_THREADS\n", argv[0]);
        return EXIT_FAILURE;
    }

    intmax_t nb_threads = strtoimax(argv[1], (char **)NULL, 10);

    if (nb_threads <= 0)
    {
        fprintf(stderr, "NB_THREADS must be > 0 (actual: %d)\n", nb_threads);
        return EXIT_FAILURE;
    }

    /* Get minimal and maximal priority values */
    int min_prio = sched_get_priority_min(SCHED_FIFO);
    int max_prio = sched_get_priority_max(SCHED_FIFO);
    max_prio -= min_prio;

    /* Initialize barrier */
    if (pthread_barrier_init(&barr, NULL, nb_threads))
    {
        fprintf(stderr, "Could not initialize barrier!\n");
        return EXIT_FAILURE;
    }

    /* Set priorities and create threads */
    pthread_attr_t thread_attr;
    struct sched_param schedparam;

    //alocate memory for array
    nb_iterations = (long*)malloc(nb_threads * sizeof(long));
    prio_value = (int*)malloc(nb_threads * sizeof(int));
    threads = (pthread_t*)malloc(nb_threads * sizeof(pthread_t));

    for(int i = 0; i < nb_threads; i++) {

        //generate random priority
        prio_value[i] = (rand() % (min_prio - max_prio)) + min_prio;

        /* Set thread attributes necessary to use priorities */
        schedparam.sched_priority = prio_value[i];


        if(pthread_attr_init(&thread_attr) != 0) {

            fprintf(stderr, "Could not init attr!\n");
            return EXIT_FAILURE;
        }

        if(pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED) != 0) {

            fprintf(stderr, "Could not set inherit scheduler!\n");
            return EXIT_FAILURE;
        }

        if (pthread_attr_setschedpolicy(&thread_attr, SCHED_FIFO) != 0){

            fprintf(stderr, "Could not set scheduler policy!\n");
            return EXIT_FAILURE;
        }

        if (pthread_attr_setschedparam(&thread_attr, &schedparam) != 0) {

            fprintf(stderr, "Could not set attribute scheduler parameters!\n");
            return EXIT_FAILURE;
        }
        
        if(pthread_create(threads + i, NULL, f_thread, nb_iterations + i) != 0) {

            fprintf(stderr, "Could not create thread!\n");
            return EXIT_FAILURE;
        }

        if(pthread_setschedparam(threads[i], SCHED_FIFO, &schedparam)) {

            fprintf(stderr, "Could not set scheduler parameters!\n");
            return EXIT_FAILURE;
        }

    }
    
    /* Wait for the threads to complete and set the results */
    for(int i = 0; i < nb_threads; i++) {

        pthread_join(threads[i], NULL);
        total_iterations += nb_iterations[i];
    }

    for (int i = 0; i < nb_threads; ++i)
    {
        fprintf(stdout, "[%02d] %ld (%2.0f%%)\n",
                prio_value[i], nb_iterations[i],
                100.0 * nb_iterations[i] / total_iterations);
    }

    //free memory
    free(prio_value);
    free(nb_iterations);
    free(threads);

    return EXIT_SUCCESS;
}