#include "LoteryScheduler.h"
#include "Thread.h"
#include "Timer.h"

LoteryScheduler* Scheduler;

//Free any allocated memory of the lotery scheduler
void LoteryScheduler_Free(LoteryScheduler* this){
    int i = 0;
    for(; i< this->numThreads; i++){
        free(this->threads[i]);
    }
    free(this->threads);
    free(this);
}

//Creates a new Lotery Scheduler
void LoteryScheduler_Init(long numThreads, void* function, int preemptive, unsigned int limit, long* tickets, long* work){
    long i = 0;
    Scheduler = (LoteryScheduler*) (malloc(sizeof(LoteryScheduler)));
    Scheduler->numThreads = numThreads;
    Scheduler->currentThread = -1; //no current thread yet
    Scheduler->preemptive = preemptive;


    Scheduler->threads = (Thread **) (malloc(numThreads * sizeof(Thread*)));

    for (; i < numThreads; i++){
        Scheduler->threads[i] = Thread_New(i, function, tickets[i]);
        Scheduler->playingTickets += Scheduler->threads[i]->tickets;
    }
    if(preemptive) {
        setup_scheduler_timer(limit);
    }
}

// Saves the current thread context
int LoteryScheduler_SaveThread(LoteryScheduler* this){
    return sigsetjmp(this->threads[this->currentThread]->context, 1);
}

// Resumes the execution of the current thread to the last call of LoteryScheduler_SaveThread, for the same threadId
void LoteryScheduler_ResumeThread(LoteryScheduler* this){
    siglongjmp(this->threads[this->currentThread]->context, 1);

}

// The main method of the scheduler, for now is first come first served. Sets the current thread to the
// next thread to run, resumes the current thread, if all threads have finished, prints the results
// frees any allocated and performs and exit(0): THIS IS BECAUSE I HAVE NOW FIGURE IT OUT HOW TO EXIT THE PROGRAM WITHOUT AN ERROR
void LoteryScheduler_Schedule(LoteryScheduler* this){
    int index;
    long ticketSum = 0;

    if(this->completedThreads == this->numThreads){
        LoteryScheduler_ResumesOwnContext(this);
    }

    int random = rand() % this->playingTickets;

    for(index = 0; index < this->numThreads; index++){
        if(!this->threads[index]->completed){
            ticketSum += this->threads[index]->tickets;
            if(ticketSum > random){
                this->currentThread = index;
                break;
            }
        }
    }

    if(this->completedThreads < this->numThreads){
        if(this->preemptive){
            set_next_alarm();
        }
        LoteryScheduler_ResumeThread(this);
    }
}

// Sets the current thread to completed and calls LoteryScheduler_Schedule
void LoteryScheduler_ThreadCompletes(LoteryScheduler* this){
    this->threads[this->currentThread]->completed = 1;
    printf("Thread completed: %ld\n", this->currentThread);
    this->completedThreads++;
    this->playingTickets -= this->threads[this->currentThread]->tickets;
    LoteryScheduler_Schedule(this);
}

//saves the context of the scheduler
int LoteryScheduler_SaveOwnContext(LoteryScheduler* this){
    return sigsetjmp(this->context, 1);
}

//saves the context of the scheduler
void LoteryScheduler_ResumesOwnContext(LoteryScheduler* this){
    siglongjmp(this->context, 1);
}