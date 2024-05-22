#include <stdio.h>
#include "mpi.h"
int main(int argc, char **argv)
{
	int rank, value, size;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	do
	{
		if (rank == 0)
		{
			printf("\nIngrese un valor entero(negativo para salir): ");
			scanf("%d", &value);
			MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
		}
		else
		{
			MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
			if (rank < size - 1)
				MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
		}

		printf("Proceso %d obtuvo %d\n", rank, value);

	} while (value >= 0);

	MPI_Finalize();
	return 0;
}
