/*
 *      uarray2.h
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Header file with function prototypes and function contracts for the 
 *      UArray2 Implementation. This is also part of our design submission, so
 *      future us don't get confused when you see function contracts here rather
 *      than the .c file. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uarray.h"

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T

typedef struct T *T;

/******** UArray2_new ********
 *
 * Allocates space for a UArray2 if height and width are non-negative and size
 * is positive.
 *
 * Parameters:
 *      int height: the height of the array to be created
 *      int width: the width of the array to be created
 *      int size: the number of bytes per cell in the array
 * Return: 
 *      a struct pointer to the instance of the new UArray
 * Expects:
 *      height and width are nonnegative
 *      size is positive
 *      throws a CRE if an invalid input is given
 * Notes:
 *      None
 ************************/
T UArray2_new(int height, int width, int size);

/******** UArray2_free ********
 *
 * Recycle memory of a UArray2
 *
 * Parameters:
 *      *uarray2: pointer value of uarray object
 * Return: 
 *      Nothing, but Hanson's UArray_free will signal that uarray2 points to
 *      freed memory at end of successful function call
 * Expects:
 *      CRE if uarray2 or *uarray2 are NULL (plan to check if thrown by Hanson)
 * Notes:
 *      In reality, *uarray2 points to a struct pointer to a UArray
 ************************/
void UArray2_free(T *uarray2);

/******** UArray2_length ********
 *
 * Return the number of elements of a UArray2
 *
 * Parameters:
 *      uarray2: address value of uarray object
 * Return: 
 *      int representing the number of elements of a UArray2
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 * Notes:
 *      none
 ************************/
int UArray2_length(T uarray2);

/******** UArray2_height ********
 *
 * Return the number of rows of a UArray2
 *
 * Parameters:
 *      uarray2: address value of uarray object
 * Return: 
 *      int representing the number of rows of a UArray2
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 * Notes:
 *      none
 ************************/
int UArray2_height(T uarray2);

/******** UArray2_width ********
 *
 * Return the number of columns of a UArray2
 *
 * Parameters:
 *      uarray2: address value of uarray object
 * Return: 
 *      int representing the number of columns of a UArray2
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 * Notes:
 *      none
 ************************/
int UArray2_width(T uarray2);

/******** UArray2_size ********
 *
 * Return the number of bytes per unboxed slot
 *
 * Parameters:
 *      uarray2: address value of uarray object
 * Return: 
 *      Return the number of bytes per unboxed slot
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 * Notes:
 *      none
 ************************/
int UArray2_size(T uarray2);

/******** UArray2_at ********
 *
 * Client requests UArray2_at(row, col). Under the hood, we are actually going
 * for 1D Uarray which can be accessed at UArray_at(row * width + col).
 *
 * Parameters:
 *      uarray2: address value of uarray object
 *      int row: the row of the requested cell
 *      int col: the col of the requested cell
 * Return: 
 *      void pointer to value stored at (row, col) 2D or (row * width + col) 1D
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 *      row and col are within [0, height - 1] and [0, width - 1] respectively
 * Notes:
 *      none
 ************************/
void *UArray2_at(T uarray2, int row, int col);

/******** UArray2_map_row_major ********
 *
 * Visit each cell in array via row major order and map according to some 
 * function's instructions. Iterate through each row by checking all columns 
 * before moving onto next row. Under the hood, this will be a simple iteration
 * through the 1D array elements. 
 *
 * Parameters:
 *      uarray2: address value of uarray object
 *      void (*function)(): void pointer to some function instructions for
 *      the map function to apply to each element
 *              For example: in useuarray2.c they passed check and print to
 *              each element.
 *      bool *OK: a bool pointer representing if an array is valid
 * Return:
 *      nothing
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 *      CRE if passed NULL function pointer
 *      CRE if boolean pointer supplied is NULL
 * Notes:
 *      Boolean is a tracker pointer, which may be altered for error checking
 *      and assertions elsewhere
 ************************/
void UArray2_map_row_major(T uarray2, void (*function)(), bool *OK);

/******** UArray2_map_col_major ********
 *
 * Visit each cell in array via column major order and map according to some 
 * function's instructions. Iterate through each column by checking all rows 
 * before moving onto next column. Under the hood in a 1D array, we will "jump"
 * around in segments of "width" size. Once we have done an iteration "height" 
 * number of times, we will move onto the next column. This subloop will happen
 * a total of "width" times.
 * 
 * Parameters:
 *      uarray2: address value of uarray object
 *      void (*function)(): void pointer to some function instructions for
 *      the map function to apply to each element
 *              For example: in useuarray2.c they passed check and print to
 *              each element.
 *      bool *OK: a bool pointer representing if an array is valid
 * Return: 
 *      nothing
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 *      CRE if passed NULL function pointer
 *      CRE if boolean pointer supplied is NULL
 * Notes:
 *      Boolean is a tracker pointer, which may be altered for error checking
 *      and assertions elsewhere
 ************************/
void UArray2_map_col_major(T uarray2, void (*function)(), bool *OK);

#endif