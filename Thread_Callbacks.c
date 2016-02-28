#include "Thread_Callbacks.h"
#include "UI_Callbacks.h"
#include "LoteryScheduler.h"


void updateCallback_expropiative(double accuResult){
    UpdateUI(Scheduler->currentThread, accuResult, 0);
}

void updateCallback_notExpropiative(double accuResult){
    UpdateUI(Scheduler->currentThread, accuResult, 0);
    int percentage = 30;
    if(percentage > 20){
        int returnValue = sigsetjmp(Scheduler->threads[Scheduler->currentThread]->context, 1);  //LoteryScheduler_SaveThread(&Scheduler);
        if (returnValue == 1) {
            return;
        }
        LoteryScheduler_Schedule(Scheduler);
    }
}

void threadFinishedCallback(double accuResult){
    UpdateUI(0, accuResult, 0);
    LoteryScheduler_ThreadCompletes(Scheduler);
}

void runThread() {
    int numberOfUnitsOfWork = 1000000;
    void (*updateCallback)(double) = NULL;
    void (*workFinishedCallback)(double) = NULL;
    int expropiative = 1;
    updateCallback = expropiative? updateCallback_expropiative : updateCallback_notExpropiative ;
    workFinishedCallback = threadFinishedCallback;
    executeThreadWork(numberOfUnitsOfWork,updateCallback, workFinishedCallback);
    //executeThreadWork2(numberOfUnitsOfWork);
}
