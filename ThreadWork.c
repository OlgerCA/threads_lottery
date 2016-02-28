
#include "ThreadWork.h"
#include "LoteryScheduler.h"

#define TERMS_PER_UNIT_OF_WORK 50

int threadid = 0;

void executeThreadWork(int numberOfUnitsOfWork, void (*updateCallback)(double), void (*workFinishedCallback)(double)) {
    int i = 0;
    double accumulatedResult = 0;
    double lastTerm = 2;
    for (i = 0; i < numberOfUnitsOfWork; i++) {
        lastTerm = executeUnitOfWork(i * TERMS_PER_UNIT_OF_WORK, lastTerm, &accumulatedResult);
        if (i < (numberOfUnitsOfWork - 1)) {
            UpdateUI(threadid++ % 2, accumulatedResult, 0);
            updateCallback(accumulatedResult);
            /*UpdateUI(Scheduler->currentThread, accumulatedResult, 0);
            int percentage = 30;
            if(percentage > 20){
                int returnValue = LoteryScheduler_SaveThread(&Scheduler);
                if (returnValue == 1) {
                    continue;
                }
                //Scheduler->currentThread = 1 -Scheduler->currentThread;
                //siglongjmp(Scheduler->threads[Scheduler->currentThread].context, 1);
                LoteryScheduler_Schedule(Scheduler);*/
            //}
        }
    }
    workFinishedCallback(accumulatedResult);
}

double executeUnitOfWork(int initial_n, double lastTerm, double *accumulator) {
    int i;
    double n;
    for (i = initial_n; i < (initial_n + TERMS_PER_UNIT_OF_WORK); i++) {
        n = i;
        *accumulator += lastTerm;
        lastTerm = lastTerm * ((4*n*n + 4*n + 1) / (4*n*n + 10*n + 6));
    }
    return lastTerm;
}

void executeThreadWork2(int numberOfUnitsOfWork) {
    int i = 0;
    double accumulatedResult = 0;
    double lastTerm = 2;
    for (i = 0; i < numberOfUnitsOfWork; i++) {
        lastTerm = executeUnitOfWork(i * TERMS_PER_UNIT_OF_WORK, lastTerm, &accumulatedResult);
        if (i < (numberOfUnitsOfWork - 1)) {
            UpdateUI(Scheduler->currentThread, accumulatedResult, 0);
            int percentage = 30;
            if(percentage > 20){
                int returnValue = sigsetjmp(Scheduler->threads[Scheduler->currentThread].context, 1);  //LoteryScheduler_SaveThread(&Scheduler);
                if (returnValue == 1) {
                    continue;
                }
                Scheduler->currentThread = 1 -Scheduler->currentThread;
                siglongjmp(Scheduler->threads[Scheduler->currentThread].context, 1);
                //LoteryScheduler_Schedule(Scheduler);

            }
        }
    }
}