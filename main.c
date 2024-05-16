#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "matrix.h"

typedef struct _query
{
    size_t row1;
    size_t col1;
    size_t row2;
    size_t col2;
} query_t;

void Task1 (size_t n, query_t *query, size_t qn)
{
    matrix mat;
    int *a = malloc(sizeof(int) * n * n);
    memset(a, 0, sizeof(int) * n * n);
    mat = createMatrixFromArray(a, n, n);
    
    for(size_t i = 0; i < qn; i++)
    {
        for(size_t j = query[i].row1; j <= query[i].row2; j++)
        {
            for(size_t k = query[i].col1; k <= query[i].col2; k++)
            {
                int num = getElementMatrix(&mat, j, k);
                putElementMatrix(&mat, j, k, num + 1);
            }
        }
    }

    outputMatrix(&mat);
}

int main() 
{
    int n = 3, qn = 2;

    query_t query[2] = {{1,1,2,2},{0,0,1,1}};
    
    Task1(n, query, qn);
}