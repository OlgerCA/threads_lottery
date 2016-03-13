#include <time.h>
#include <ucontext.h>
#include "LoteryScheduler.h"
#include "Timer.h"
#include "Viewer.callbacks.h"


static ucontext_t exiter = {0};

LoteryScheduler* Scheduler;

//Free any allocated memory of the lotery scheduler and the Loader
void LoteryScheduler_Free(LoteryScheduler* this){
    int i = 0;
    for(; i< this->numThreads; i++){
        free(this->threads[i]);
    }
    free(this->threads);
    free(this);
}

//Creates a new Lotery Scheduler
void LoteryScheduler_Init(long numThreads, void* function, int preemptive, double yiedlPercentage, long* tickets, long* work, void* exitGreenThreads){
    long i = 0;
    Scheduler = (LoteryScheduler*) (malloc(sizeof(LoteryScheduler)));
    Scheduler->scheduleComplete = 0;
    Scheduler->numThreads = numThreads;
    Scheduler->currentThread = -1; //no current thread yet
    Scheduler->preemptive = preemptive;
    Scheduler->completedThreads = 0;
    Scheduler->yieldPercentage = yiedlPercentage;
    Scheduler->playingTickets = 0;

    getcontext(&exiter);
    make_stack(&exiter);
    makecontext(&exiter, exitGreenThreads, 0);

    Scheduler->state.uc_link = NULL;

    getcontext(&Scheduler->state);
    make_stack(&Scheduler->state);
    Scheduler->state.uc_link = &exiter;
    makecontext(&Scheduler->state, Schedule, 0);

    srand((unsigned int)time(NULL));

    Scheduler->threads = (Thread **) (malloc(numThreads * sizeof(Thread*)));

    for (; i < numThreads; i++){
        Scheduler->threads[i] = Thread_New(i, function, tickets[i], work[i], yiedlPercentage, ThreadCompletes);
        Scheduler->playingTickets += Scheduler->threads[i]->tickets;
    }
}

void LoteryScheduler_Yield() {
    if(Scheduler->currentThread != -1){
        Scheduler->threads[Scheduler->currentThread]->state_reentered = 0;
        getcontext(&Scheduler->threads[Scheduler->currentThread]->threadContext);
        if (Scheduler->threads[Scheduler->currentThread]->state_reentered++ == 0) {
            Schedule();
        }
    } else {
        Schedule();
    }

}

void Schedule(){
    LoteryScheduler_Schedule(Scheduler);
}

// The main method of the scheduler
void LoteryScheduler_Schedule(LoteryScheduler* this){
    int index;
    long ticketSum = 0;

    if(this->completedThreads == this->numThreads){
        if (this->preemptive)
            clear_scheduler_timer();
        pthread_exit((void *) 0);
    }

    int random = rand() % this->playingTickets;

    for(index = 0; index < this->numThreads; index++){
        if(!this->threads[index]->completed){
            ticketSum += this->threads[index]->tickets;
            if(ticketSum > random){
                break;
            }
        }
    }
    this->currentThread = index;
    Scheduler->scheduleComplete = 1;
    if(this->completedThreads < this->numThreads) {
        if (this->preemptive)
            set_next_alarm();
        setcontext(&this->threads[this->currentThread]->threadContext);
    }
}

// Sets the current thread to completed and calls LoteryScheduler_Schedule
void LoteryScheduler_ThreadCompletes(LoteryScheduler* this){
    this->threads[this->currentThread]->completed = 1;
    printf("Thread completed: %ld\n", this->currentThread);
    this->completedThreads++;
    this->playingTickets -= this->threads[this->currentThread]->tickets;
    LoteryScheduler_Yield();
}

void ThreadCompletes(){
    LoteryScheduler_ThreadCompletes(Scheduler);
}

long LoteryScheduler_GetWorkOfCurrentThread(LoteryScheduler* this){
    return this->threads[this->currentThread]->work;
}