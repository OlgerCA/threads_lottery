#include <signal.h>
#include "Thread.h"
#include <sys/mman.h>
#include <ucontext.h>

#define ENV_STACK_SIZE  16384


static ucontext_t exiter = {0};

Thread* Thread_New(long threadID, void *function, long tickets, long work, double yieldPercentage, void* onthreadComplete) {
    Thread* this = (Thread*) (malloc(sizeof(Thread)));
    this->threadID = threadID;
    this->completed = 0;
    this->tickets = tickets;
    this->work = work;
    this->yieldPercentage = yieldPercentage;

    if(exiter.uc_stack.ss_size != ENV_STACK_SIZE){
        getcontext(&exiter);
        make_stack(&exiter);
        makecontext(&exiter, onthreadComplete, 0);
    }

    // this->threadContext.uc_link = NULL;

    getcontext(&this->threadContext);
    make_stack(&this->threadContext);
    this->threadContext.uc_link = &exiter;
    makecontext(&this->threadContext, function, 0);
    return this;
}

void make_stack(ucontext_t *ucp) {
    ucp->uc_stack.ss_sp = mmap(
            NULL, ENV_STACK_SIZE, PROT_READ | PROT_WRITE,
            MAP_ANONYMOUS | MAP_GROWSDOWN | MAP_PRIVATE,
            -1, 0);
    ucp->uc_stack.ss_size = ENV_STACK_SIZE;
}