
#ifndef THREADS_LOTTERY_THREADWORK_H
#define THREADS_LOTTERY_THREADWORK_H

void executeThreadWork(int numberOfUnitsOfWork, void (*updateCallback)(double), void (*workFinishedCallback)(double));

static double executeUnitOfWork(int initial_n, double lastTerm, double *accumulator);

#endif
