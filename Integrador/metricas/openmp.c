#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 100000000

void load(int *array)
{
    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % N;
    }
}


double find_max_min(int *array, int size, int *global_max, int *global_min, int num_threads)
{
    int local_max, local_min;
    double start, end;

    *global_max = array[0];
    *global_min = array[0];

    int base_count = size / num_threads;
    int extra_count = size % num_threads;

    start = omp_get_wtime();
#pragma omp parallel private(local_max, local_min)
    {
        int tid = omp_get_thread_num();
        int start_index = tid * base_count + (tid < extra_count ? tid : extra_count);
        int end_index = start_index + base_count + (tid < extra_count ? 1 : 0);

        local_max = array[start_index];
        local_min = array[start_index];

        // Buscar el máximo y mínimo localmente
        for (int i = start_index + 1; i < end_index; i++)
        {
            if (array[i] > local_max)
                local_max = array[i];
            if (array[i] < local_min)
                local_min = array[i];
        }

        // Buscar el máximo y mínimo globalmente
#pragma omp critical
        {
            if (local_max > *global_max)
                *global_max = local_max;
            if (local_min < *global_min)
                *global_min = local_min;
        }
    }
    end = omp_get_wtime();

    return end - start;
}

double test(int num_threads)
{
    int *array = (int *)malloc(N * sizeof(int));
    int global_max, global_min;

    load(array);

    double time_parallel = find_max_min(array, N, &global_max, &global_min, num_threads);

    printf("Max: %d, Min: %d\n", global_max, global_min);
    printf("Time taken: %f seconds\n", time_parallel);

    free(array);

    return time_parallel;
}

int main()
{
    double start = omp_get_wtime();
    int num_threads = 6;

    omp_set_num_threads(num_threads);

    double time_parallel = test(num_threads);
    double end = omp_get_wtime();

    double total_time = end - start;

    double time_secuencial = total_time - time_parallel;

    printf("------------------------------\n");
    printf("Cantidad de hilos: %d\n", num_threads);
    printf("Total time: %f seconds\n", total_time);
    printf("Time secuencial: %f seconds\n", time_secuencial);
    printf("Time parallel: %f seconds\n", time_parallel);

    return 0;
}
