/*
 *      my_usebit2.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Interface for two-dimensional bit arrays
 */

#include "bit2.h"

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

        // printf("Before initializing bitmap2D\n");
        Bit2_T bitmap2D = Bit2_new(9,15);
        // printf("After initializing bitmap2D\n");

        for (int row = 0; row < Bit2_height(bitmap2D); row++) {
                // printf("Just tried to get rows\n");
                for (int col = 0; col < Bit2_width(bitmap2D); col++) {
                        printf("%d ", Bit2_get(bitmap2D, col, row));
                }
                printf("\n");
        }

        Bit2_free(&bitmap2D);
        
        return 0;
}