#include <gtk/gtk.h>

#ifndef PROGRESSBARLIST
#define PROGRESSBARLIST

void progressbarlist_init(GtkBuilder* builder, int length);
void progressbarlist_item_update(int id, double result, double percentage, int tickets);

GObject* progressbarlist_get_label(int id);
GObject* progressbarlist_get_progressbar(int id);

#endif
