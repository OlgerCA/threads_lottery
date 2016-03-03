#include <gtk/gtk.h>
#include "Viewer.h"
#include "LoteryScheduler.h"
#include "Thread_Callbacks.h"

/* THIS SHOULD BE REPLACED WITH INFO FROM FILE */
//#define PREEMPTIVE 1
//#define MILISECONDS 100
//#define NUM_THREADS 5

int main (int argc, char *argv[])
{
    /* initialize random seed: */
    srand((unsigned int)time(NULL));


    /* Initialize GTK+ */
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init(&argc, &argv);
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    viewer_show();

    gtk_main();

    /* THIS SHOULD BE REPLACED WITH INFO FROM FILE */
//    int i = 0;
//    long *tickets = (long*) malloc(NUM_THREADS * sizeof(long));
//    long *work = (long*) malloc(NUM_THREADS * sizeof(long));
//    for(; i < NUM_THREADS; i++){
//        tickets[i] = 10 + rand() % 10000;
//        work[i] = 50;
//    }

    /* THIS SHOULD BE REPLACED WITH INFO FROM FILE */
//    LoteryScheduler_Init(NUM_THREADS, runThread, PREEMPTIVE, MILISECONDS, tickets, work);
//
//    int retVal = sigsetjmp(Scheduler->context, 1);
//    if (retVal == 1) {
//        return 0;
//    }
//    LoteryScheduler_Schedule(Scheduler);
//    LoteryScheduler_Free(Scheduler);


    return 0;

}