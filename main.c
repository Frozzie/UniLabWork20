#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define MAX_BUFFER_SIZE    100000

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

bool isOrdered(int *a, size_t n)
{
    bool answ = true;
    int prev = a[0];

    for(size_t i = 1; i < n; i++)
    {
        if(prev > a[i])
        {
            answ = false;
            break;
        }
        prev = a[i];
    }

    return answ;
}

void outputArray_(int *a, size_t n)
{
    for(size_t i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void outputArrayHex(int *a, size_t n)
{
    for(size_t i = 0; i < n; i++)
    {
        printf("%08X ", a[i]);
    }
    printf("\n");
}

void checkTime (void(*sortFunc)(int *, size_t), 
                void (*generateFunc)(int *, size_t), 
                size_t size, 
                char *experimentName) 
{
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[MAX_BUFFER_SIZE];
    generateFunc(innerBuffer, size);

    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);
    double time;
    TIME_TEST(
    {
        sortFunc(innerBuffer, size);
    }, time);

    printf("Status: ");
    if (isOrdered(innerBuffer, size)) 
    {
        printf("OK! Time: %.3f s.\n", time);

        // запись в файл
        char filename[256];
        // sprintf(filename, "./data/%s.csv", experimentName);
        sprintf(filename, "%s.csv", experimentName);

        FILE *f = fopen(filename, "a");
        if (f == NULL) 
        {
            printf("FileOpenError %s", filename);
            exit(1);
        }

        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } 
    else 
    {
        printf("Wrong!\n");
        // вывод массива, который не смог быть отсортирован
        outputArrayHex(innerBuffer, size);

        exit(1);
    }
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
            if (min < a[j])
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
    // float factor = 1.25;
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

		// step = (size_t)((float)step/factor);
        step--;
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

uint8_t digit(int a, uint8_t n)
{
    uint8_t shift = n * 8;
    return (uint8_t)(a >> shift);
}

void radixSort (int *a, size_t n)
{
    const size_t len = sizeof(int);     // длина числа
    const size_t radix = 256;           // количество чисел в разряде 2^8 // основание системы счисления
    uint8_t d;
    int *b = malloc(sizeof(int) * radix),       // число чисел в корзине
        *c = malloc(sizeof(int) * radix * n);   // корзины для сортировки radix

    for (size_t i = 0; i < len; i++)  // перебираем все разряды, начиная с нулевого
    {        
        for (size_t j = 0; j < radix; j++)
        {                      
            b[j] = 0; // пустой массив корзин
        }

        for (size_t j = 0; j < n; j++)
        {
            int val = a[i];
            d = digit(val, i);              // получаем цифру, стоящую на текущем разряде в каждом числе массива
            int index = (d * n) + b[d];     // индекс записи
            c[index] = val;                 // отправляем число в промежуточный массив в корзину, которая совпадает со значением этой цифры
            b[d]++;                         // добавляем число чисел в корзине
        }

        size_t count = 0;
        
        // сложим обратно числа из корзин в массив a
        for (size_t j = 0; j < radix; j++)
        {
            int k = 0;
            int bj = b[j];
            while (k < bj)
            {
                a[count++] = c[(j * n) + k];
                k++;
            }
        }
    }
    free(b);
    free(c);
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

    // запись статистики в файл up to MAX_BUFFER_SIZE
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
            
                sprintf (filename, "%s_%s_time", sorts[i].name, generatingFuncs[j].name);
            
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