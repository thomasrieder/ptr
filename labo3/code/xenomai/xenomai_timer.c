
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <rtdk.h>
#include <native/task.h>
#include <native/timer.h>


#define TASK_NAME   "task1"
#define TASK_PRIO   99
#define TASK_CPU_ID 0
#define NB_IT       3000

RTIME time_period_ns = 5000000; //5 ms
RT_TASK task;

void task_handler(void *arg) {

    RTIME now;
    RTIME previous;

    //set the current task periodic with period [time_period_ns]
    if(rt_task_set_periodic(NULL, TM_NOW, time_period_ns) != 0) {

        rt_printf("FAILED TO SET TASK PERIODIC !\n");
        exit(EXIT_FAILURE);
    }

    previous = rt_timer_read();

    for(int i = 0; i < NB_IT; i++) {
        
        //wait period [time_period_ns] [ns]
        rt_task_wait_period(NULL);
        
        now = rt_timer_read();


        rt_printf("%llu\n", (now - previous));

        //prepare for the next iteration previous
        previous = now;
    }

    exit(EXIT_SUCCESS);
}

void catch_signal(int sig) {
    
    rt_task_delete(&task);
}

int main(void) {

    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);

    //lock virtual address space of process into RAM
    mlockall(MCL_CURRENT|MCL_FUTURE);

    //call for rt_printf()
    rt_print_auto_init(1);


    //create task
    if(rt_task_create(&task, TASK_NAME, 0, TASK_PRIO, 0) != 0) {
        rt_printf("FAILED TO CREATE TASK !\n");
        return EXIT_FAILURE;
    }

    //start task
    if(rt_task_start(&task, task_handler, NULL) != 0) {
        rt_printf("FAILED TO START TASK !\n");
        return EXIT_FAILURE;
    }


    pause();

    return EXIT_SUCCESS;
}