#include "Thread_Callbacks.h"
#include "UI_Callbacks.h"
#include "LoteryScheduler.h"

void updateCallback_preemptive(double accuResult, double percentage, int execution){
    int returnValue =  sigsetjmp(Scheduler->threads[Scheduler->currentThread]->context, 1); //LoteryScheduler_SaveThread(Scheduler);
    if (returnValue == 1) {
        return;
    }
    UpdateUI(Scheduler->currentThread, accuResult, percentage,execution);
    LoteryScheduler_Schedule(Scheduler);
}

void updateCallback_notPreemptive(double accuResult, double percentage, int execution){
    /*TODO calculate percentage*/
    percentage = 30;
    if(percentage > 20){
        int returnValue =  sigsetjmp(Scheduler->threads[Scheduler->currentThread]->context, 1); //LoteryScheduler_SaveThread(Scheduler);
        if (returnValue == 1) {
            return;
        }
        UpdateUI(Scheduler->currentThread, accuResult, percentage,execution);
        LoteryScheduler_Schedule(Scheduler);
    }
}

void threadFinishedCallback(double accuResult ){
    UpdateUI(Scheduler->currentThread, accuResult, 100, -1);
    LoteryScheduler_ThreadCompletes(Scheduler);
}

void runThread() {
    int numberOfUnitsOfWork = 100000;
    void (*updateCallback)(double, double, int) = NULL;
    void (*workFinishedCallback)(double) = NULL;
    updateCallback = Scheduler->preemptive ? updateCallback_preemptive : updateCallback_notPreemptive ;
    workFinishedCallback = threadFinishedCallback;
    executeThreadWork(numberOfUnitsOfWork,updateCallback, workFinishedCallback);
}
