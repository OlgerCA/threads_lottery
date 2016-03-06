#include <gtk/gtk.h>
#include "SharedState.h"
#include "Viewer.h"
#include "LoteryScheduler.h"
#include "FileLoader.h"

int main (int argc, char *argv[])
{
    FileLoader_Init("settings/settingsFile"); // copy settings file to output folder
    SharedState = (ThreadEntry*) malloc(sizeof(ThreadEntry) * Loader->numThreads); // TODO move initialization to other place

    //Initialize GTK+
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init(&argc, &argv);
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    viewer_show();

    gtk_main();

    free(SharedState); // TODO move free to other place
    return 0;
}
