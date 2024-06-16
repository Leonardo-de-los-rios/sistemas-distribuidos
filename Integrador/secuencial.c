#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000
#define TESTS 100

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

void find_max_min(int *array, int size, int *global_max, int *global_min)
{
    *global_max = array[0];
    *global_min = array[0];

    for (int i = 1; i < size; i++)
    {
        if (array[i] > *global_max)
            *global_max = array[i];
        if (array[i] < *global_min)
            *global_min = array[i];
    }
}

void test()
{
    int *array = (int *)malloc(N * sizeof(int));
    double *times = (double *)malloc(TESTS * sizeof(double));
    int global_max, global_min;
    double start, end;

    for (int i = 0; i < TESTS; i++)
    {
        printf("Iteration: %d\n", i);
        load(array, i);

        start = (double)clock() / CLOCKS_PER_SEC;
        find_max_min(array, N, &global_max, &global_min);
        end = (double)clock() / CLOCKS_PER_SEC;

        times[i] = end - start;
        printf("Max: %d, Min: %d\n", global_max, global_min);
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
