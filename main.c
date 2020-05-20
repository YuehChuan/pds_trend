#include <stdio.h>
#include <stdlib.h>
#include "convolve.h"
#include <assert.h>
#include "diff.h"
#include "list.h"
#include "detect_cusum.h"
#include "read_data.h"
int main() {
    /*
     INPUT DATA: 透過.txt存120個電壓值以及pps值
     data_Mv.txt 120個電壓值
     data_Pps.txt 120個pps值
     透過動態配置Mv 120個float記憶體，計算完成後釋放
     */

    //float Mv[120];
    char fileMv[]="data_Mv.txt";
    char filePps[]="data_Pps.txt";
    //pdSimply到pdcare有可能掉資料點! 未必為120筆 要先算.txt收到幾筆data
    int lenMv= count_data_in_file(fileMv);
    printf("lenMv %d \n", lenMv);
    float *Mv = (float*) calloc(lenMv, sizeof(float));
    read_data(Mv, fileMv, lenMv);
   /*
    printf("diff\n");

    for (int i = 0; i < lenMv; i++) {
        printf("%3.3f\n", Mv[i]);
    }
    */

    /*
    Apply derivertive to Mv to enhance the change
    diff(x, lenX, show)
    x: input
    lenX: length of X
    show: print value

    Return
    -------
    1D array
    */
    float *y = diff(Mv, lenMv, false);
    //free memory
    free(Mv);

    /*convolution
     減少計算量，略過convolution
     因作用不大
     x: input
    lenX: length of X
    convolution mask: h[]
    lenH: convolve length
    show: print value

    Return
    -------
    1D array
    */
/*
    float h[] = {1.0, 1.0}; //convolution length
    int lenH = 2;
    float *y_con = convolve(h, y, lenH, len_Conv, &lenY, true);
    free(y);
*/
    /*
      Detect CUSUM to Mv
    x: input
    len_Conv: length of x

    Parameter:
    -------
    threshold:
    drift:

    show: print value

    Result
    -------
    ta_list : 1D array, int
        alarm time (index of when the change was detected).
    tai_list : 1D array, int
        index of when the change started.
    */
    float threshold =2;
    float drift=0.02;
    int len_Diff= lenMv-1; //differnetial 是差值會少一位

    List * ta_list = makelist();
    List * tai_list = makelist();
    detect_cusum(y, len_Diff, ta_list, tai_list, threshold, drift, true);

    //free memory
    free(y);

    /*External discharge: 0 ,
      Internal discharge :1 ,
      Noise: 3
    */
    /*parameter*/
    int alarm_cnt_threshold = 10;  // 2hr
    float pearsonr_threshold = 0.625;
    int ppsAverageCnt_threshold = 600;  // pps重複率高，超個1000以上大都雜訊
    int ext_high_bound = 120;  //voltage bound
    
    int result;
    int MvAlarm_Cnt=ta_list->size;
    int ppsAverageCnt;
    int sum=0;
    //float Pps[120];  lenMv=lenPps
    int *Pps = (int*) calloc(lenMv, sizeof(float));

    read_data_Pps(Pps, filePps, lenMv);
    //test
    printf("MvAlarm_Cnt %d \n",MvAlarm_Cnt);
    int ta_list_first_element = (ta_list->head)->data;
    //printf("mVIndex %d \n",ta_list_first_element);

    /*calculate corespondent pps average*/
    for (int mVIndex=ta_list_first_element; mVIndex <MvAlarm_Cnt; mVIndex++ ){
        sum= Pps[mVIndex]+sum;
    }
    //free memory
    free(Pps);
    destroy(ta_list);
    destroy(tai_list);

    ppsAverageCnt=sum/MvAlarm_Cnt;
    printf("ppsAverageCnt %d \n",ppsAverageCnt);

    /*   在pdcare端會有空值, 這邊不做檢查 check ppsAverageCnt pps is nan if nan use original data
*/
    if (MvAlarm_Cnt > alarm_cnt_threshold){

        if(0 < ppsAverageCnt && ppsAverageCnt< 120){  // 有效外部放電10-120
            printf("外部放電!!!\n");
            result = 0;
        }
        else if(ppsAverageCnt > ppsAverageCnt_threshold){
            printf("雜訊!!!! PPS過大 (趨勢像外部放電)\n"); //為顯示給開發者知道趨勢歸類哪一種雜訊
            result = 3;
        } else{
            printf("無法判讀\n");
            result = 2;
        }
    }
    else if(MvAlarm_Cnt < alarm_cnt_threshold){
        if (ppsAverageCnt>ppsAverageCnt_threshold){
        printf("雜訊!!!! PPS過大 (趨勢像外部放電)\n"); //為顯示給開發者知道趨勢歸類哪一種雜訊
        result = 3;
        }
        else {
            float r = 0.1;
            //r, p = stats.pearsonr(npMv, npPps); //沒做相似性檢查 減少計算
            if ( (r > pearsonr_threshold)||(ppsAverageCnt > ppsAverageCnt_threshold) ){
            printf(" computed Pearson r: {r} and p-value: {p}");
            printf("雜訊!!!(內)");
            result = 3;
            }
            else{
                printf("趨勢為內部放電!!!但可能為雜訊");
                result = 1;
            }
        }
    }else{
        printf("無法判別!!!\n");
        result =2;
    }
    //free(y_con);
    //destroy(ta_list);
    //destroy(tai_list);
    return 0;
}



