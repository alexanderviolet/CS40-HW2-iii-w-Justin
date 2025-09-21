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

        T2 arr1 = UArray2_new(1,1,1);
        printf("Size1 = %d\n", UArray2_size(arr1));
        printf("Width1 = %d\n", UArray2_width(arr1));
        printf("Height1 = %d\n", UArray2_height(arr1));

        T2 arr2 = UArray2_new(2,2,2);
        printf("Size2 = %d\n", UArray2_size(arr2));
        printf("Width2 = %d\n", UArray2_width(arr2));
        printf("Height2 = %d\n", UArray2_height(arr2));

        printf("Size1 = %d\n", UArray2_size(arr1));
        printf("Width1 = %d\n", UArray2_width(arr1));
        printf("Height1 = %d\n", UArray2_height(arr1));

        UArray2_free(&arr1);
        UArray2_free(&arr2);

        // T2 arrfail = UArray2_new(-1, 1, 1);
        // T2 arrfail = UArray2_new(1, -1, 1);
        // T2 arrfail = UArray2_new(1, 1, -1);
        // printf("SizeFail = %d\n", UArray2_size(arrfail));
        // printf("WidthFail = %d\n", UArray2_width(arrfail));
        // printf("HeightFail = %d\n", UArray2_height(arrfail));

        return 0;
}