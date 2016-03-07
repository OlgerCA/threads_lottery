#ifndef THREADS_LOTTERY_LOTERYSCHEDULER_H
#define THREADS_LOTTERY_LOTERYSCHEDULER_H

#include <sys/ucontext.h>
#include "Thread.h"

typedef struct {
    Thread** threads;
    long numThreads;
    long currentThread;
    int preemptive;
    long completedThreads;
    int playingTickets;
    double yieldPercentage;
    int scheduleComplete;
    ucontext_t state;
}LoteryScheduler;

extern LoteryScheduler* Scheduler;

void LoteryScheduler_Init(long numThreads, void* function, int preemptive, double yiedlPercentage, long* tickets, long* work, void* exit);
void LoteryScheduler_ThreadCompletes(LoteryScheduler* this);
void LoteryScheduler_Free(LoteryScheduler* this);
void LoteryScheduler_Schedule(LoteryScheduler* this);
long LoteryScheduler_GetWorkOfCurrentThread(LoteryScheduler* this);
void ThreadCompletes();
void LoteryScheduler_Yield();
void Schedule();

#endif //THREADS_LOTTERY_LOTERYSCHEDULER_H
