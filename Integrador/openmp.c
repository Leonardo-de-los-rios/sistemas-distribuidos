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

int set_threads(int *array, int num_threads)
{
    printf("Ingrese la cantidad de hilos: ");
    if (scanf("%d", &num_threads) != 1)
    {
        fprintf(stderr, "Error al leer el número de hilos\n");
        free(array);
        return 1;
    }

    return num_threads;
}

void max_min(int *array, int num_threads)
{
    double start, end;

    omp_set_num_threads(num_threads);

    int base_count = N / num_threads;
    int extra_count = N % num_threads;

    int max = array[0];
    int min = array[0];

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int local_max, local_min;
        int start_index = tid * base_count + (tid < extra_count ? tid : extra_count);
        int end_index = start_index + base_count + (tid < extra_count ? 1 : 0);

        local_max = array[start_index];
        local_min = array[start_index];

#pragma omp critical
        {
            start = omp_get_wtime();
        }

        for (int i = start_index + 1; i < end_index; i++)
        {
            if (array[i] > local_max)
                local_max = array[i];
            if (array[i] < local_min)
                local_min = array[i];
        }

#pragma omp critical
        {
            if (local_max > max)
                max = local_max;
            if (local_min < min)
                min = local_min;
        }
    }

    end = omp_get_wtime();
    double time_taken = end - start;

    printf("Max: %d, Min: %d\n", max, min);
    printf("Time taken: %f seconds\n", time_taken);
}

int main()
{
    int *array = (int *)malloc(N * sizeof(int));

    load(array);

    int num_threads = set_threads(array, num_threads);

    max_min(array, num_threads);

    free(array);
    return 0;
}
