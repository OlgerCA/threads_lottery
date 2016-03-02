#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "Thread_Callbacks.h"
#include "Timer.h"
#include "LoteryScheduler.h"
#include "ProgressbarList.h"

#define PREEMPTIVE 1
#define MILISECONDS 100

/* ---------------------------------------------------------------- */
void window_init(GtkBuilder* sender) {
	progressbarlist_init(sender, NUM_THREADS);
}
/* ---------------------------------------------------------------- */
void btStart_clicked(GtkWidget* btStart, gpointer user_data) {
	// progressbarlist_item_update(1, 3.1234567890, 0.1, 4);
	
	LoteryScheduler_Init(NUM_THREADS, runThread, PREEMPTIVE, MILISECONDS);

	int retVal = sigsetjmp(Scheduler->context, 1);
	if (retVal == 1) {
		return;
	}
	LoteryScheduler_Schedule(Scheduler);
}
/* ---------------------------------------------------------------- */
