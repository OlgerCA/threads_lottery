#include <config.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include "Viewer.h"

/*
void updateCallback(double currentValue) {
	printf("Current value is: %lf\n", currentValue);
}

void finishedCallback(double finalValue) {
	printf("Final value is: %lf\n", finalValue);
}

int main(int argc, char** argv) {
	setup_scheduler_timer(1000);
	executeThreadWork(5000000, updateCallback, finishedCallback);
}
*/

int main(int argc, char** argv) {
	Viewer* viewer;
	int status;

#ifdef ENABLE_NLS
	bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
#endif

	viewer = viewer_new();
	status = g_application_run(G_APPLICATION(viewer), argc, argv);
	g_object_unref(viewer);

	return status;
}
