#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000
#define TESTS 100
// #define TESTS_PARALLEL 100

void load(int *array, int iteration)
{
    unsigned int seed = (unsigned int)time(NULL) + iteration;
    srand(seed);

    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % N;
    }
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

void find_max_min(int *array, int size, int *global_max, int *global_min, int num_threads)
{
    int local_max, local_min;

    *global_max = array[0];
    *global_min = array[0];

    int base_count = size / num_threads;
    int extra_count = size % num_threads;

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
}

void test(int num_threads, double *times)
{
    int *array = (int *)malloc(N * sizeof(int));
    int global_max, global_min;
    double start, end;

    omp_set_num_threads(num_threads);

    for (int i = 0; i < TESTS; i++)
    {
        printf("Test: %d\n", i + 1);
        load(array, i);

        start = omp_get_wtime();
        find_max_min(array, N, &global_max, &global_min, num_threads);
        end = omp_get_wtime();

        times[i] = end - start;
        printf("Max: %d, Min: %d\n", global_max, global_min);
        printf("Time taken: %f seconds\n", times[i]);
    }

    double median_time = median(times);

    printf("Median time: %f seconds\n", median_time);

    free(array);
}

int main()
{
    int num_threads = 12;

    double *times = (double *)malloc(TESTS * sizeof(double));

    double start = omp_get_wtime();
    test(num_threads, times);
    double end = omp_get_wtime();

    double total_time = end - start;

    double time_parallel = 0.0;

    for (int i = 0; i < TESTS; i++)
    {
        time_parallel += times[i];
    }

    double time_secuencial = total_time - time_parallel;

    printf("------------------------------\n");
    printf("Cantidad de hilos: %d\n", num_threads);
    printf("Total time: %f seconds\n", total_time);
    printf("Time secuencial: %f seconds\n", time_secuencial);
    printf("Time parallel: %f seconds\n", time_parallel);

    return 0;
}