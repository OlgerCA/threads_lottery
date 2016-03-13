
#include "ThreadWork.h"
#include "LoteryScheduler.h"

#define TERMS_PER_UNIT_OF_WORK 50

void executeThreadWork(int threadId, int numberOfUnitsOfWork, void (*updateCallback)(double, double, int), void (*workFinishedCallback)(double)) {
    int i = 0;
    double accumulatedResult = 0;
    double lastTerm = 2;

    for (i = 0; i < numberOfUnitsOfWork; i++) {
        int initial_n = i * TERMS_PER_UNIT_OF_WORK;
        double innerLastTerm = lastTerm;
        double innerAccumulated = accumulatedResult;
        int j;
        double n;
        for (j = initial_n; j < (initial_n + TERMS_PER_UNIT_OF_WORK); j++) {
            n = j;
            innerAccumulated += innerLastTerm;
            innerLastTerm = innerLastTerm * ((4*n*n + 4*n + 1) / (4*n*n + 10*n + 6));
        }

        if(threadId == Scheduler->currentThread){
            accumulatedResult = innerAccumulated;
            lastTerm = innerLastTerm;
            if (i < (numberOfUnitsOfWork - 1))
                updateCallback(accumulatedResult, (double) (i+1) / (double) numberOfUnitsOfWork, i);
        } else {
            i--;
        }

    }
    workFinishedCallback(accumulatedResult);
}