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
#include <string.h>

/*
 * 
 */
#include "inssort.h"
char *Exec_Name;
int  Exit_Status = EXIT_SUCCESS;
int compare (const void *a, const void *b)
{
  return ( strcmp(*(char **)a, *(char **)b) );
}

int main(int argc, char** argv) {
    Exec_Name = basename(argv[0]);
    int count = 0;
    char *buffer[1000];
    char *temp;
    size_t length;
    if(argc != 1){
        fprintf (stderr, "%s has no condition.\n",
                  Exec_Name);
        Exit_Status = EXIT_FAILURE;   
    }
    for(int i=0; i<1000; i++){ 
        char input[4096];
        char *gotline = fgets (input, sizeof input, stdin);
        if (gotline == NULL) break;
        char *nlpos = strchr(input, '\n');
        if (nlpos != NULL) {
         *nlpos = '\0';
        }else {
         fprintf (stderr, "%s: unterminated line because"
                 " is too long\n", Exec_Name);
         Exit_Status = EXIT_FAILURE;
      }
        /*
        int scanct = scanf ("%4095s", input);
        if(scanct == EOF) {
            break;
        }
        if(scanct != 1){
            fprintf (stderr, "invalid input.\n");
            Exit_Status = EXIT_FAILURE;
            break;
        }
         * */
        temp = strdup(input);
        buffer[i]=temp;   
        count++;
        length = count;
    }
    inssort(buffer, count, sizeof(char*), compare);
    for(int j=0; j<count; j++){
        printf("%s\n", buffer[j]);
        free(buffer[j]);
    }
    return (Exit_Status);
}

