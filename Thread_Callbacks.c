#include "Thread_Callbacks.h"
#include "LoteryScheduler.h"
#include "Thread.h"

void updateCallback_preemptive(double accuResult, double percentage, int iteration){
    UpdateUI(Scheduler->currentThread, accuResult, percentage, iteration);
}

void updateCallback_notPreemptive(double accuResult, double threadCurrentPercentage, int iteration){
    UpdateUI(Scheduler->currentThread, accuResult, threadCurrentPercentage,iteration);
    // if currentPercentage  >  thread->yieldPercentage
    if(threadCurrentPercentage >= Scheduler->threads[Scheduler->currentThread]->yieldPercentage){
        Scheduler->threads[Scheduler->currentThread]->yieldPercentage += Scheduler->yieldPercentage;
        LoteryScheduler_Schedule(Scheduler);
    }
}

void threadFinishedCallback(double accuResult){
    UpdateUI(Scheduler->currentThread, accuResult, 100, -1);
    LoteryScheduler_ThreadCompletes(Scheduler);
}

void runThread() {
    int unitsOfWork = LoteryScheduler_GetWorkOfCurrentThread(Scheduler);
    void (*updateCallback)(double, double, int) = NULL;
    void (*workFinishedCallback)(double) = NULL;
    updateCallback = Scheduler->preemptive ? updateCallback_preemptive : updateCallback_notPreemptive ;
    workFinishedCallback = threadFinishedCallback;

    executeThreadWork(unitsOfWork,updateCallback, workFinishedCallback);
}
