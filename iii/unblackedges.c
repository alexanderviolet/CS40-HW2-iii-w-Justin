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
#include <stack.h>

typedef struct element Element;

struct element {
        int col;
        int row;
};

/* Helper function prototypes */
Bit2_T initializeBitMap(int argc, char *argv[]);
FILE *openFile(int argc, char *argv[]);
void populate(int col, int row, Bit2_T bit2, int value, void *rdr_vp);
void check_edges(int col, int row, Stack_T stack, Bit2_T bit2);
void process_stack(Stack_T stack, Bit2_T bit2);
void process_element(Stack_T stack, Bit2_T bit2);
void push_to_stack(int col, int row, Stack_T stack, Bit2_T);

/******** main ********
 *
 * Driver function for unblackedges program
 *
 * Parameters:
 *      int argc:       argument count integer
 *      char *argv[]:   argument character arrays
 * Return: 
 *      0 if successful program run
 * Expects:
 *      None
 * Notes: 
 *      None
 ************************/
int main (int argc, char *argv[])
{
        /* Initialize Data Structures */
        Bit2_T bit2 = initializeBitMap(argc, argv);
        Stack_T stack = Stack_new();

        /* Hardcoding for 1st column (left side) */
        for (int row = 0; row < Bit2_height(bit2); row++) {
                check_edges(0, row, stack, bit2);
        }

        /* Hardcoding for last row (bottom side) */
        for (int col = 0; col < Bit2_width(bit2); col++) {
                check_edges(col, Bit2_height(bit2) - 1, stack, bit2);
        }
        /* Hardcoding for last column (right side) */
        for (int row = 0; row < Bit2_height(bit2); row++) {
                check_edges(Bit2_width(bit2) - 1, row, stack, bit2);
        }
        /* Hardcoding for 1st row (top side) */
        for (int col = 0; col < Bit2_width(bit2); col++) {
                check_edges(col, 0, stack, bit2);
        }

        /* Print remaining content */
        for (int row = 0; row < Bit2_height(bit2); row++) {
                for (int col = 0; col < Bit2_width(bit2); col++) {
                        int value = Bit2_get(bit2, col, row);
                        printf("%d ", value);
                }
                printf("\n");
        }

        Stack_free(&stack);
        Bit2_free(&bit2);

        return 0;
}

/******** initializeBitMap ********
 *
 * Read info from pgm and copy into bitmap
 *
 * Parameters:
 *      int argc:       argument count
 *      char *argv[]:   argument character arrays
 * Return: 
 *      address of bit2 object
 * Expects:
 *      None
 * Notes: 
 *      None
 ************************/
Bit2_T initializeBitMap(int argc, char *argv[])
{
        /* Set up PGM information */
        FILE *fp = openFile(argc, argv);
        Pnmrdr_T rdr = Pnmrdr_new(fp);
        Pnmrdr_mapdata data = Pnmrdr_data(rdr);

        /* Declare blank 2D array of PBM's dimensions */
        Bit2_T bit2 = Bit2_new(data.width, data.height);
        
        /* Populate the array with pnmrdr content */
        Bit2_map_row_major(bit2, populate, rdr);

        /* Output Header to standard output */
        printf("P1\n%d %d\n", data.width, data.height);

        fclose(fp);
        Pnmrdr_free(&rdr);

        return bit2;
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

/******** populate ********
 *
 * Take a bit from file and input it into a slot of bit2 map
 *
 * Parameters:
 *      int col:        col integer of element
 *      int row:        row integer of element
 *      Bit2_T bit2:    bit2 object 
 *      int value:      bit element at (col, row)
 *      void *rdr_vp:   void pointer to reader 
 * Return: 
 *      none
 * Expects:
 *      bit2 and rdr_vp are not NULL. Throws CRE otherwise.
 * Notes: 
 *      This function is called by bit mapping functions. 
 ************************/
void populate(int col, int row, Bit2_T bit2, int value, void *rdr_vp)
{       
        assert(bit2 != NULL && rdr_vp != NULL);
        
        (void) value;

        /* Convert void pointers to usable pointers */
        Pnmrdr_T rdr_copy = rdr_vp;

        /* Set value within array to the next data element in pnmrdr */
        Bit2_put(bit2, col, row, Pnmrdr_get(rdr_copy));
}

/* TODO: function contract */
void check_edges(int col, int row, Stack_T stack, Bit2_T bit2)
{
        /* ALWAYS check at before every iteration if stack is populated */
        if (Stack_empty(stack) == false) {
                process_stack(stack, bit2);
        }
        /* Check if edge bit is black and push accordingly */
        int bit = Bit2_get(bit2, col, row);
        if (bit == 1) {
                push_to_stack(col, row, stack, bit2);
        }
}

/******** process_stack ********
 *
 * Loop through stack and whiten black edges until stack is empty.
 *
 * Parameters:
 *      Stack_T stack:  stack of coordiates that may or may not need to be 
 *                      whitened
 *      Bit2_T bit2:    bit2 map of image data
 * Return: 
 *      none
 * Expects:
 *      stack and bit2 are not NULL. Throws CRE otherwise. 
 * Notes: 
 *      drives loop to iterate through stack. Pushing / popping is elsewhere. 
 ************************/
void process_stack(Stack_T stack, Bit2_T bit2)
{
        assert(stack != NULL && bit2 != NULL);

        while (Stack_empty(stack) == false) {
                process_element(stack, bit2);
        }
}

/******** process_element ********
 *
 * Determine if specific element must be whitened and add neighbors to stack for
 * future checking. 
 *
 * Parameters:
 *      Stack_T stack:  stack of coordiates that may or may not need to be 
 *                      whitened
 *      Bit2_T bit2:    bit2 map of image data
 * Return: 
 *      none
 * Expects:
 *      stack and bit2 are not NULL. Throws CRE otherwise. 
 * Notes: 
 *      Here is where pushing / popping logic occurs.  
 ************************/
void process_element(Stack_T stack, Bit2_T bit2)
{
        assert(stack != NULL && bit2 != NULL);
        assert(Stack_empty(stack) == false);
        
        /* Retrieve current element from stack */
        Element *elem = Stack_pop(stack); 
        
        /* Ensure current pixel is not white as to not check neighbors */
        if (Bit2_get(bit2, elem->col, elem->row) == 0) {
                /* Nothing left to process from this point */
                free(elem);
                return;
        }

        /* Otherwise, element is black. Push neighbors and set to white */
        push_to_stack(elem->col - 1, elem->row, stack, bit2);
        push_to_stack(elem->col + 1, elem->row, stack, bit2);
        push_to_stack(elem->col, elem->row + 1, stack, bit2);
        push_to_stack(elem->col, elem->row - 1, stack, bit2);

        /* set to white */
        Bit2_put(bit2, elem->col, elem->row, 0);

        /* Recycle memory of processed element. No longer necessary */
        free(elem);
}

/******** push_to_stack ********
 *
 * For a given set of coordinates, push said coords to the stack for future
 * processing.
 *
 * Parameters:
 *      int col:        column index of bit
 *      int row:        row index of bit
 *      Stack_T stack:  stack of coordiates that may or may not need to be 
 *                      whitened
 *      Bit2_T bit2:    bit2 map of image data
 * Return: 
 *      none
 * Expects:
 *      stack and bit2 are not NULL. 
 *      Throws CRE otherwise. 
 * Notes: 
 *      Checks to see if column and row are within range. Otherwise, we simply
 *      don't add to stack rather than throwing CRE. 
 *      We are mallocing each struct here, so be sure to free!
 ************************/
void push_to_stack(int col, int row, Stack_T stack, Bit2_T bit2)
{
        assert(stack != NULL && bit2 != NULL);

        /* Ensure col and row are within range, move on otherwise */
        if(col < 0 || col >= Bit2_width(bit2) || row < 0 || 
                row >= Bit2_height(bit2)) {
                return;
        }

        Element *elem = malloc(sizeof(Element));
        assert(elem != NULL);

        elem->col = col;
        elem->row = row;

        Stack_push(stack, elem);
}