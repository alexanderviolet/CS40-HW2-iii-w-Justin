/*
 *      my_useuarray2.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Interface for two-dimensional bit arrays
 */

#include "uarray2.h"

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

        T2 arr1 = UArray2_new(9,9,4);
        printf("Number of bytes per slot = %d\n", UArray2_size(arr1));
        printf("Width1 = %d\n", UArray2_width(arr1));
        printf("Height1 = %d\n", UArray2_height(arr1));

        /* Set Values to random*/
        for (int row = 0; row < 9; row++) {
                for (int col = 0; col < 9; col++) {
                        // void *vptr = UArray2_at(arr1, row, col);
                        // int *value = vptr;
                        int *value = UArray2_at(arr1, col, row);
                        *value = (row + col) % 2;
                }
        }

        /* Print out values for testing*/
        for (int row = 0; row < 9; row++) {
                for (int col = 0; col < 9; col++) {
                        int *value = UArray2_at(arr1, col, row);
                        printf("%d ", *value);
                }
                printf("\n");
        }

        return 0;
}