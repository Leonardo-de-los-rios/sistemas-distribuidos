#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define N 100000

void load(int *array)
{
    srand(time(NULL));

    // Llenar el arreglo con números aleatorios del 0 al 999
    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % 1000;
    }
}

void partition_data(int size, int rank, int *array, int *local_n, int **local_array, int **sendcounts, int **displs)
{
    int base_count = N / size;
    int extra_count = N % size;

    *local_n = base_count + (rank < extra_count ? 1 : 0);
    *local_array = (int *)malloc(*local_n * sizeof(int));

    *sendcounts = (int *)malloc(size * sizeof(int));
    *displs = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        (*sendcounts)[i] = base_count + (i < extra_count ? 1 : 0);
        (*displs)[i] = (i == 0) ? 0 : (*displs)[i - 1] + (*sendcounts)[i - 1];
    }

    printf("Rank: %d, sendcounts: %d, displs: %d\n", rank, (*sendcounts)[rank], (*displs)[rank]);

    MPI_Scatterv(array, *sendcounts, *displs, MPI_INT, *local_array, *local_n, MPI_INT, 0, MPI_COMM_WORLD);
}

void max_min(int *local_array, int local_n, int rank)
{
    int local_max = local_array[0];
    int local_min = local_array[0];

    int global_max, global_min;
    double start = MPI_Wtime();

    for (int i = 1; i < local_n; i++)
    {
        if (local_array[i] > local_max)
            local_max = local_array[i];
        if (local_array[i] < local_min)
            local_min = local_array[i];
    }

    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();
    if (rank == 0)
    {
        double time_taken = end - start;
        printf("Max: %d, Min: %d\n", global_max, global_min);
        printf("Time taken: %f seconds\n", time_taken);
    }
}

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *array = NULL;
    if (rank == 0)
    {
        array = (int *)malloc(N * sizeof(int));
        load(array);
    }

    int local_n;
    int *local_array;
    int *sendcounts;
    int *displs;

    partition_data(size, rank, array, &local_n, &local_array, &sendcounts, &displs);
    max_min(local_array, local_n, rank);

    if (rank == 0)
    {
        free(array);
    }

    free(local_array);
    free(sendcounts);
    free(displs);
    MPI_Finalize();
    return 0;
}
