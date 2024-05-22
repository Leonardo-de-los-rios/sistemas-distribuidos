#include <stdio.h>
#include <string.h>
#include <mpi.h>
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
	char dato[100];
	if (rank == 0)
	{
		strcpy(dato, "hola");
		MPI_Send(dato, strlen(dato) + 1, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
		printf("Proceso %d envió %s al proceso %d\n", rank, dato, rank + 1);
	}
	else if (rank == 1)
	{
		MPI_Recv(&dato, 100, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Proceso %d recibió %s del proceso %d\n", rank, dato, rank + 1);
	}
	MPI_Finalize();
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	// CLOCKS_PER_SEC constante que indica numero de ciclos por seg de la CPU

	printf("Tiempo de ejecucion: %.6f segundos\n", cpu_time_used);

	return 0;
}
