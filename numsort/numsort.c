/* 
 * File:   numsort.c
 * Author: Hai Vo
 *
 * Created on December 3, 2012, 12:50 PM
 */
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
#include "inssort.h"
char *Exec_Name;
int  Exit_Status = EXIT_SUCCESS;
int compare (const void *a, const void *b)
{
  return ( *(double*)a - *(double*)b );
}

int main(int argc, char** argv) {
    Exec_Name = basename(argv[0]);
    int count = 0;
    double array[1000];
    size_t length;
    if(argc != 1){
        fprintf (stderr, "%s has no condition.\n",
                  Exec_Name);
        Exit_Status = EXIT_FAILURE;   
    }
    for(int i=0; i<1000; i++){ 
        double input;
        int scanct = scanf("%lf", &input);
        if(scanct == EOF) {
            break;
        }
        if(scanct != 1){
            fprintf (stderr, "invalid input.\n");
            Exit_Status = EXIT_FAILURE;
            break;
        }
        array[i]=input;   
        count++;
        length = count;
    }
    inssort(array, count, sizeof(double), compare);
    for(int j=0; j<count; j++){
        printf("%f\n", array[j]);
    }
    return (Exit_Status);
}

