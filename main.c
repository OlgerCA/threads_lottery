#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LoteryScheduler.h"
#include "ThreadWork.h"
#include "Timer.h"


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

   // setup_scheduler_timer(100);
   // executeThreadWork(5000000, updateCallback, finishedCallback);

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}

/*
LoteryScheduler loteryScheduler;

void foo(void) {
    int i = 0;
    long fact = 1;

    while (i < 4) {
        ++i;
        fact *= i;
    }

    LoteryScheduler_SaveResult(&loteryScheduler,fact);
    //LoteryScheduler_SwitchThreads(loteryScheduler);
    LoteryScheduler_ThreadCompletes(&loteryScheduler);
}

int main(int argc, char **argv) {
    loteryScheduler = LoteryScheduler_New(NUM_THREADS, foo);
    LoteryScheduler_Schedule(&loteryScheduler);
    LoteryScheduler_Free(&loteryScheduler);
    return 0;
}
*/