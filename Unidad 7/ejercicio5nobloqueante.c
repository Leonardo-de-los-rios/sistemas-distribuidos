#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
    int rank, size;
    clock_t start, end;
    double cpu_time_used;

    MPI_Init(&argc, &argv);
    start = clock();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    float dato = 3.5;
    MPI_Request request;
    MPI_Status status;

    if (rank == 0)
    {
        MPI_Isend(&dato, 1, MPI_FLOAT, rank + 1, 0, MPI_COMM_WORLD, &request); // Envío no bloqueante
        printf("Proceso 0 inició el envío del mensaje %f\n", dato);

        int result_p0 = 0;
        for (int i = 0; i < 100; ++i)
        {
            result_p0 += i;
        }

        printf("Resultado de la suma de los primeros 100 enteros: %d\n", result_p0);

        MPI_Wait(&request, &status); // Espera a que el envío se complete
        printf("Proceso 0 completó el envío del mensaje %f\n", dato);
    }
    else if (rank == 1)
    {
        MPI_Irecv(&dato, 1, MPI_FLOAT, rank - 1, 0, MPI_COMM_WORLD, &request); // Recepción no bloqueante
        printf("Proceso 1 inició la recepción del mensaje\n");

        int result_p1 = 0;
        for (int i = 0; i < 20; ++i)
        {
            result_p1 += i;
        }

        printf("Resultado de la suma de los primeros 20 enteros: %d\n", result_p1);

        MPI_Wait(&request, &status); // Espera a que la recepción se complete
        printf("Proceso 1 completó la recepción del mensaje %f\n", dato);
    }

    MPI_Finalize();
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // CLOCKS_PER_SEC constante que indica numero de ciclos por seg de la CPU

    printf("Tiempo de ejecucion: %.6f segundos\n", cpu_time_used);
    return 0;
}
