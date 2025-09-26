/*
 *      sudoku.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Implementation to determine if a PGM is a valid sudoku using our UArray2
 *      interface and PNM reader (pnmrdr)
 */

#include "uarray2.h"
#include "assert.h"
#include <pnmrdr.h>

/* Helper functions */
UArray2_T initializeSudoku(int argc, char *argv[]);
FILE *openFile(int argc, char *argv[]);
bool pgm_invalid(Pnmrdr_mapdata data);
bool check_sudoku(UArray2_T sudoku);
void populate(int col, int row, UArray2_T uarray2, void *val_vp, void *rdr_vp);
void check_row(int col, int row, UArray2_T uarray2, void *val_vp, void *cl);
void check_col(int col, int row, UArray2_T uarray2, void *val_vp, void *cl);
void check_box(int col, int row, UArray2_T uarray2, void *val_vp, void *cl);
void check_tracking_array(int number, bool *tracking_arr);

/******** main ********
 *
 * Driver function to run sudoku program. All storage variable pointers and
 * program logic follows within this function. 
 *
 * Parameters:
 *      int argc:       argument count
 *      char *argv[]:   argument array
 * Return: 
 *      0 as main function
 * Expects:
 *      user to compile program :D
 * Notes:
 *      If the sudoku is invalid, the program exits with EXIT_FAILURE.
 ************************/
int main(int argc, char *argv[])
{
        UArray2_T sudoku = initializeSudoku(argc, argv);

        if (check_sudoku(sudoku) == false) {
                exit(EXIT_FAILURE);
        }
        
        return 0;
}

/******** initializeSudoku ********
 *
 * Read info from pgm and copy into UArray2
 *
 * Parameters:
 *      int argc:       argument count
 *      char *argv[]:   argument array
 * Return: 
 *      address of UArray2 object
 * Expects:
 *      pgm to be in P2 format.
 * Notes: 
 *      Uses Pnmrdr to read pgm data into the UArray2 object.
 ************************/
UArray2_T initializeSudoku(int argc, char *argv[])
{
        /* Set up PGM information */
        FILE *fp = openFile(argc, argv);
        Pnmrdr_T rdr = Pnmrdr_new(fp);
        Pnmrdr_mapdata data = Pnmrdr_data(rdr);

        /* Ensure pgm is formatted according to spec */
        if (pgm_invalid(data)) {
                fclose(fp);
                Pnmrdr_free(&rdr);
        }

        /* Declare blank 2D array of PBM's dimensions */
        UArray2_T sudoku = UArray2_new(data.width, data.height, sizeof(int));

        /* Populate the array with pnmrdr content */
        UArray2_map_row_major(sudoku, populate, rdr);

        fclose(fp);
        Pnmrdr_free(&rdr);

        return sudoku;
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

/******** pgm_invalid ********
 *
 * ensure that mapdata of pgm is within format of sudoku
 *
 * Parameters:
 *      Pnmrdr_mapdata data:    mapdata struct of pnmrdr data
 * Return: 
 *      true if invalid format
 *      false if correctly formatted
 * Expects:
 *      data is not NULL
 *      file data is of type P2 for PGM
 * Notes: 
 *      Only the NULL and P2 conditions result in CRE.
 *      The improper width, height, and denominator is just bad Sudoku, so we
 *      signal to exit with EXIT_FAILURE
 ************************/
bool pgm_invalid(Pnmrdr_mapdata data)
{
        assert(data != NULL);
        assert(data.type == 2);

        if (data.width != 9 || data.height != 9 || data.denominator != 9) {
                return true;
        }

        return false;
}

/******** populate ********
 *
 * Take a digit from file and input it into a slot of UArray2 map
 *
 * Parameters:
 *      int col:                col integer of element
 *      int row:                row integer of element
 *      UArray2_T uarray2:      uarray2 object
 *      void *val_vp:           digit element at (col, row)
 *      void *rdr_vp:           void pointer to reader
 * Return: 
 *      none
 * Expects:
 *      uarray2 and rdr_vp are not NULL. Throws CRE otherwise.
 * Notes: 
 *      This function is called by uarray2 mapping functions. 
 *      If sudoku file data is not with digits 1 to 9, then we exit failure
 *      and free memory allocated back in initializeSudoku.
 ************************/
void populate(int col, int row, UArray2_T uarray2, void *val_vp, void *rdr_vp)
{
        assert(uarray2 != NULL && rdr_vp != NULL);
        
        /* Eliminate warning for unused arguments */
        (void) col;
        (void) row;
        (void) uarray2;
        
        /* Convert void pointers to usable pointers */
        Pnmrdr_T rdr_copy = rdr_vp;
        int *value = val_vp;

        /* Set value within array to the next data element in pnmrdr */
        *value = Pnmrdr_get(rdr_copy);
        
        /* If sudoku element is not within [1,9], then improperly formatted */
        if (*(int *)val_vp <= 0 || *(int *)val_vp >= 10) {
                UArray2_free(&uarray2);
                exit(EXIT_FAILURE);
        }
}

/******** check_sudoku ********
 *
 * Check if a sudoku is valid
 *
 * Parameters:
 *      UArray2_T sudoku:       uarray2 object representing sudoku grid
 * Return: 
 *      none
 * Expects:
 *      sudoku is not NULL. Throws CRE otherwise.
 * Notes: 
 *      Checks if the sudoku is valid rowwise, columnwise, and boxwise.
 *      Frees memory of UArray2 which was allocated back in initalizeSudoku
 ************************/
bool check_sudoku(UArray2_T sudoku)
{
        assert(sudoku != NULL);

        /*
         * tracking array's first index represents validity of sudoku. We're 
         * making it size 28 to account for check box's 3 * 9 different checks
         * 3 passes (to check all 9 boxes). It's not super clear cut, but it 
         * works.
         */
        bool tracking[28] = { false };

        /* Check rows, columns, and boxes in that order */
        UArray2_map_row_major(sudoku, check_row, tracking);
        UArray2_map_col_major(sudoku, check_col, tracking);
        UArray2_map_row_major(sudoku, check_box, tracking);

        UArray2_free(&sudoku);
        
        if (tracking[0]) {
                return false;
        } else {
                return true;
        }
}

/******** check_row ********
 *
 * Check row-wise validity of sudoku
 *
 * Parameters:
 *      int col:                col integer of element
 *      int row:                row integer of element
 *      UArray2_T uarray2:      uarray2 object pointer representing sudoku
 *      void *val_vp:           void pointer to value at (col, row)
 *      void *cl:               closure pointer that points to tracking array
 * Return: 
 *      none
 * Expects:
 *      val_vp and cl are not NULL. Otherwise throws CRE.
 * Notes:
 *      none
 ************************/
void check_row(int col, int row, UArray2_T uarray2, void *val_vp, void *cl)
{
        assert(val_vp != NULL && cl != NULL);
        
        (void) uarray2;
        (void) row;
        
        /* Convert closure to boolean type use */        
        bool *tracking_arr = cl;

        /* If ever an invalid sudoku, don't waste computation */
        if (tracking_arr[0]) {
                return;
        }

        /* At start of row, reset tracking array */
        if (col == 0) {
                for (int i = 1; i < 10; i++) {
                        tracking_arr[i] = false;
                }
        }

        /* Check if number has been seen */
        check_tracking_array(*(int *)val_vp, tracking_arr);
}

/******** check_col ********
 *
 * Check column-wise validity of sudoku
 *
 * Parameters:
 *      int col:                col integer of element
 *      int row:                row integer of element
 *      UArray2_T uarray2:      uarray2 object pointer representing sudoku
 *      void *val_vp:           void pointer to value at (col, row)
 *      void *cl:               closure pointer that points to tracking array
 * Return: 
 *      none
 * Expects:
 *      val_vp and cl are not NULL. Otherwise throws CRE.
 * Notes:
 *      none
 ************************/
void check_col(int col, int row, UArray2_T uarray2, void *val_vp, void *cl)
{
        assert(val_vp != NULL && cl != NULL);

        (void) uarray2;
        (void) col;
        
        /* Convert closure to boolean type use */        
        bool *tracking_arr = cl;

        /* If ever an invalid sudoku, don't waste computation */
        if (tracking_arr[0]) {
                return;
        }

        /* At start of column, reset tracking array */
        if (row == 0) {
                for (int i = 1; i < 10; i++) {
                        tracking_arr[i] = false;
                }
        }

        /* Check if number has been seen */
        check_tracking_array(*(int *)val_vp, tracking_arr);
}

/******** check_box ********
 *
 * Check box-wise validity of sudoku
 *
 * Parameters:
 *      int col:                col integer of element
 *      int row:                row integer of element
 *      UArray2_T uarray2:      uarray2 object pointer representing sudoku
 *      void *val_vp:           void pointer to value at (col, row)
 *      void *cl:               closure pointer that points to tracking array
 * Return: 
 *      none
 * Expects:
 *      val_vp and cl are not NULL. Otherwise throws CRE.
 * Notes:
 *      Here is where we really take advantage of the tracking array being
 *      28 slots. There are 27 indicies divided into 3 groups of 9, where each
 *      group represents 3 boxes in row major order. When we check tracking
 *      array, we divide the boxes by staggering by 9 slots. 
 * 
 *      For example:
 *      number 3 for box 2 will be at tracking_array[3 + 9]
 ************************/
void check_box(int col, int row, UArray2_T uarray2, void *val_vp, void *cl)
{
        assert(val_vp != NULL && cl != NULL);
        (void) uarray2;
        
        /* Convert closure to boolean type use */        
        bool *tracking_arr = cl;

        /* If ever an invalid sudoku, don't waste computation */
        if (tracking_arr[0]) {
                return;
        }

        /* At start of new box section, reset tracking array */
        if ((row % 3) == 0) {
                for (int i = 1; i < 28; i++) {
                        tracking_arr[i] = false;
                }
        }

        if (col >= 0 && col <= 2) {
                /* Check if number is seen in box 1 */
                check_tracking_array(*(int *)val_vp, tracking_arr);
        } else if (col >= 3 && col <= 5) {
                /* Check if number is seen in box 2 */
                check_tracking_array(*(int *)val_vp + 9, tracking_arr);
        } else if (col >= 6 && col <= 8) {
                /* Check if number is seen in box 3 */
                check_tracking_array(*(int *)val_vp + 18, tracking_arr);
        }
}

/******** check_tracking_array ********
 *
 * for any given number, check tracking array to ensure it has not been seen
 * before. If not seen, mark as seen. If seen, mark validity slot (index 0) as
 * true to signal sudoku is invalid. 
 *
 * Parameters:
 *      int number: number being checked
 * Return: 
 *      none
 * Expects:
 *      val_vp and cl are not NULL. Otherwise throws CRE.
 * Notes:
 *      This takes advantage of the logic explained in check_box
 ************************/
void check_tracking_array(int number, bool *tracking_arr)
{       
        if (tracking_arr[number]) {
                /* If number previously seen, set first slot to true */
                tracking_arr[0] = true;
        } else {
                /* If unseen, set to seen */
                tracking_arr[number] = true;
        }
}

#undef T