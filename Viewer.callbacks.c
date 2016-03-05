#include <gtk/gtk.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "Thread_Callbacks.h"
#include "Timer.h"
#include "LoteryScheduler.h"
#include "ProgressbarList.h"

/* THIS SHOULD BE REPLACED WITH INFO FROM FILE */
#define PREEMPTIVE 0
#define MILISECONDS 100
#define NUM_THREADS 10

void* startBackgroundTask(void* parameters) {
    /* THIS SHOULD BE REPLACED WITH INFO FROM FILE */
    int i = 0;
    long *tickets = (long*) malloc(NUM_THREADS * sizeof(long));
    long *work = (long*) malloc(NUM_THREADS * sizeof(long));
    for(; i < NUM_THREADS; i++){
        tickets[i] = 10;
        work[i] = 50000;
    }
    Scheduler = NULL;
    /* THIS SHOULD BE REPLACED WITH INFO FROM FILE */
    LoteryScheduler_Init(NUM_THREADS, runThread, PREEMPTIVE, MILISECONDS, tickets, work);

    int retVal = sigsetjmp(Scheduler->context, 1);
    if (retVal == 1) {
        printf("free scheduler");
        LoteryScheduler_Free(Scheduler);
        Scheduler = NULL;
        pthread_exit((void *) 0);
    }
    LoteryScheduler_Schedule(Scheduler);
    pthread_exit((void *) 0);
}

int thread = 0;
gboolean update_function(gpointer data) {
    progressbarlist_item_update(thread % NUM_THREADS, 3.2, 0.3, 1);
    thread++;
    return TRUE;
}

/* ---------------------------------------------------------------- */
void window_init(GtkBuilder* sender) {
	progressbarlist_init(sender, NUM_THREADS);
}
/* ---------------------------------------------------------------- */
void btStart_clicked(GtkWidget* btStart, gpointer user_data) {
	// progressbarlist_item_update(1, 3.1234567890, 0.1, 4);
    g_timeout_add(1000, update_function, NULL);
    pthread_t* backgroundThread = (pthread_t*) malloc(sizeof(pthread_t));
    if (pthread_create(backgroundThread, NULL, startBackgroundTask, NULL))
        puts("ERROR from pthread_create()");
}
/* ---------------------------------------------------------------- */
