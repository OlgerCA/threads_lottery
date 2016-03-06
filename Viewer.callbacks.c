#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Thread_Callbacks.h"
#include "LoteryScheduler.h"
#include "ProgressbarList.h"
#include "FileLoader.h"
#include "SharedState.h"

void* startBackgroundTask(void* parameters) {
    LoteryScheduler_Init(Loader->numThreads, runThread, Loader->preemptive, Loader->quantum, Loader->yieldPercentage, Loader->tickets, Loader->work);

    int retVal = sigsetjmp(Scheduler->context, 1);
    if (retVal == 1) {
        // TODO free memory after UI has stopped updating values
        //printf("\n\n////////////////////////////////free scheduler//////////////////////////\n\n");
        //LoteryScheduler_Free(Scheduler);
        //Scheduler = NULL;
        pthread_exit((void *) 0);
    }
    LoteryScheduler_Schedule(Scheduler);
    pthread_exit((void *) 0);
}

gboolean update_function(gpointer data) {
    int i;
    ThreadEntry* entry = NULL;
    for (i = 0; i < Scheduler->numThreads; i++) {
        entry = &SharedState[i];
        progressbarlist_item_update(i, entry->accuResult, entry->percentage, (int) Scheduler->threads[i]->tickets);
    }
    return true;
}

/* ---------------------------------------------------------------- */
void window_init(GtkBuilder* sender) {
	progressbarlist_init(sender, Loader->numThreads);
}
/* ---------------------------------------------------------------- */
void btStart_clicked(GtkWidget* btStart, gpointer user_data) {
    g_timeout_add(1000, update_function, NULL);

    pthread_t backgroundThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if (pthread_create(&backgroundThread, &attr, startBackgroundTask, NULL))
        puts("ERROR from pthread_create()");
}
/* ---------------------------------------------------------------- */
