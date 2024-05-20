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

#define MAX_ROWS 30
#define MAX_STR_LEN 50
typedef struct _mylink
{
    int count;
    char str[MAX_STR_LEN];
} mylink;

void Task4(char **arrStr, size_t n)
{
    mylink arr_link[MAX_ROWS];
    size_t link_size = 0;
    char *str;
    char *str_char;

    // all input strings
    for(size_t i = 0; i < n; i++)
    {
        str = arrStr[i];                    // pointer to current string
        str_char = findSpace(str);          // p after num
        

        while(*str_char > 0)
        {
            str_char = findNonSpace(str_char);  // p to next word
            strcpy(arr_link[link_size].str, str_char);  // save string to array
            arr_link[link_size].count = atoi(str);      // save counter to array
            bool flag = false;                          // find the same string

            for (size_t n = 0; n < link_size; n++)      // check all prev words in array
            {
                if (strcmp (arr_link[n].str, arr_link[link_size].str) == 0)
                {
                    flag = true;
                    arr_link[n].count += arr_link[link_size].count;
                    break;
                }
            }

            if (!flag) // string new - save string
            {
                link_size++;
            }

            str_char = findSpace(str_char);  // next word in string
        }
    }

    // print all strings from array
    for (size_t i = 0; i < link_size; i++)
    {
        printf ("%d %s\n", arr_link[i].count, arr_link[i].str);
    }
}

bool isMatrixCont0 (matrix *mat, size_t x0, size_t y0, size_t x_size, size_t y_size)
{
    bool answ = false;
    for(size_t x = x0; x < x0 + x_size; x++)
    {
        for(size_t y = y0; y < y0 + y_size; y++)
        {
            if(getElementMatrix(mat, x, y) == 0)
            {
                answ = true;
                break;
            }
        }

        if(answ)
        {
            break;
        }
    }

    return answ;
}

int countOfFittingMatrices (matrix *mat, size_t x_size, size_t y_size)
{
    int answ = 0;

    for(size_t row = 0; row <= mat->nRows - y_size; row++)
    {
        for(size_t col = 0; col <= mat->nCols - x_size; col++)
        {
            if(!isMatrixCont0(mat, col, row, x_size, y_size))
            {
                answ++;
            }
        }
    }

    return answ;
}

void Task5(matrix *mat)
{
    int count = 0;
    for(size_t row = 1; row <= mat->nRows; row++)
    {
        for(size_t col = 1; col <= mat->nCols; col++)
        {
            count += countOfFittingMatrices(mat, col, row);
        }
    }

    printf("%d", count);
}

typedef struct numbers
{
    int num;
    bool present;
} numbers;

// return 0 if false
int getInc (numbers *num, int cur_num)
{

}

int getDec (numbers *num, int cur_num)
{

}

void Task6(char *str)
{
    size_t size = strlen1(str);

    char *order = malloc(sizeof(char) * (size + 2));
    char *answ = malloc(sizeof(char) * (size + 1) + 1);
    answ[size + 1] = 0;

    for(size_t i = 0; i < 9; i++)
    {
        order[i] = '1' + i;
    }
    order[9] = 0;
    size_t start = 10, end = 10, rev = 10;
    size_t i;

    for( i = 0; i < size; i++)
    {
        int mem_id;

        if(str[i] == 'I')
        {
            if(i == end)
            {
                answ[i] = order[start];

                if(rev > 0)
                {
                    rev--;
                }
            }
            else
            {
                answ[i] = order[i];
            }
        }
        else // Нашли D
        {
            if(i < start || i > end)
            {
                size_t index = 0;
                start = i;

                while(str[i + index] == 'D')
                {
                    index++;
                }
                end = i + index;

                answ[i] = order[end];
                rev = end - 1;
            }
            else
            {
                answ[i] = order[rev--];
            }
        }
    }
    answ[i] = order[rev];

    printf("%s", answ);
    free(order);
}

typedef struct rec_arr
{
    int     *arr;
    int     val;
    size_t  n;
    size_t  level;
    void    *l;
    void    *r;
} rec_arr;

void recursive_push (rec_arr *t)
{
    if (t->n > 0)
    {
        size_t i_max = 0;
        
        for(size_t i = 0; i < t->n; i++)
        {
            if(t->arr[i] >= t->arr[i_max])
            {
                i_max = i;
                t->val = t->arr[i];
            }
        }

        size_t left_size = i_max;
        size_t right_size = t->n - i_max - 1;

        t->l = malloc (sizeof(rec_arr));
        rec_arr *left = (rec_arr *)t->l;
        left->arr = malloc (sizeof(int) * left_size);
        memcpy (left->arr, t->arr, sizeof(int) * left_size);
        left->n = left_size;
        left->level = t->level + 1;
        recursive_push (left);

        t->r = malloc (sizeof(rec_arr));
        rec_arr *right = (rec_arr *)t->r;
        right->arr = malloc (sizeof(int) * right_size);
        right->n = right_size;
        memcpy (right->arr, &t->arr[i_max + 1], sizeof(int) * right_size);
        right->level = t->level + 1;
        recursive_push (right);
    }
    else
    {
        t->l = NULL;
        t->r = NULL;
        t->val = INT32_MAX;
    }
}

bool print_level (rec_arr *t, int level)
{
    bool ret = false;
    bool ret_l;
    bool ret_r;

    if (t != NULL)
    {
        if (t->level == level)
        {
            if (t->val == INT32_MAX)
            {
                printf ("null,");
            }
            else
            {
                printf ("%d,", t->val);
                ret = true;
            }  
        }
        else if (t->n > 1)
        {
            ret_l = print_level (t->l, level);
            ret_r = print_level (t->r, level);
            ret = ret_l || ret_r;
        }
    }

    return ret;
}



void Task7(int *arr, size_t n)
{
    rec_arr t;
    t.arr = malloc (sizeof(int) * n);
    memcpy (t.arr, arr, sizeof(int) * n);
    t.n = n;
    t.level = 0;
    t.l = NULL;
    t.r = NULL;
    recursive_push (&t);

    // print tree from zero level
    int level = 0;
    bool level_flag = true;
    while (level_flag)
    {
	    level_flag = print_level (&t, level);
        level++;
        // printf ("\n");
    }
    printf ("\n");
    free (t.arr);
}

void Task8 (char *str, int *arr)
{
    size_t size = strlen(str);
    char *output = malloc(sizeof(char) * size);

    for(size_t i = 0; i < size; i++)
    {
        output[i] = str[arr[i]];
    }

    output[size] = 0;

    printf("%s\n", output);
}

void Task9(int argc, char **argv)
{
    if (argc != 4) 
    {
        printf ("Error: found %d arguments. Needs exactly 3", argc - 1);
        return;
    }
    char *fileIn = malloc(strlen(argv[0])); // first argument is file name in
    strcpy(fileIn, argv[1]);

    char *fileOut = malloc(strlen(argv[1])); // second argument is file name out
    strcpy(fileOut, argv[2]);

    int max_num = atoi(argv[3]); // third argument is max num

    FILE *fIn = fopen(fileIn, "r");
    FILE *fOut = fopen(fileOut, "w");

    if (fIn == NULL || fOut == NULL)
    {
        printf("ERROR\n");
    }
    else
    {
        int num;
        char buf[50];
        while (fscanf (fIn, "%s ", buf) > 0)
        {
            num = atoi (buf);

            if(num < max_num)
            {
                fprintf (fOut, "%d ", num);
            }
        }
    }

    fclose(fIn);
    fclose(fOut);
}

int main(int argc, char **argv)
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

    int task5_data[] = {
        1, 0, 1,
        1, 1, 0,
        1, 1, 0
    };
    matrix Task5_m = createMatrixFromArray(task5_data, 3, 3);

    char task6_str1[] = {"IIIDIDDD"};
    char task6_str2[] = {"DDD"};
    
    int task7a_arr[] = {3, 2, 1, 6, 0, 5};
    int task7b_arr[] = {3, 2, 1};

    char task8A_str[] = {"abc"};
    int task8A_arr[3] = {0, 1, 2};
    char task8B_str[] = {"abap"};
    int task8B_arr[4] = {0, 3, 2, 1};
    printf("Task 1: \n");
    Task1(n, query, qn);
    printf("\n");

    printf("Task 2: \n");
    Task2(4, 3, a);
    printf("\n");

    printf("Task 3: \n");
    Task3(3, mat1);
    printf("\n");

    printf("Task 4: \n");
    Task4(arr, arr_n);
    printf("\n");

    printf("Task 5: \n");
    Task5(&Task5_m);
    printf("\n \n");

    printf("Task 6: \n");
    Task6(task6_str1);
    printf("\n");
    Task6(task6_str2);
    printf("\n\n");

    printf("Task 7: \n");
    size_t size = sizeof (task7a_arr) / sizeof (int);
    Task7(task7a_arr, size);
    size = sizeof (task7b_arr) / sizeof (int);
    Task7(task7b_arr, size);

    printf("\n");

    printf("Task 8: \n");
    Task8(task8A_str, task8A_arr);
    Task8(task8B_str, task8B_arr);
    printf("\n");

    printf("Task 9: \n");
    Task9(argc, argv);
    freeMemMatrix(&mat1);
    freeMemMatrix(&Task5_m);
}