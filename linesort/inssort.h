/* 
 * File:   inssort.h
 * Author: Hai Vo
 *
 * Created on December 3, 2012, 12:52 PM
 */

#ifndef __INSSORT_H__
#define __INSSORT_H__

void inssort(void *base, size_t nelem, size_t size, 
        int(*compar) (const void *, const void *));

void swap(char *cbase, char *address, size_t size);

#endif
