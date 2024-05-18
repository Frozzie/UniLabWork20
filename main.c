#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "matrix.h"
#include "string_.h"

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
    freeMemMatrix(&mat);
    free(a);
}

void Task2 (size_t max_row, size_t max_col, int *a)
{
    matrix mat, mat_answ;
    mat = createMatrixFromArray(a, max_row, max_col);
    mat_answ = createMatrixFromArray(a, max_row, max_col);

    for(size_t row = 0; row < max_row; row++)
    {
        for(size_t col = 0; col < max_col; col++)
        {
            int sum_of_living_near = 0;
            
            int sur_col, sur_row;
            
            sur_row = row - 1;
            sur_col = col - 1;
            if(sur_col >= 0 && sur_row >= 0 && sur_col < max_col && sur_row < max_row)
            {
                sum_of_living_near += getElementMatrix(&mat, sur_row, sur_col);
            }

            sur_row = row - 1;
            sur_col = col;
            if(sur_col >= 0 && sur_row >= 0 && sur_col < max_col && sur_row < max_row)
            {
                sum_of_living_near += getElementMatrix(&mat, sur_row, sur_col);
            }
            
            sur_row = row - 1;
            sur_col = col + 1;
            if(sur_col >= 0 && sur_row >= 0 && sur_col < max_col && sur_row < max_row)
            {
                sum_of_living_near += getElementMatrix(&mat, sur_row, sur_col);
            }
            
            sur_row = row;
            sur_col = col - 1;
            if(sur_col >= 0 && sur_row >= 0 && sur_col < max_col && sur_row < max_row)
            {
                sum_of_living_near += getElementMatrix(&mat, sur_row, sur_col);
            }
            
            sur_row = row;
            sur_col = col + 1;
            if(sur_col >= 0 && sur_row >= 0 && sur_col < max_col && sur_row < max_row)
            {
                sum_of_living_near += getElementMatrix(&mat, sur_row, sur_col);
            }
            
            sur_row = row + 1;
            sur_col = col - 1;
            if(sur_col >= 0 && sur_row >= 0 && sur_col < max_col && sur_row < max_row)
            {
                sum_of_living_near += getElementMatrix(&mat, sur_row, sur_col);
            }
            
            sur_row = row + 1;
            sur_col = col;
            if(sur_col >= 0 && sur_row >= 0 && sur_col < max_col && sur_row < max_row)
            {
                sum_of_living_near += getElementMatrix(&mat, sur_row, sur_col);
            }
            
            sur_row = row + 1;
            sur_col = col + 1;
            if(sur_col >= 0 && sur_row >= 0 && sur_col < max_col && sur_row < max_row)
            {
                sum_of_living_near += getElementMatrix(&mat, sur_row, sur_col);
            }
            
            if(getElementMatrix(&mat, row, col) == 1)
            {
                if(sum_of_living_near < 2 || sum_of_living_near > 3)
                {
                    putElementMatrix(&mat_answ, row, col, 0);
                }
            }
            else
            {
                if(sum_of_living_near == 3)
                {
                    putElementMatrix(&mat_answ, row, col, 1);
                }
            }
        }
    }

    outputMatrix(&mat_answ);

    freeMemMatrix(&mat);
    freeMemMatrix(&mat_answ);
}

void shellSort (int *a, size_t n)
{
    for (int s = n / 2; s > 0; s /= 2) 
    {
        for (int i = s; i < n; ++i) 
        {
            for (int j = i - s; j >= 0 && a[j] > a[j + s]; j -= s) 
            {
                int temp = a[j];
                a[j] = a[j + s];
                a[j + s] = temp;
            }
        }
    }
}

int median (int *arr, size_t n)
{
    shellSort(arr, n);
    int ret;

    if(n % 2 == 0)
    {
        ret = (arr[n/2] + arr[n/2 + 1]) / 2;
    }
    else
    {
        ret = arr[n/2];
    }

    return ret;
}

void Task3 (size_t n, matrix mat)
{
    int border = n / 2;
    int *arr = malloc(sizeof(int) * n * n);

    for(int i = border; i < mat.nRows - border; i++)
    {
        for(int j = border; j < mat.nCols - border; j++)
        {   
            int count = 0;
            for(int k = i - border; k <= i + border; k++)
            {
                for(int s = j - border; s <= j + border; s++)
                {
                    arr[count++] = getElementMatrix(&mat, k, s);
                }
            }

            int med = median(arr, n * n);
            putElementMatrix(&mat, i, j, med);
        }
    }

    free(arr);

    outputMatrix(&mat);
}

void subTask4(char *str)
{
    char *first_space = findSpace(str);
    first_space++;

    char *num = malloc(strlen(str));
    char *words_begin = copy(str, first_space, num);
    num[first_space - str] = 0;

    BagOfWords words;
    getBagOfWords(&words, first_space);

    for(int i = 0; i < words.size; i++)
    {
        printf("%s", num);
        for(int j = i; j < words.size; j++)
        {
            printWord(words.words[j]);
            if(j < words.size - 1)
            {
                printf(".");
            }
        }

        printf("\n");
    }
    printf("\n");

    free(num);
}

void Task4(char **arrStr, size_t n)
{
    for(size_t i = 0; i < n; i++)
    {
        subTask4(arrStr[i]);
    }
}
int main()
{
    int n = 3, qn = 2;
    int a[] = {
        0,1,0,
        0,0,1,
        1,1,1,
        0,0,0
    };
    query_t query[2] = {{1,1,2,2},{0,0,1,1}};
    
    int b[] = {
        10, 20, 30,
        25, 35, 45,
        15, 25, 35
    };
    matrix mat1 = createMatrixFromArray(b, 3, 3);
    
    char c2[] = {"900 google.mail.com\0"};
    char c3[] = {"50 yahoo.com\0"};
    char c4[] = {"1 intel.mail.com\0"};
    char c5[] = {"5 wiki.org\0"};

    char *arr[] = {c2, c3, c4, c5};
    size_t arr_n = sizeof(arr) / sizeof(*arr);

    Task1(n, query, qn);
    printf("\n");

    Task2(4, 3, a);
    printf("\n");

    Task3(3, mat1);
    printf("\n");

    Task4(arr, arr_n);

    freeMemMatrix(&mat1);
}