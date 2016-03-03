/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * viewer.c
 * Copyright (C) 2016 Wil C <wilz04@gmail.com>
 */
#include <glib/gi18n.h>
#include "Viewer.h"
#include "Viewer.callbacks.h"

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/viewer.ui" */
#define UI_FILE "src/viewer.ui"
#define TOP_WINDOW "window"

G_DEFINE_TYPE(Viewer, viewer, GTK_TYPE_APPLICATION);

/* Macro VIEWER_APPLICATION gets Viewer - DO NOT REMOVE */
struct _ViewerPrivate {
	/* Widgets declaration for viewer.ui - DO NOT REMOVE */
};

/* Create a new window loading a file */
static void viewer_new_window(GApplication* app, GFile* file) {
	GtkWidget* window;

	GtkBuilder* builder;
	GError* error = NULL;

	ViewerPrivate* priv = VIEWER_APPLICATION(app)->priv;

	/* Load UI from file */
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, UI_FILE, &error)) {
		g_critical("Couldn't load builder file: %s", error->message);
		g_error_free(error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals(builder, app);

	/* Get the window object from the ui file */
	window = GTK_WIDGET(gtk_builder_get_object(builder, TOP_WINDOW));

	if (!window) {
		g_critical("Widget \"%s\" is missing in file %s.", TOP_WINDOW, UI_FILE);
	}

	/* Widgets initialization for viewer.ui - DO NOT REMOVE */
	window_init(builder);
	g_object_unref(builder);
	
	gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
	if (file != NULL) {
		/* TODO: Add code here to open the file in the new window */
	}

	gtk_widget_show_all(GTK_WIDGET(window));
}

/* GApplication implementation */
static void viewer_activate(GApplication* application) {
	viewer_new_window(application, NULL);
}

static void viewer_open(GApplication* application, GFile** files, gint n_files, const gchar* hint) {
	gint i;
	for (i=0; i<n_files; i++) {
		viewer_new_window(application, files[i]);
	}
}

static void viewer_init(Viewer* object) {
	object->priv = G_TYPE_INSTANCE_GET_PRIVATE(object, VIEWER_TYPE_APPLICATION, ViewerPrivate);
}

static void viewer_finalize(GObject* object) {
	G_OBJECT_CLASS(viewer_parent_class)->finalize(object);
}

static void viewer_class_init(ViewerClass* klass) {
	G_APPLICATION_CLASS(klass)->activate = viewer_activate;
	G_APPLICATION_CLASS(klass)->open = viewer_open;

	g_type_class_add_private(klass, sizeof(ViewerPrivate));

	G_OBJECT_CLASS(klass)->finalize = viewer_finalize;
}

Viewer* viewer_new(void) {
	g_type_init();

	return g_object_new(
		viewer_get_type(),
		"application-id",
		"org.gnome.viewer",
		"flags",
		G_APPLICATION_HANDLES_OPEN,
		NULL
	);
}
