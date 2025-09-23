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

#define T2 UArray2_T

typedef struct T2 *T2;

/******** UArray2_new ********
 *
 * Allocates space for a UArray2 if width and height are non-negative and size
 * is positive.
 *
 * Parameters:
 *      int width: the width of the array to be created
 *      int height: the height of the array to be created
 *      int size: the number of bytes per cell in the array
 * Return: 
 *      a struct pointer to the instance of the new UArray
 * Expects:
 *      width and height are nonnegative
 *      size is positive
 *      throws a CRE if an invalid input is given
 * Notes:
 *      None
 ************************/
T2 UArray2_new(int width, int height, int size);

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
void UArray2_free(T2 *uarray2);

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
int UArray2_width(T2 uarray2);

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
int UArray2_height(T2 uarray2);

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
int UArray2_size(T2 uarray2);

/******** UArray2_at ********
 *
 * Client requests UArray2_at(col, row). Returns void pointer to memory located 
 * at arr[col][row].
 *
 * Parameters:
 *      uarray2: address value of uarray object
 *      int col: the col of the requested cell
 *      int row: the row of the requested cell
 * Return: 
 *      void pointer to value stored at (col, row) 2D or (row * width + col) 1D
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 *      col and row are within [0, width - 1] and [0, height - 1] respectively
 * Notes:
 *      none
 ************************/
 void *UArray2_at(T2 uarray2, int col, int row);
 
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
 *      void *cl: void pointer to some dependent element within mapping. To be 
 *                modular, the parameter is a void pointer so the client can 
 *                give us whatever they want.
 * Return: 
 *      nothing
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 *      CRE if passed NULL function pointer
 *      CRE if void pointer supplied is NULL
 * Notes:
 *      Boolean is a tracker pointer, which may be altered for error checking
 *      and assertions elsewhere
 ************************/
 void UArray2_map_col_major(T2 uarray2, void *function, void *cl);

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
 *      void *cl: void pointer to some dependent element within mapping. To be 
 *                modular, the parameter is a void pointer so the client can 
 *                give us whatever they want.
 * Return:
 *      nothing
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 *      CRE if passed NULL function pointer
 *      CRE if void pointer supplied is NULL
 * Notes:
 *      Boolean is a tracker pointer, which may be altered for error checking
 *      and assertions elsewhere
 ************************/
void UArray2_map_row_major(T2 uarray2, void *function, void *cl);

#undef T2
#endif