#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "ProgressbarList.h"

/* Global variables ----------------------------------------------- */
GtkBuilder* progressbarlist_builder = NULL;
int progressbarlist_length = 0;

/* ---------------------------------------------------------------- */
void progressbarlist_init(GtkBuilder *sender, int length) {
	progressbarlist_builder = g_object_ref(sender);
	
	if (length > 10) {
		g_critical("The max capacity for visible threads is 10 (requested: %d)", length);
		progressbarlist_length = 10;
	} else {
		progressbarlist_length = length;
	}
	int i;
	for (i=0; i<progressbarlist_length; i++) {
		gtk_widget_set_visible(GTK_WIDGET(progressbarlist_get_label(i)), 1);
		gtk_widget_set_visible(GTK_WIDGET(progressbarlist_get_progressbar(i)), 1);
	}
}
/* ---------------------------------------------------------------- */
void progressbarlist_item_update(int id, double result, double percentage, int tickets) {
	if (id >= progressbarlist_length) {
		g_critical("Couldn't update item, the thread is not visible (threadid: %d)", id);
		return;
	}
	
	char* label = (char*) malloc(sizeof(char)*64);
	sprintf(label, "Process %i (%d tickets): %3.1f%%", id, tickets, percentage);
	
	char* ptext = (char*) malloc(sizeof(char)*32);
	sprintf(ptext, "%1.15f", result);
	
	gtk_label_set_text(GTK_LABEL(progressbarlist_get_label(id)), label);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbarlist_get_progressbar(id)), label);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbarlist_get_progressbar(id)), 0.3);

	free(label);
	free(ptext);
}
/* ---------------------------------------------------------------- */
GObject* progressbarlist_get_label(int id) {
	if (id >= progressbarlist_length) {
		g_critical("Couldn't get label, the thread is not visible (threadid: %d)", id);
		return NULL;
	}
	
	char* name = (char*) malloc(sizeof(char)*8);
	sprintf(name, "label_%d", id);
	return gtk_builder_get_object(progressbarlist_builder, name);
}
/* ---------------------------------------------------------------- */
GObject* progressbarlist_get_progressbar(int id) {
	if (id >= progressbarlist_length) {
		g_critical("Couldn't get progressbar, the thread is not visible (threadid: %d)", id);
		return NULL;
	}
	
	char* name = (char*) malloc(sizeof(char)*16);
	sprintf(name, "progressbar_%d", id);
	return gtk_builder_get_object(progressbarlist_builder, name);
}
/* ---------------------------------------------------------------- */
