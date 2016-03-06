#include <gtk/gtk.h>
#include <stdlib.h>
#include "Thread_Callbacks.h"
#include "LoteryScheduler.h"
#include "ProgressbarList.h"
#include "FileLoader.h"

void* startBackgroundTask(void* parameters) {
    LoteryScheduler_Init(Loader->numThreads, runThread, Loader->preemptive, Loader->quantum, Loader->yieldPercentage, Loader->tickets, Loader->work);

    int retVal = sigsetjmp(Scheduler->context, 1);
    if (retVal == 1) {
        printf("\n\n////////////////////////////////free scheduler//////////////////////////\n\n");
        LoteryScheduler_Free(Scheduler);
        Scheduler = NULL;
        pthread_exit((void *) 0);
    }
    LoteryScheduler_Schedule(Scheduler);
    pthread_exit((void *) 0);
}

int thread = 0;
gboolean update_function(gpointer data) {
    //progressbarlist_item_update(thread % Loader->numThreads, 3.2, 0.3, 1);
    thread++;
    return TRUE;
}

/* ---------------------------------------------------------------- */
void window_init(GtkBuilder* sender) {
	progressbarlist_init(sender, Loader->numThreads);
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
