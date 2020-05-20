#include "diff.h"


float* diff(float x[], int lenX, bool show)
{
    int ndiff = lenX-1;
    int i;
    float *y = (float*) calloc(ndiff, sizeof(float));

    for (i = 0; i<ndiff; i++)
    {
        y[i] = x[i+1]- x[i];

    }
    if (show==true){
        printf("diff\n");

        for (int i = 0; i < ndiff; i++) {
            printf("%3.3f\n", y[i]);
        }
    }
    return y;
}

