#ifndef TREND_CLASSIFICATION_READ_DATA_H
#define TREND_CLASSIFICATION_READ_DATA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isSpace(char c);
int count_length(FILE *fptr);
bool isDigit(char c);
int count_data_in_file(char s[]);
float* read_data(float* data, char s[], int data_length);
int* read_data_Pps(int* data, char s[], int data_length);


#endif //TREND_CLASSIFICATION_READ_DATA_H
