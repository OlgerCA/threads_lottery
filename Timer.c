
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include "Timer.h"

long int selected_quantum = 0;

void setup_scheduler_timer(unsigned int quantum) {
    selected_quantum = quantum;
    catch_signal(SIGALRM, invoke_scheduler);
    set_next_alarm(selected_quantum);
}

int catch_signal(int sig,void(*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void invoke_scheduler(int sig)
{
    puts("Invoking Scheduler...");
    getchar();
    // Invoke scheduler logic
    set_next_alarm(selected_quantum);
}

void set_next_alarm(long int quantum) {
    struct itimerval new;
    new.it_interval.tv_usec = 0;
    new.it_interval.tv_sec = 0;
    new.it_value.tv_usec = (quantum % 1000) * 1000;
    new.it_value.tv_sec = quantum / 1000;
    setitimer (ITIMER_REAL, &new, NULL);
}
