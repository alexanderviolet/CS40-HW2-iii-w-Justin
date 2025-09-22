/*
 *      bit2.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Interface for two-dimensional bit arrays
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bit.h"
#include "assert.h"

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*                      EXCEPTION(S)                     */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - */

Except_T Invalid_Argument;
Except_T Malloc_Error;

struct BT
{
        int width;
        int height;
        Bit_T array;
};

/******** Bit2_new ********
 *
 * Creates a new 2D bit array with specified dimensions
 *
 * Parameters:
 *      int width: number of columns (must be non-negative)
 *      int height: number of rows (must be non-negative)
 * Return: 
 *      Pointer to new Bit2_T instance (under the hood is Hanson bitmap)
 * Expects:
 *      width and height are non-negative
 *      Throws CRE if invalid dimensions
 * Notes:
 *      Initializes all bits to 0 (white)
 ************************/
BT Bit2_new(int width, int height)
{
        /* Ensure dimensions are valid */
        if (width < 0 || height < 0) {
                RAISE(Invalid_Argument);
        }

        /* Make a UArray object */
        BT bit2d = malloc(sizeof(*bit2d));
        if(bit2d == NULL) {
                RAISE(Malloc_Error);
        }

        bit2d->width = width;
        bit2d->height = height;
        bit2d->array = Bit_new(width * height, size);

        return bit2d;
}

/******** Bit2_free ********
 *
 * Deallocates memory used by a 2D bit array
 *
 * Parameters:
 *      BT *bitmap: pointer to Bit2_T instance to free
 * Return: 
 *      Nothing
 * Expects:
 *      bitmap and *bitmap are not NULL
 *      Throws CRE if NULL pointer
 ************************/
void Bit2_free(BT *bitmap);

/******** Bit2_width ********
 *
 * Returns the width (number of columns) of the bit array
 *
 * Parameters:
 *      BT bitmap: Bit2_T instance
 * Return: 
 *      Number of columns
 * Expects:
 *      bitmap is not NULL
 *      Throws CRE if NULL pointer
 ************************/
int Bit2_width(BT bitmap);

/******** Bit2_height ********
 *
 * Returns the height (number of rows) of the bit array
 *
 * Parameters:
 *      BT bitmap: Bit2_T instance
 * Return: 
 *      Number of rows
 * Expects:
 *      bitmap is not NULL
 *      Throws CRE if NULL pointer
 ************************/
int Bit2_height(BT bitmap);

/******** Bit2_get ********
 *
 * Retrieves the bit value at specified coordinates
 *
 * Parameters:
 *      BT bitmap: Bit2_T instance
 *      int col: column index (0-based)
 *      int row: row index (0-based)
 * Return: 
 *      0 or 1 (the bit value)
 * Expects:
 *      bitmap is not NULL
 *      col in range [0, width-1]
 *      row in range [0, height-1]
 *      Throws CRE if out of bounds or NULL pointer
 ************************/
int Bit2_get(BT bitmap, int col, int row);

/******** Bit2_put ********
 *
 * Sets the bit value at specified coordinates
 *
 * Parameters:
 *      BT bitmap: Bit2_T instance
 *      int col: column index (0-based)
 *      int row: row index (0-based)
 *      int bit: value to set (0 or 1)
 * Return: 
 *      Previous value at that position
 * Expects:
 *      bitmap is not NULL
 *      col in range [0, width-1]
 *      row in range [0, height-1]
 *      bit is either 0 or 1
 *      Throws CRE if invalid parameters
 ************************/
int Bit2_put(BT bitmap, int col, int row, int bit);

/******** Bit2_map_row_major ********
 *
 * Applies function to each bit in row-major order
 * (processes each row completely before moving to next row)
 *
 * Parameters:
 *      BT bitmap: Bit2_T instance
 *      TODO: figure out other arguments
 * Return: 
 *      Nothing
 * Expects:
 *      bitmap is not NULL
 *      Throws CRE if NULL pointers
 ************************/
void Bit2_map_row_major(BT bitmap);

/******** Bit2_map_col_major ********
 *
 * Applies function to each bit in column-major order
 * (processes each column completely before moving to next column)
 *
 * Parameters:
 *      BT bitmap: Bit2_T instance
 *      TODO: figure out other arguments
 * Return: 
 *      Nothing
 * Expects:
 *      bitmap is not NULL
 *      Throws CRE if NULL pointers
 ************************/
void Bit2_map_col_major(BT bitmap);

#endif