#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib/gi18n.h>
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
        if (SharedState != NULL)
            free(SharedState);
        SharedState = (ThreadEntry*) malloc(sizeof(ThreadEntry) * Loader->numThreads);
        // TODO free when all is finished
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}

/* ---------------------------------------------------------------- */
void window_init(GtkBuilder* sender) {
    file_loader(sender);
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
