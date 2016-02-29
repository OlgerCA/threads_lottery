#include "UI_Callbacks.h"

void UpdateUI(long threadID, double accuResult, double percentage, int execution) {
    printf("ThreadID: %ld , result: %f percentage: %f execution: %d\n", threadID, accuResult, percentage, execution);
}
