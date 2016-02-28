#include "LoteryScheduler.h"
#include "Thread.h"

//Free any allocated memory of the lotery scheduler
void LoteryScheduler_Free(LoteryScheduler* this){
    free(this->threads);
}

//Creates a new Lotery Scheduler
LoteryScheduler LoteryScheduler_New(long numThreads, void* function){
    long i = 0;
    LoteryScheduler this;
    this.numThreads = numThreads;
    this.currentThread = -1; //no current thread yet

    this.threads = (Thread*) (malloc(numThreads * sizeof(Thread)));

    for (; i < numThreads; i++){
        this.threads[i] = Thread_New(i, function);
    }

    return this;
}

// Saves the current thread context
int LoteryScheduler_SaveThread(LoteryScheduler this){
    return sigsetjmp(this.threads[this.currentThread].context, 1);
}

// Resumes the execution of the current thread to the last call of LoteryScheduler_SaveThread, for the same threadId
void LoteryScheduler_ResumeThread(LoteryScheduler this){
    siglongjmp(this.threads[this.currentThread].context, 1);
}

// The main method of the scheduler, for now is first come first served. Sets the current thread to the
// next thread to run, resumes the current thread, if all threads have finished, prints the results
// frees any allocated and performs and exit(0): THIS IS BECAUSE I HAVE NOW FIGURE IT OUT HOW TO EXIT THE PROGRAM WITHOUT AN ERROR
void LoteryScheduler_Schedule(LoteryScheduler* this){
    int completedThreads = 0;
    do{
        if(this->currentThread == -1) {
            this->currentThread = 0;
        }else{
            //determine next thread to run
            this->currentThread = (this->currentThread + 1) % NUM_THREADS; // for now is FCFS
        }
    }while(this->threads[this->currentThread].completed && completedThreads++ < this->numThreads);

    if(completedThreads < this->numThreads){
        LoteryScheduler_ResumeThread(*this);
    }else{
        long i = this->numThreads;
        while(i--){
            printf("Result[%ld]: %f\n", i, this->piResults[i]);
        }
        LoteryScheduler_Free(this);
        exit(0);
    }
}

// Sets the current thread to completed and calls LoteryScheduler_Schedule
void LoteryScheduler_ThreadCompletes(LoteryScheduler* this){
    this->threads[this->currentThread].completed = 1;
    LoteryScheduler_Schedule(this);
}

// this is a test...
void LoteryScheduler_SwitchThreads(LoteryScheduler this) {
    int returnValue = LoteryScheduler_SaveThread(this);
    if (returnValue == 1) {
        return;
    }
    this.currentThread = (this.currentThread + 1) % NUM_THREADS; // for now is FCFS
    LoteryScheduler_ResumeThread(this);
}

// Saves the result of the current thread
void LoteryScheduler_SaveResult(LoteryScheduler* this, double result){
    this->piResults[this->currentThread] = result;
}