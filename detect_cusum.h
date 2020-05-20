#ifndef TREND_CLASSIFICATION_DETECT_CUSUM_H
#define TREND_CLASSIFICATION_DETECT_CUSUM_H
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void detect_cusum(float x[], int lenX, List *ta_list, List *tai_list,float threshold, float drift, bool show);
#endif //TREND_CLASSIFICATION_DETECT_CUSUM_H
