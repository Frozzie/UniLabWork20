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

void checkTime (void(*sortFunc)(int *, size_t), 
                void (*generateFunc)(int *, size_t), 
                size_t size, 
                char *experimentName) 
{
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);

    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);
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

void insertionSort (int *a, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        int minPosition = i;

        for (int j = i + 1; j < n; j++)
        {
            if (a[minPosition] > a[j])
            {
                minPosition = j;
            }
        }

        int tmp = a[minPosition];
        a[minPosition] = a[i];
        a[i] = tmp;
    }
}

void brushSort (int *a, size_t n)
{
    float factor = 1.25;
	size_t step = n - 1;
    
	while (step >= 1)
	{
		for (size_t i = 0; i + step < n; i++)
		{
			if (a[i] > a[i + step])
			{
				int temp = a[i];
                a[i] = a[i + step];
                a[i + step] = temp;
			}
		}

		step = (size_t)((float)step/factor);
	}
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

void radixSort (int *a, size_t n)
{
    const size_t k = 4;
    uint8_t d;
    int *b = malloc(sizeof(int) * n),
        *c = malloc(sizeof(int) * n);

    for (size_t i = 1; i < k; i++)
    {        
        for (size_t j = 0; j < k - 1; j++)
        {                      
            c[j] = 0;
        }

        for (size_t j = 0; j < n - 1; j++)
        {
            d = digit(a[j], i);
            c[d]++;
        }
        int count = 0;
        
        for (size_t j = 0; j < k - 1; j++)
        {
            int tmp = c[j];
            c[j] = count;
            count += tmp;
        }

        for (size_t j = 0; j < n - 1; j++)
        {
            d = digit(a[j], i);
            b[c[d]] = a[j];
            c[d]++;
        }
        memcpy(a, b, n);

    }
}

void timeExperiment() 
{
    // описание функций сортировки
    SortFunc sorts[] = 
    {
        {bubbleSort, "bubbleSort"},
        {selectionSort, "selectionSort"},
        {insertionSort, "insertionSort"},
        {brushSort, "brushSort"},
        {shellSort, "shellSort"},
        {radixSort, "radixSort"}
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