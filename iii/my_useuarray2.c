/*
 *      my_usearray2.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Interface for two-dimensional bitmaps
 */

#include "uarray2.h"

typedef long number;

const int DIM1 = 5;
const int DIM2 = 7;
const int ELEMENT_SIZE = sizeof(number);
const int MARKER = 99;

void
check_and_print(int i, int j, UArray2_T a, void *p1, void *p2) 
{
        number *entry_p = p1;

        *((bool *)p2) &= UArray2_at(a, i, j) == entry_p;

        if ( (i == (DIM1 - 1) ) && (j == (DIM2 - 1) ) ) {
                /* we got the corner */
                *((bool *)p2) &= (*entry_p == MARKER);
        }

        printf("ar[%d,%d]\n", i, j);
}

/******** NAME ********
 *
 * TODO: There should not be a main for this
 *
 * Parameters:
 *      int argc:       argument count
 *      char *argv[]:   string of arguments
 * Return: 
 *      0 for exit success
 * Expects:
 *      TODO:
 * Notes:
 *      TODO:
 ************************/
int main(int argc, char *argv[])
{
        /* Eliminate warnings of unused variables */
        (void) argc;
        (void) argv;

        UArray2_T arr1 = UArray2_new(DIM1, DIM2, ELEMENT_SIZE);
        printf("Number of bytes per slot = %d\n", UArray2_size(arr1));
        printf("Width1 = %d\n", UArray2_width(arr1));
        printf("Height1 = %d\n", UArray2_height(arr1));

        /* Set Values to random*/
        int running_total = 0;
        for (int row = 0; row < UArray2_height(arr1); row++) {
                for (int col = 0; col < UArray2_width(arr1); col++) {
                        int *value = UArray2_at(arr1, col, row);
                        *value = running_total;
                        running_total++;
                }
        }

        for (int row = 0; row < UArray2_height(arr1); row++) {
                for (int col = 0; col < UArray2_width(arr1); col++) {
                        int *value = UArray2_at(arr1, col, row);
                        printf("%d ", *value);
                }
                printf("\n");
        }

        *((number *)UArray2_at(arr1, DIM1 - 1, DIM2 - 1)) = MARKER;
        
        bool OK = true;
        UArray2_map_col_major(arr1, check_and_print, &OK);

        UArray2_free(&arr1);

        return 0;
}