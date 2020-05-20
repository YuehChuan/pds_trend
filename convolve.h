#ifndef TREND_CLASSIFICATION_CONVOLVE_H
#define TREND_CLASSIFICATION_CONVOLVE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// helper functions to get the min and max of two numbers
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

/**
 the convolve function will have as input two arrays h and x.
 I will return a pointer to a new array, as well as,
 set the length of that array in lenY.
 The length of h and x must be specified as inputs.
*/
float* convolve(float h[], float x[], int lenH, int lenX, int* lenY, bool show);
#endif //TREND_CLASSIFICATION_CONVOLVE_H