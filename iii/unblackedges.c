/*
 *      sudoku.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Implementation to determine if a PGM is a valid sudoku or not using 
 *      our Bit2 interface and PNM reader (pnmrdr)
 */

#include "bit2.h"
#include "assert.h"
#include <pnmrdr.h>
#include <seq.h>

/* Struct element will be within Sequence*/
struct element {
        int bit; /* TODO: if needed in impementation */
        int col;
        int row;
};

/*
 * Implementation Plan:
 * 0. Copy file info into Bit2_T
 *
 * WHEN QUEUE IS EMPTY:
 * 1. Scan edge of the image
 * 2. First check if queue is empty
 * 3. If empty, check if current edge is black or white
 *      a. if white continue along
 *      b. if black emplace in queue
 * 4. Terminating condition is when we get back to starting edge. 
 * IF QUEUE IS NOT EMPTY:
 * 1. check if current pixel is black or white
 *      a. if white, move onto next element of queue (if possible) and repeat
 *         process
 * 2. OTHERWISE, current pixel is black --> check 4 neighbors
 *      a. ignore if white
 *      b. add black pixels to processing queue
 * 3. Once checked all 4 neighbors (TODO: always ensure within bounds), whiten
 *    current pixel being processed
 * 4. repeat process for the rest of the queue (we will be using a sequence)
 */

/* Helper function prototypes */
FILE *openFile(int argc, char *argv[]);
void populate(int col, int row, Bit2_T bit2, int value, void *rdr_vp);

/* TODO: function contract */
int main (int argc, char *argv[])
{
        FILE *fp = openFile(argc, argv);
        
        Pnmrdr_T rdr = Pnmrdr_new(fp);
        Pnmrdr_mapdata data = Pnmrdr_data(rdr);

        /* Declare blank 2D array of PBM's dimensions */
        Bit2_T arr = Bit2_new(data.width, data.height);
        
        /* Populate the array with pnmrdr content */
        Bit2_map_row_major(arr, populate, rdr);
        
        /* For testing: Print Array */
        for (int row = 0; row < Bit2_height(arr); row++) {
                for (int col = 0; col < Bit2_width(arr); col++) {
                        int value = Bit2_get(arr, col, row);
                        printf("%d ", value);
                }
                printf("\n");
        }

        Seq_T queue = Seq_new(0);

        for (int row = 0; row < Bit2_height(arr); row++) {
                if (Seq_length(queue) != 0) {
                        /* TODO: process queue */
                        printf("Queue is not empty!\n");
                }
                int bit = Bit2_get(arr, 0, row);
                if (bit == 1) {
                        struct element *elem = malloc(sizeof(struct element));
                        elem->bit = bit;
                        elem->col = 0;
                        elem->row = row;
                        printf("row = %d, elem->row = %d\n", row, elem->row);
                        Seq_addhi(queue, &elem);
                }
        }

        for (int i = 0; i < Seq_length(queue); i++) {
                struct element *elem = Seq_get(queue, i);
                printf("Coords: (%d, %d)\n", elem->col, elem->row);
        }

        Pnmrdr_free(&rdr);
        Bit2_free(&arr);
        fclose(fp);

        return 0;
}

/******** openFile ********
 *
 * Try to open a file by checking the number of arguments and verifying it has
 * opened. Returns a FILE pointer if successful, otherwise, terminates with a
 * Checked Runtime Error (CRE).
 *
 * Parameters:
 *      int argc:       argument count
 *      char *argv[]:   argument array to access filename
 * Return: 
 *      FILE pointer to file (given file opens successfully)
 * Expects:
 *      argc and argv to be properly defined, other error checking occurs here
 * Notes: 
 *      Terminates with a CRE if the argument count is invalid or if the file
 *      does not open successfully.
 ************************/
FILE *openFile(int argc, char *argv[]) 
{
        /* Check for valid argument count */
        assert(argc == 1 || argc == 2);

        FILE *fp;

        /* Try to open argument */
        if (argc == 2) {
                fp = fopen(argv[1], "rb");
        } else {
                fp = stdin;
        }

        /* Check that file opened successfully */
        assert(fp != NULL);

        return fp;
}

void populate(int col, int row, Bit2_T bit2, int value, void *rdr_vp)
{       
        (void) value;

        /* Convert void pointers to usable pointers */
        Pnmrdr_T rdr_copy = rdr_vp;

        /* Set value within array to the next data element in pnmrdr */
        Bit2_put(bit2, col, row, Pnmrdr_get(rdr_copy));
}