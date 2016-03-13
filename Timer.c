
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <ucontext.h>
#include <time.h>
#include "Timer.h"
#include "LoteryScheduler.h"
#include "Thread.h"

#define TIMERSIG SIGRTMIN

long int selected_quantum = 0;

timer_t timer;
/*const struct itimerspec ts = {
        {0, 0},
        {0, 100000000},
};*/

void setup_scheduler_timer(unsigned int quantum) {
    selected_quantum = quantum;

    struct sigaction act = {
            .sa_sigaction = invoke_scheduler,
            .sa_flags = SA_SIGINFO,
    };
    struct sigevent sigev = {
            .sigev_notify = SIGEV_SIGNAL,
            .sigev_signo = TIMERSIG,
            .sigev_value.sival_int = 0,
    };

    sigemptyset(&act.sa_mask);
    sigaction(TIMERSIG, &act, NULL);
    timer_create(CLOCK_PROCESS_CPUTIME_ID, &sigev, &timer);

    //catch_signal(SIGALRM, invoke_scheduler);
}

int catch_signal(int sig,void(*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void invoke_scheduler(int signum, siginfo_t *si, void *context)
{
    swapcontext(&Scheduler->threads[Scheduler->currentThread]->threadContext, &Scheduler->state);
    // LoteryScheduler_Yield();
}

void set_next_alarm() {
    /*struct itimerval new;
    new.it_interval.tv_usec = 0;
    new.it_interval.tv_sec = 0;
    new.it_value.tv_usec = (selected_quantum % 1000) * 1000;
    new.it_value.tv_sec = selected_quantum / 1000;
    setitimer (ITIMER_REAL, &new, NULL);*/

    struct itimerspec ts;
    ts.it_interval.tv_sec = 0;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = selected_quantum / 1000;
    ts.it_value.tv_nsec = (selected_quantum % 1000) * 1000 * 1000;
    timer_settime(timer, 0, &ts, NULL);
}
