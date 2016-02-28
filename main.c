#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Thread_Callbacks.h"
#include "Timer.h"
#include "LoteryScheduler.h"
#include <errno.h>

/*
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);
    gtk_widget_show_all(window);
}

void updateCallback(double currentValue)
{
    printf("Current value is: %lf\n", currentValue);
}

void finishedCallback(double finalValue)
{
    printf("Final value is: %lf\n", finalValue);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    setup_scheduler_timer(1000);
    executeThreadWork(5000000, updateCallback, finishedCallback);

    //app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    //g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    //status = g_application_run(G_APPLICATION (app), argc, argv);
    //g_object_unref(app);

    return status;
}
 */

void diediedie(int i){
    fprintf(stdout, "%s\n", strerror(errno));
}

void foo(void) {
    int i = 0;
    long fact = 1;

    while (i < 4) {
        ++i;
        fact *= i;
        printf("thread: %ld, result: %ld \n", Scheduler->currentThread, fact);
        int returnValue = LoteryScheduler_SaveThread(Scheduler);
        if (returnValue == 1) {
            continue;
        }
        LoteryScheduler_Schedule(Scheduler);
    }

}

int main2(int argc, char **argv) {
    //LoteryScheduler_Init(NUM_THREADS, runThread);
    catch_signal(SIGINT,diediedie);
    catch_signal(SIGTERM,diediedie);
    catch_signal(SIGKILL,diediedie);

    Scheduler = (LoteryScheduler*) (malloc(sizeof(LoteryScheduler)));
    Scheduler->numThreads = NUM_THREADS;
    Scheduler->currentThread = -1; //no current thread yet
    Scheduler->threads = (Thread*) (malloc(NUM_THREADS * sizeof(Thread)));

    Scheduler->threads[0] = Thread_New(0, runThread);
    Scheduler->threads[1] = Thread_New(1, foo);

    setup_scheduler_timer(1000);
    LoteryScheduler_Schedule(Scheduler);

    return 0;
}
