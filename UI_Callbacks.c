#include "UI_Callbacks.h"
#include "ProgressbarList.h"

void UpdateUI(long threadID, double accuResult, double percentage, int iteration) {
    printf("ThreadID: %ld , result: percentage: iteration: %d\n", threadID, iteration);
	//progressbarlist_item_update(threadID, accuResult, percentage, 1);
}
