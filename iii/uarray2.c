/*
 *      uarray2.c
 *      Justin Paik (jpaik03), Alex Violet (aviole01)
 *      September 25, 2025
 *      iii
 * 
 *      Interface for two-dimensional bit arrays
 */

#include "uarray2.h"
#include "assert.h"

#define T UArray2_T

struct T
{
        int width;
        int height;
        int size;
        UArray_T array;
};

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
 *      throws a CRE if malloc fails
 ************************/
T UArray2_new(int width, int height, int size)
{       
        assert(0 <= width && 0 <= height && 0 < size);

        /* Make a UArray object */
        T arr2d = malloc(sizeof(*arr2d));
        assert(arr2d != NULL);

        /* populate struct */
        arr2d->width = width;
        arr2d->height = height;
        arr2d->size = size;
        arr2d->array = UArray_new(width * height, size);

        return arr2d;
}

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
 *      None
 ************************/
void UArray2_free(T *uarray2)
{
        assert(uarray2 != NULL && *uarray2 != NULL);

        /* Free 1D array */
        UArray_free(&(*uarray2)->array);

        /* free actual struct */
        free(*uarray2);
}

/******** UArray2_width ********
 *
 * Return the number of columns of a UArray2
 *
 * Parameters:
 *      uarray2: address value of uarray object
 * Return: 
 *      int representing the number of columns of a UArray2
 * Expects:
 *      uarray2 is not NULL
 * Notes:
 *      none
 ************************/
int UArray2_width(T uarray2)
{
        assert(uarray2 != NULL);

        return uarray2->width;
}

/******** UArray2_height ********
 *
 * Return the number of rows of a UArray2
 *
 * Parameters:
 *      uarray2: address value of uarray object
 * Return: 
 *      int representing the number of rows of a UArray2
 * Expects:
 *      uarray2 is not NULL
 *      CRE if uarray2 is NULL
 * Notes:
 *      none
 ************************/
int UArray2_height(T uarray2)
{
        assert(uarray2 != NULL);

        return uarray2->height;
}

/******** UArray2_size ********
 *
 * Return the number of bytes per unboxed slot
 *
 * Parameters:
 *      uarray2: address value of uarray object
 * Return: 
 *      Return the number of bytes per unboxed slot
 * Expects:
 *      uarray2 is not NULL
 *      CRE if uarray2 is NULL
 * Notes:
 *      none
 ************************/
int UArray2_size(T uarray2)
{
        assert(uarray2 != NULL);

        return uarray2->size;
}

/******** UArray2_at ********
 *
 * Client requests UArray2_at(col, row). Under the hood, we are actually going
 * for 1D Uarray which can be accessed at UArray_at(row * width + col).
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
void *UArray2_at(T uarray2, int col, int row)
{
        assert(uarray2 != NULL && 0 <= col && col < uarray2->width && 0 <= row
                && row < uarray2->height);

        return UArray_at(uarray2->array, row * uarray2->width + col);
}

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
 *      void *cl: closure void pointer to some dependent element within mapping.
 *                To be modular, the parameter is a void pointer so the client 
 *                can give us whatever they want.
 * Return: 
 *      nothing
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 *      CRE if passed NULL function pointer
 *      CRE if void pointer supplied is NULL
 * Notes:
 * 
 ************************/
void UArray2_map_col_major(T uarray2, 
        void apply(int col, int row, T a, void *p1, void *p2), void *cl)
{
        /* Ensure all arguments are not NULL */
        assert(uarray2 != NULL && apply != NULL && cl != NULL);
        
        for (int col = 0; col < uarray2->width; col++) {
                for (int row = 0; row < uarray2->height; row++) {
                        apply(col, row, uarray2, UArray2_at(uarray2, col, row), cl); /* TODO: 80 chars! */
                }
        }
        
}

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
 *      void *cl: closure void pointer to some dependent element within mapping.
 *                To be modular, the parameter is a void pointer so the client 
 *                can give us whatever they want.
 * Return:
 *      nothing
 * Expects:
 *      CRE if uarray2 is NULL (thrown by Hanson)
 *      CRE if passed NULL function pointer
 *      CRE if void pointer supplied is NULL
 * Notes:
 * 
 ************************/
void UArray2_map_row_major(T uarray2, 
        void apply(int col, int row, T a, void *p1, void *p2), void *cl)
{
        /* Ensure all arguments are not NULL */
        assert(uarray2 != NULL && apply != NULL && cl != NULL);
        
        for (int row = 0; row < uarray2->height; row++) {
                for (int col = 0; col < uarray2->width; col++) {
                        apply(col, row, uarray2, UArray2_at(uarray2, col, row), cl); /* TODO: 80 chars! */
                }
        }
}

#undef T