#include "UI_Callbacks.h"

void UpdateUI(long threadID, double accuResult, double percentage) {
    printf("ThreadID: %ld , currentResult: %f \n", threadID, accuResult);
}
