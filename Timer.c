
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <ucontext.h>
#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "Timer.h"
#include "LoteryScheduler.h"

#define TIMERSIG SIGRTMIN

long int selected_quantum = 0;

timer_t timer;

void setup_scheduler_timer(unsigned int quantum) {
    selected_quantum = quantum;

    struct sigaction act = {
            .sa_sigaction = invoke_scheduler,
            .sa_flags = SA_SIGINFO,
    };

    long tid;
    tid = syscall(SYS_gettid);

    struct sigevent sigev = {
            .sigev_notify = SIGEV_THREAD_ID,
            .sigev_signo = TIMERSIG,
            .sigev_value.sival_int = 0,
            ._sigev_un._tid = (__pid_t) tid
    };

    sigemptyset(&act.sa_mask);
    sigaction(TIMERSIG, &act, NULL);
    timer_create(CLOCK_THREAD_CPUTIME_ID, &sigev, &timer);
}

void invoke_scheduler(int signum, siginfo_t *si, void *context)
{
    swapcontext(&Scheduler->threads[Scheduler->currentThread]->threadContext, &Scheduler->state);
}

void set_next_alarm() {
    struct itimerspec ts;
    ts.it_interval.tv_sec = 0;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = selected_quantum / 1000;
    ts.it_value.tv_nsec = (selected_quantum % 1000) * 1000 * 1000;
    timer_settime(timer, 0, &ts, NULL);
}
