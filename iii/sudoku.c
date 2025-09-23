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

void populate(int col, int row, UArray2_T uarray2, void *value_vp, void *rdr_vp)
{
        printf("col %d ", col);
        printf("row %d \n", row);
        (void) uarray2;

        Pnmrdr_T rdr_copy = rdr_vp;

        int *value = value_vp;

        // assert(UArray2_at(uarray2, col, row) == value);
        printf("value %d\n", Pnmrdr_get(rdr_copy));

        *value = Pnmrdr_get(rdr_copy);
}

int main(int argc, char *argv[])
{
        assert(argc == 1 || argc == 2);

        /* Try to open file (assuming that we have 1 argument) */
        FILE *fp = fopen(argv[1], "rb");
        Pnmrdr_T rdr;

        /* Test */
        rdr = Pnmrdr_new(fp);

        Pnmrdr_mapdata data = Pnmrdr_data(rdr);

        /* Access inital pgm info: */
        printf("trying to access data:\n");
        printf("width of pgm: %u\n", data.width);
        printf("height of pgm: %u\n", data.height);

        UArray2_T arr = UArray2_new(data.width, data.height, sizeof(int));
        printf("height %d ", UArray2_height(arr));
        UArray2_map_row_major(arr, populate, rdr);
        // for (int row = 0; row < data.height; row++) {
        //         for (int col = 0; col < data.width; col++) {
        //                 int *value = UArray2_at(ar);
        //         }
        // }

        Pnmrdr_free(&rdr);
        UArray2_free(&arr);
        fclose(fp);

        return 0;
}


#undef T