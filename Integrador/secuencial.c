#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

void load(int *array)
{
    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % N;
    }
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
    int global_max, global_min;
    double start, end;

    load(array);

    start = (double)clock() / CLOCKS_PER_SEC;
    find_max_min(array, N, &global_max, &global_min);
    end = (double)clock() / CLOCKS_PER_SEC;

    printf("Max: %d, Min: %d\n", global_max, global_min);
    printf("Time taken: %f seconds\n", end - start);

    free(array);
}

int main()
{
    double start = (double)clock() / CLOCKS_PER_SEC;
    test();
    double end = (double)clock() / CLOCKS_PER_SEC;

    double total_time = end - start;

    double time_parallel = 0.0;

    double time_secuencial = total_time - time_parallel;

    printf("------------------------------\n");
    printf("Ejecución secuencial\n");
    printf("Total time: %f seconds\n", total_time);
    printf("Time secuencial: %f seconds\n", time_secuencial);
    printf("Time parallel: %f seconds\n", time_parallel);
    return 0;
}
