
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inssort.h"

void inssort(void *base, size_t nelem, size_t size,
        int(*compare)(const void *, const void *)){   
    char *cbase =  base;
    char *address;
    for(int i = 1; i<(int)nelem; i++){
        int j = i;
        address = (char*)base + size * i;      
        for(; j > 0; j--){
            //printf("%d\n", compare(cbase, address));
            address = (char*)base + size * j;
            cbase = (char*)base + size * (j-1);
            if(compare(cbase, address)<0){
                break;
            }else{
                swap(cbase, address, size);
            }   
        }
        cbase = address;
    }
}

void swap(char *cbase, char *address, size_t size){
   char tmp[size];
   memcpy (tmp, cbase, size);
   memcpy (cbase, address, size);
   memcpy (address, tmp, size);
}


