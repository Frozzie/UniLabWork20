#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define TIME_TEST(testCode, time) \
{ \
    clock_t start_time = clock(); \
    testCode \
    clock_t end_time = clock();\
    clock_t sort_time = end_time - start_time; \
    time = (double) sort_time / CLOCKS_PER_SEC; \
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

typedef struct SortFunc 
{
    void    (*sort)(int *a, size_t n);  // указатель на функцию сортировки
    char    name[64];                   // имя сортировки, используемое при выводе
} SortFunc;

typedef struct GeneratingFunc 
{
    void (*generate)(int *a, size_t n); // указатель на функцию генерации последоват.
    char name[64];                      // имя генератора, используемое при выводе
} GeneratingFunc;

double getTime() 
{
    clock_t start_time = clock(); 
        // фрагмент кода
        // время которого измеряется
    clock_t end_time = clock(); 
    clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}

void generateOrderedArray (int *a, size_t n)
{
    for(size_t i = 0; i < n; i++)
    {
        *a++ = i;
    }
}

void generateOrderedBackwards (int *a, size_t n)
{
    for(size_t i = n; i > 0; i--)
    {
        *a++ = i;
    }
}

void generateRandomArray (int *a, size_t n)
{
    srand(0);

    for(size_t i = 0; i < n; i++)
    {
        *a++ = rand();
    }
}

void bubbleSort (int *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        int min = a[i];
        for (size_t j = i + 1; j < n; j++)
        {
            if (min > a[j])
            {
                min = a[j];
            }

            int temp = min;
            min = a[j];
            a[j] = temp;
        }
    }
}

void selectionSort (int *a, size_t n)
{
    for (int i = 1; i < n; i++)
    {
        int newElement = a[i];
        int location = i - 1;

        while(location >= 0 && a[location] > newElement)
        {
            a[location + 1] = a[location];
            location = location - 1;
        }

        a[location + 1] = newElement;
    }
}

void timeExperiment() 
{
    // описание функций сортировки
    SortFunc sorts[] = 
    {
        {bubbleSort, "bubbleSort"},
        {selectionSort, "selectionSort"},
        //{insertionSort, "insertionSort"},
        // вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = 
    {
        // генерируется случайный массив
        {generateRandomArray, "random"},
        // генерируется массив 0, 1, 2, ..., n - 1
        {generateOrderedArray, "ordered"},
        // генерируется массив n - 1, n - 2, ..., 0
        {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) 
    {
        printf("------------------------------\n");
        printf("Size: %d\n", size);
    
        for (int i = 0; i < FUNCS_N; i++) 
        {
            for (int j = 0; j < CASES_N; j++) 
            {
                // генерация имени файла
                static char filename[128];
            
                sprintf(filename, "%s_%s_time",
            
                sorts[i].name, generatingFuncs[j].name);
            
                checkTime(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf("\n");
    }
}

int main() 
{
    timeExperiment();
    
    return 0;
}