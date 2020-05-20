#include <assert.h>
#include "convolve.h"
#include "diff.h"
#include "read_data.h"
void TestConvolve()
{
    float h[] = {1.0 , 1.0};
    float x[] = {1.0 , 1.0, 1.0, 1.0, 1.0};
    int lenY;
    float *y = convolve(h,x,2,5,&lenY,true);
    
    assert(y[0]==1);
    assert(y[1]==2);
    assert(y[2]==2);
    assert(y[3]==2);
    assert(y[4]==2);
    assert(y[5]==1);
}

void TestDiff()
{
    float x[] = {0.1,0.2,0.3};
    int lenY;
    float *y = diff(x,3,false);
    
    for(int i=0; i<2;i++){
      printf("%2.3f\n",y[i]);
    }
    
    //assert(y[0]==0.1);
    //assert(y[1]==2.8);
    free(y);
}


void main()
{
    //TestConvolve();
    //TestDiff();
    float Mv[120];
    char filePps[]="data_Mv.txt";
    read_data(Mv,filePps);

    for(int i =0; i<120; i++){
    printf("%3.3f\n",Mv[i]);
    }


}
