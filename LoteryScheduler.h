#ifndef THREADS_LOTTERY_LOTERYSCHEDULER_H
#define THREADS_LOTTERY_LOTERYSCHEDULER_H
#define NUM_THREADS 4


#include "Thread.h"

typedef struct {
    Thread** threads;
    long numThreads;
    long currentThread;
    double piResults[NUM_THREADS]; //fow now static
    int expropiative;
}LoteryScheduler;

extern LoteryScheduler* Scheduler;

void LoteryScheduler_Init(long numThreads, void* function);
void LoteryScheduler_Free(LoteryScheduler* this);
int LoteryScheduler_SaveThread(LoteryScheduler* this); //saves current thread context
void LoteryScheduler_ResumeThread(LoteryScheduler* this); //resumes current thread
void LoteryScheduler_Schedule(LoteryScheduler* this);
void LoteryScheduler_ThreadCompletes(LoteryScheduler* this);
void LoteryScheduler_SwitchThreads(LoteryScheduler this);
void LoteryScheduler_SaveResult(LoteryScheduler* this, double result);

#endif //THREADS_LOTTERY_LOTERYSCHEDULER_H
