#include "UI_Callbacks.h"
#include "ProgressbarList.h"

void UpdateUI(long threadID, double accuResult, double percentage, int execution) {
//	printf("ThreadID: %ld , result: %f percentage: %f execution: %d\n", threadID, accuResult, percentage, execution);

	progressbarlist_item_update(threadID, accuResult, percentage, 1);
}
