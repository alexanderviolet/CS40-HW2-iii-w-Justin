/*
 *      bit2.h
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Header file for 2D representaiton of a bit map as a client of Hanson's 
 *      bit map interface. Includes function prototypes for future use in .c
 *      file and implementation. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bit.h"

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T

typedef struct T *T;

T Bit2_new(int length);
int Bit2_length(T set);
int Bit2_count(T set);
void Bit2_free(T *set);
int Bit2_get(T set, int n);
int Bit2_put(T set, int n, int bit);
void Bit2_map_row_major(T bit2, void (*function)(), bool *OK);
void Bit2_map_col_major(T bit2, void (*function)(), bool *OK);

#endif