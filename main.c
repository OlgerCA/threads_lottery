#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "LoteryScheduler.h"


static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

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