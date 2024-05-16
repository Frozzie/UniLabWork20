/******************************************************************************
 * @file matrix.h
 * @author Yakov Petrukhin (yasha.petrukhin@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
******************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct matrix 
{
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position 
{
    int rowIndex;
    int colIndex;
} position;

matrix   getMemMatrix                            (int nRows, int nCols);
void     freeMemMatrix                           (matrix *m);
matrix  *getMemArrayOfMatrices                   (int nMatrices, int nRows, int nCols);
void     freeMemMatrices                         (matrix *ms, int nMatrices);
void     inputMatrix                             (matrix *m);
void     outputMatrix                            (matrix *m);
void     inputMatrices                           (matrix *ms, int nMatrices);
void     outputMatrices                          (matrix *ms, int nMatrices);
void     swapRows                                (matrix *m, int i1, int i2);
void     swapColumns                             (matrix *m, int j1, int j2);
void     insertionSortRowsMatrixByRowCriteria    (matrix *m, int (*criteria)(int*, int));
int      getSum                                  (int *a, int n);
void     selectionSortColsMatrixByColCriteria    (matrix *m, int (*criteria)(int*, int));
void     getMatrixColumn                         (matrix *m, int num, int *column);
bool     isSquareMatrix                          (matrix *m);
bool     areTwoMatricesEqual                     (matrix *m1, matrix *m2);
bool     isEMatrix                               (matrix *m);
bool     isSymmetricMatrix                       (matrix *m);
int      getElementMatrix                        (matrix *m, int i, int j);
void     putElementMatrix                        (matrix *m, int i, int j, int val);
void     transposeSquareMatrix                   (matrix *m);
void     transposeMatrix                         (matrix *m);
position getMinValuePos                          (matrix *m);
matrix   createMatrixFromArray                   (const int *a, int nRows, int nCols);
matrix  *createArrayOfMatrixFromArray            (const int *values, int nMatrices, int nRows, int nCols);
#endif // MATRIX_H