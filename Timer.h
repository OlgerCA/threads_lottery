
#ifndef THREADS_LOTTERY_TIMER_H
#define THREADS_LOTTERY_TIMER_H

extern unsigned int selected_quantum;

void setup_scheduler_timer(unsigned int quantum);

static int catch_signal(int sig,void(*handler)(int));
static void invoke_scheduler(int sig);

#endif
