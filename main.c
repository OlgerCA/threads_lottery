#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include "Viewer.h"
#include "LoteryScheduler.h"
#include "FileLoader.h"

int main (int argc, char *argv[])
{
    FileLoader_Init("settings/settingsFile"); // copy settings file to output folder

    //Initialize GTK+
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init(&argc, &argv);
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    viewer_show();

    gtk_main();

    return 0;

}
