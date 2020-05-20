#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


bool isDigit(char c)
{
    if ( (c - '0') >= 0 && (c - '0') <= 9 )
        return true;
    return false;
}
bool isSpace(char c)
{
    if (c == ' ' || c == '\t')
        return true;
    return false;
}


int count_length(FILE *fptr)
{
    int length=0;
    char c = fgetc(fptr);

    while( isSpace(c)==false )
    {
        c = fgetc(fptr);
        length++;
    }
    return length;
}

/*
int count_data_in_file(char s[]){
    FILE *fp;
    if ((fp = fopen( s, "r")) == NULL){
        printf("Error! opening file");
    }

    int i = 0;
    float *data = (float*) calloc(120, sizeof(float));

    while(!feof(fp))
    {
        fscanf(fp,"%f",&data[i]);
        printf("%3.3f\n",data[i] );
        i++;
    }
    fclose(fp);
    free(data);
    printf("i= %d", i);
    return i;
}
*/

int count_data_in_file(char s[]){
    FILE *fp;
    if ((fp = fopen( s, "r")) == NULL){
        printf("Error! opening file");
    }
    char c;
    int nFloat=0;
    while(!feof(fp))
    {
        fscanf(fp,"%c",&c);
        if (c=='.')  //is a dot from a floating number
            nFloat++;
    }
    return nFloat;
}

float* read_data(float* data, char s[], int data_length) {
    FILE *fp;
    if ((fp = fopen( s, "r")) == NULL){
        printf("Error! opening file");
    }

    for(int i=0; i<data_length ; i++){
        fscanf(fp,"%f",&data[i]);
       // printf("%3.3f\n", data[i]);
    }
    fclose(fp);
    return data;
}

int* read_data_Pps(int* data, char s[], int data_length) {
    FILE *fp;
    if ((fp = fopen( s, "r")) == NULL){
        printf("Error! opening file");
    }

    for(int i=0; i<data_length ; i++){
        fscanf(fp,"%d",&data[i]);
        //printf("%d\n", data[i]);
    }
    fclose(fp);
    return data;
}

