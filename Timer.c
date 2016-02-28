
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "Timer.h"

unsigned int selected_quantum = 0;

void setup_scheduler_timer(unsigned int quantum) {
    selected_quantum = quantum;
    catch_signal(SIGALRM, invoke_scheduler);
    alarm(selected_quantum / 1000);
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
    alarm(selected_quantum / 1000);
}