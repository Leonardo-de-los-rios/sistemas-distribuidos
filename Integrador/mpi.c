#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

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

void find_max_min(int *array, int size, int *local_max, int *local_min)
{
    *local_max = array[0];
    *local_min = array[0];

    for (int i = 1; i < size; i++)
    {
        if (array[i] > *local_max)
            *local_max = array[i];
        if (array[i] < *local_min)
            *local_min = array[i];
    }
}

void test(int rank, int size)
{
    int *array = NULL;
    int *sub_array = NULL;
    double *times = NULL;
    double start, end;

    if (rank == 0)
    {
        array = (int *)malloc(N * sizeof(int));
        times = (double *)malloc(TESTS * sizeof(double));
    }

    int base_count = N / size;
    int extra_count = N % size;
    int sub_array_size = (rank < extra_count) ? base_count + 1 : base_count;
    sub_array = (int *)malloc(sub_array_size * sizeof(int));

    for (int i = 0; i < TESTS; i++)
    {
        if (rank == 0)
        {
            printf("Iteration: %d\n", i);
            load(array, i);
        }

        int *send_counts = NULL;
        int *displs = NULL;
        if (rank == 0)
        {
            send_counts = (int *)malloc(size * sizeof(int));
            displs = (int *)malloc(size * sizeof(int));
            int offset = 0;
            for (int j = 0; j < size; j++)
            {
                send_counts[j] = (j < extra_count) ? base_count + 1 : base_count;
                displs[j] = offset;
                offset += send_counts[j];
            }
        }

        MPI_Scatterv(array, send_counts, displs, MPI_INT, sub_array, sub_array_size, MPI_INT, 0, MPI_COMM_WORLD);

        start = MPI_Wtime();

        int local_max, local_min;
        find_max_min(sub_array, sub_array_size, &local_max, &local_min);

        int global_max, global_min;
        MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
        MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

        end = MPI_Wtime();

        if (rank == 0)
        {
            times[i] = end - start;
            printf("Max: %d, Min: %d\n", global_max, global_min);
            printf("Time taken: %f seconds\n", times[i]);

            free(send_counts);
            free(displs);
        }
    }

    if (rank == 0)
    {
        printf("Median time across processes: %f seconds\n", median(times));
        free(array);
        free(times);
    }

    free(sub_array);
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    test(rank, size);

    MPI_Finalize();
    return 0;
}
