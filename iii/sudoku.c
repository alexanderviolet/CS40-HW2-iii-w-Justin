/*
 *      sudoku.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Implementation to determine if a PGM is a valid sudoku or not using 
 *      our UArray2 interface and PNM reader (pnmrdr)
 */

#include "uarray2.h"
#include "assert.h"
#include <pnmrdr.h>

/* TODO: function contract */
void populate(int col, int row, UArray2_T uarray2, void *value_vp, void *rdr_vp)
{
        /* Eliminate warning for unused arguments */
        (void) col;
        (void) row;
        (void) uarray2;
        
        /* Convert void pointers to usable pointers */
        Pnmrdr_T rdr_copy = rdr_vp;
        int *value = value_vp;

        /* Set value within array to the next data element in pnmrdr */
        *value = Pnmrdr_get(rdr_copy);
}

/* TODO: check if an element is a part of valid sudoku */
// void check_sudoku_elem(int col, int row, UArray2_T uarray2, void *value_vp, void *tracking_arr)
// {

// }

int main(int argc, char *argv[])
{
        assert(argc == 1 || argc == 2);

        /* Try to open file (assuming that we have 1 argument) */
        FILE *fp = fopen(argv[1], "rb");

        /* Set up PNM reader content */
        Pnmrdr_T rdr = Pnmrdr_new(fp);
        Pnmrdr_mapdata data = Pnmrdr_data(rdr);

        /* Declare blank 2D array of PGM's dimensions */
        UArray2_T arr = UArray2_new(data.width, data.height, sizeof(int));
        
        /* Populate the array with pnmrdr content */
        UArray2_map_row_major(arr, populate, rdr);
        
        /* For testing: Print Array */
        for (int row = 0; row < UArray2_height(arr); row++) {
                for (int col = 0; col < UArray2_width(arr); col++) {
                        int *value = UArray2_at(arr, col, row);
                        printf("%d ", *value);
                }
                printf("\n");
        }


        Pnmrdr_free(&rdr);
        UArray2_free(&arr);
        fclose(fp);

        return 0;
}


#undef T