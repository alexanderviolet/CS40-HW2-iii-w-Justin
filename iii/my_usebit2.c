/*
 *      my_usebit2.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Interface for two-dimensional bit arrays
 */

#include "bit2.h"


void check_and_print(int col, int row, Bit2_T a, int b, void *cl)
{
        (void) a;
        (void) cl;

        printf("(%d, %d) = %d \n", col, row, b);
}

void populate(int col, int row, Bit2_T a, int b, void *cl)
{
        (void) b;
        (void) cl;

        Bit2_put(a, col, row, (col + row) % 2);
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
        
        bool OK = true;

        Bit2_T bitmap2D = Bit2_new(4,3);

        Bit2_map_row_major(bitmap2D, populate, &OK);

        for (int row = 0; row < Bit2_height(bitmap2D); row++) {
                // printf("Just tried to get rows\n");
                for (int col = 0; col < Bit2_width(bitmap2D); col++) {
                        printf("%d ", Bit2_get(bitmap2D, col, row));
                }
                printf("\n");
        }

        printf("Trying row major!\n");
        Bit2_map_row_major(bitmap2D, check_and_print, &OK);
        printf("Trying column major!\n");
        Bit2_map_col_major(bitmap2D, check_and_print, &OK);



        Bit2_free(&bitmap2D);
        
        return 0;
}