#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define N 100000000

void load(int *array)
{
    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % N;
    }
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

void test(int rank, int size, double *time_secuencial)
{
    int *array = NULL;
    double start_test, end_test, start_sec, end_sec;
    int local_max, local_min;
    int global_max, global_min;

    if (rank == 0)
    {
        start_sec = MPI_Wtime();

        array = (int *)malloc(N * sizeof(int));
        end_sec = MPI_Wtime();

        *time_secuencial = end_sec - start_sec;
    }

    int base_count = N / size;
    int extra_count = N % size;
    int sub_array_size = (rank < extra_count) ? base_count + 1 : base_count;
    int *sub_array = (int *)malloc(sub_array_size * sizeof(int));

    if (rank == 0)
    {
        start_sec = MPI_Wtime();
        load(array);
        end_sec = MPI_Wtime();
        *time_secuencial += (end_sec - start_sec);
    }

// TODO: analizar si tiene que hacerlo el rank 0
    start_test = MPI_Wtime();

    int *send_counts = NULL;
    int *displs = NULL;
    if (rank == 0)
    {
        start_sec = MPI_Wtime();
        send_counts = (int *)malloc(size * sizeof(int));
        displs = (int *)malloc(size * sizeof(int));
        int offset = 0;
        for (int j = 0; j < size; j++)
        {
            send_counts[j] = (j < extra_count) ? base_count + 1 : base_count;
            displs[j] = offset;
            offset += send_counts[j];
        }
        end_sec = MPI_Wtime();

        *time_secuencial += (end_sec - start_sec);
    }

    MPI_Scatterv(array, send_counts, displs, MPI_INT, sub_array, sub_array_size, MPI_INT, 0, MPI_COMM_WORLD);

    find_max_min(sub_array, sub_array_size, &local_max, &local_min);

    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    end_test = MPI_Wtime();

    if (rank == 0)
    {
        start_sec = MPI_Wtime();
        double time_parallel = end_test - start_test;
        printf("Max: %d, Min: %d\n", global_max, global_min);
        printf("Time taken: %f seconds\n", time_parallel);

        free(array);
        free(send_counts);
        free(displs);
        end_sec = MPI_Wtime();

        *time_secuencial += (end_sec - start_sec);
    }

    free(sub_array);
}

int main(int argc, char *argv[])
{
    double start, end, time_secuencial;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        start = (double)clock() / CLOCKS_PER_SEC;
    }

    test(rank, size, &time_secuencial);
    MPI_Finalize();

    if (rank == 0)
    {
        end = (double)clock() / CLOCKS_PER_SEC;

        double total_time = end - start;

        double time_parallel = total_time - time_secuencial;

        printf("------------------------------\n");
        printf("Cantidad de procesos: %d\n", size);
        printf("Total time: %f seconds\n", total_time);
        printf("Time secuencial: %f seconds\n", time_secuencial);
        printf("Time parallel: %f seconds\n", time_parallel);
    }

    return 0;
}
