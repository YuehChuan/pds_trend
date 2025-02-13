#include "convolve.h"

float* convolve(float h[], float x[], int lenH, int lenX, int* lenY, bool show)
{
  int nconv = lenH+lenX-1;
  (*lenY) = nconv;
  int i,j,h_start,x_start,x_end;

  float *y = (float*) calloc(nconv, sizeof(float));

  for (i=0; i<nconv; i++)
  {
    x_start = MAX(0,i-lenH+1);
    x_end   = MIN(i+1,lenX);
    h_start = MIN(i,lenH-1);
    for(j=x_start; j<x_end; j++)
    {
      y[i] += h[h_start--]*x[j];
    }
  }

    if (show==true){
        printf("convolution\n");

        for (int i = 0; i < nconv; i++) {
            printf("%3.3f\n", y[i]);
        }
    }
  return y;
}
