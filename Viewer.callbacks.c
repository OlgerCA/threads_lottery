#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib/gi18n.h>
#include "Thread_Callbacks.h"
#include "LoteryScheduler.h"
#include "ProgressbarList.h"
#include "FileLoader.h"
#include "SharedState.h"
#include "Timer.h"

void* startBackgroundTask(void* parameters) {
    if (Scheduler->preemptive)
        setup_scheduler_timer(Loader->quantum);
    LoteryScheduler_Yield();
}

void exitGreenThreads(){
    // pthread_exit((void *) 0);
}

gboolean update_function(gpointer data) {
    int i;
    ThreadEntry* entry = NULL;
    gboolean allFinished = true;
    for (i = 0; i < Scheduler->numThreads; i++) {
        entry = &SharedState[i];
        if (entry->percentage != 1)
            allFinished = false;
        progressbarlist_item_update(i, entry->accuResult, entry->percentage, (int) Scheduler->threads[i]->tickets);
    }
    if (allFinished) {
        free(SharedState);
        SharedState = NULL;
        GtkWidget* button = GTK_WIDGET(gtk_builder_get_object(Builder, "btStart"));
        gtk_widget_set_sensitive(button, true);
        return false;
    }
    else
        return true;
}

void file_loader(GtkBuilder* sender) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open File",
                                          GTK_WINDOW(gtk_builder_get_object(sender, "window")),
                                          action,
                                          _("_Cancel"),
                                          GTK_RESPONSE_CANCEL,
                                          _("_Open"),
                                          GTK_RESPONSE_ACCEPT,
                                          NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        FileLoader_Init(filename);
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}

/* ---------------------------------------------------------------- */
void window_init(GtkBuilder* sender) {
    file_loader(sender);
	progressbarlist_init(sender, (int) Loader->numThreads);
}
/* ---------------------------------------------------------------- */
void btStart_clicked(GtkWidget* btStart, gpointer user_data) {
    if (SharedState != NULL) {
        free(SharedState);
        SharedState = NULL;
    }
    SharedState = (ThreadEntry*) malloc(sizeof(ThreadEntry) * Loader->numThreads);
    int i;
    for (i = 0; i < Loader->numThreads; i++) {
        SharedState[i].percentage = 0.0;
        SharedState[i].accuResult = 0.0;
        SharedState[i].iteration = 0;
    }

    if (Scheduler != NULL) {
        Scheduler = NULL;
    }
    LoteryScheduler_Init(Loader->numThreads, runThread, Loader->preemptive,
                         Loader->yieldPercentage, Loader->tickets, Loader->work, exitGreenThreads);

    GtkWidget* button = GTK_WIDGET(gtk_builder_get_object(Builder, "btStart"));
    gtk_widget_set_sensitive(button, false);

    g_timeout_add(100, update_function, NULL);

    pthread_t backgroundThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if (pthread_create(&backgroundThread, &attr, startBackgroundTask, NULL))
        puts("ERROR from pthread_create()");
}
/* ---------------------------------------------------------------- */
