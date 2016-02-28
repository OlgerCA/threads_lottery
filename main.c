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


int main(int argc, char **argv) {
    LoteryScheduler_Init(NUM_THREADS, runThread);
    //setup_scheduler_timer(1000);
    LoteryScheduler_Schedule(Scheduler);

    return 0;
}
