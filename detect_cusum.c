#include "detect_cusum.h"

void detect_cusum(float x[], int lenX, List *ta_list, List *tai_list,float threshold, float drift, bool show )
{
    float* gp = malloc(lenX* sizeof(float));
    float* gn = malloc(lenX* sizeof(float));

    int tap = 0;
    int tan = 0;
    float s;

    int i;

    for (  i=1; i < lenX; i++) {
    //s = y_con[i] - y_con[i - 1];
        s = x[i] - x[i - 1];
        gp[i] = gp[i - 1] + s - drift;
        gn[i] = gn[i - 1] - s - drift;

        if (gp[i] < 0) {
            gp[i] = 0;
            tap = i;
        }

        if (gn[i] < 0) {
            gn[i] = 0;
            tan = i;
        }

        if ((gp[i] > threshold) || (gn[i] > threshold))//change detected!
        {
            add(i, ta_list);    //alarm index

            if (gp[i] > threshold) {
                add(tap, tai_list);
            } else {
                add(tan, tai_list);
            }
       // reset alarm
            gp[i] = 0;
            gn[i] = 0;
        }

    }
    //THE CLASSICAL CUSUM ALGORITHM ENDS HERE

    free(gp);
    free(gn);
    //print CUSUM result

    if (show==true){
    printf("ta_list is : \n");
    display(ta_list);
    printf("tai_list is : \n");
    display(tai_list);
    }

}