#ifndef THREADS_LOTTERY_THREAD_H
#define THREADS_LOTTERY_THREAD_H

#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>


#define STACK_SIZE 4096 * 2

#ifdef __x86_64__ // code for 64 bit Intel arch

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

#else // code for 32 bit Intel arch

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5

#endif

typedef struct {
    long threadID;
    long tickets;
    long work;
    double yieldPercentage;
    int completed;
    ucontext_t threadContext;
    int state_reentered;
}Thread;


void make_stack(ucontext_t *ucp);

Thread* Thread_New(long threadID, void *function, long tickets, long work, double yieldPercentage, void* onthreadComplete);

#endif //THREADS_LOTTERY_THREAD_H
