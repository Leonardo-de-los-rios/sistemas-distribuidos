#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000

void load(int *array)
{
    srand(time(NULL));

    // Llenar el arreglo con números aleatorios del 0 al 999
    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % 1000;
    }
}

void max_min(int *array)
{
    int max = array[0];
    int min = array[0];

    double start = omp_get_wtime();

    for (int i = 1; i < N; i++)
    {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }

    double end = omp_get_wtime();
    double time_taken = end - start;

    printf("Max: %d, Min: %d\n", max, min);
    printf("Time taken: %f seconds\n", time_taken);
}

int main()
{
    int *array = (int *)malloc(N * sizeof(int));

    load(array);
    max_min(array);

    free(array);
    return 0;
}
