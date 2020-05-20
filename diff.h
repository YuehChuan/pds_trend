#ifndef TREND_CLASSIFICATION_DIFF_H
#define TREND_CLASSIFICATION_DIFF_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//helper functions to get the min and max of two numbers
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

float* diff( float x[], int lenX, bool show);
#endif //TREND_CLASSIFICATION_DIFF_H