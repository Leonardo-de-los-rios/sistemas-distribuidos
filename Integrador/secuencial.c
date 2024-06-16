#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000
#define TESTS 100

void load(int *array, int iteration)
{
    // Calcular una semilla única basada en el tiempo actual y la iteración
    unsigned int seed = (unsigned int)time(NULL) + iteration;
    srand(seed);

    // Llenar el arreglo con números aleatorios del 0 al 999
    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % N;
    }
}

void max_min(int *array)
{
    int max = array[0];
    int min = array[0];

    for (int i = 1; i < N; i++)
    {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }

    printf("Max: %d, Min: %d\n", max, min);
}

int compare_doubles(const void *a, const void *b)
{
    double arg1 = *(const double *)a;
    double arg2 = *(const double *)b;

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

double median(double *times)
{
    qsort(times, TESTS, sizeof(double), compare_doubles);

    if (TESTS % 2 == 0)
        return (times[TESTS / 2 - 1] + times[TESTS / 2]) / 2;
    else
        return times[TESTS / 2];
}

void test()
{
    int *array = (int *)malloc(N * sizeof(int));
    double *times = (double *)malloc(TESTS * sizeof(double));
    double start, end;

    for (int i = 0; i < TESTS; i++)
    {
        printf("Iteration: %d\n", i);
        load(array, i);

        start = omp_get_wtime();
        max_min(array);
        end = omp_get_wtime();

        times[i] = end - start;
        printf("Time taken: %f seconds\n", times[i]);
    }

    printf("Median time: %f seconds\n", median(times));

    free(array);
    free(times);
}

int main()
{
    test();
    return 0;
}
