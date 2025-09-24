/*
 *      bit2.h
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

#define T Bit2_T

typedef struct T *T;

/******** Bit2_new ********
 *
 * Creates a new 2D bit array with specified dimensions
 *
 * Parameters:
 *      int width:      number of columns
 *      int height:     number of rows
 * Return: 
 *      Pointer to new Bit2_T instance
 * Expects:
 *      width and height are non-negative
 *      Throws CRE if invalid dimensions
 * Notes:
 *      Initializes all bits to 0 (white)
 ************************/
T Bit2_new(int width, int height);

/******** Bit2_free ********
 *
 * Deallocates memory used by a 2D bit array
 *
 * Parameters:
 *      T *bitmap: pointer to Bit2_T instance to free
 * Return: 
 *      Nothing
 * Expects:
 *      bitmap and *bitmap are not NULL
 *      Throws CRE if client passes NULL pointer
 ************************/
void Bit2_free(T *bitmap);

/******** Bit2_width ********
 *
 * Returns the width (number of columns) of the bit array
 *
 * Parameters:
 *      T bitmap: Bit2_T instance
 * Return: 
 *      Number of columns
 * Expects:
 *      bitmap is not NULL
 *      Throws CRE if NULL pointer
 ************************/
int Bit2_width(T bitmap);

/******** Bit2_height ********
 *
 * Returns the height (number of rows) of the bit array
 *
 * Parameters:
 *      T bitmap: Bit2_T instance
 * Return: 
 *      Number of rows
 * Expects:
 *      bitmap is not NULL
 *      Throws CRE if NULL pointer
 ************************/
int Bit2_height(T bitmap);

/******** Bit2_get ********
 *
 * Retrieves the bit value at specified coordinates
 *
 * Parameters:
 *      T bitmap: Bit2_T instance
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
int Bit2_get(T bitmap, int col, int row);

/******** Bit2_put ********
 *
 * Sets the bit value at specified coordinates
 *
 * Parameters:
 *      T bitmap: Bit2_T instance
 *      int col: column index (0-based)
 *      int row: row index (0-based)
 *      int bit: value to set (0 or 1)
 * Return: 
 *      Previous bit value at that position
 * Expects:
 *      bitmap is not NULL
 *      col in range [0, width-1]
 *      row in range [0, height-1]
 *      bit is either 0 or 1
 *      Throws CRE if invalid parameters
 ************************/
int Bit2_put(T bitmap, int col, int row, int bit);

/******** Bit2_map_col_major ********
 *
 * Applies function to each bit in column-major order
 * (processes each column completely before moving to next column)
 *
 * Parameters:
 *      T bitmap:       Bit2_T instance
 *      void apply:     general function pointer which takes, column, row, 
 *                      bitmap, bit, and closure as parameters
 *      void *cl:       closure pointer for client's implementation.
 * Return: 
 *      Nothing
 * Expects:
 *      all arguments are not NULL
 *      Throws CRE if NULL pointers
 ************************/
void Bit2_map_col_major(T bitmap, 
        void apply(int col, int row, T bitmap, int bit, void *cl), void *cl);

/******** Bit2_map_row_major ********
 *
 * Applies function to each bit in row-major order
 * (processes each column completely before moving to next column)
 *
 * Parameters:
 *      T bitmap:       Bit2_T instance
 *      void apply:     general function pointer which takes, column, row, 
 *                      bitmap, bit, and closure as parameters
 *      void *cl:       closure pointer for client's implementation.
 * Return: 
 *      Nothing
 * Expects:
 *      all arguments are not NULL
 *      Throws CRE if NULL pointers
 ************************/
void Bit2_map_row_major(T bitmap, 
        void apply(int col, int row, T bitmap, int bit, void *cl), void *cl);

#undef T
#endif