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
			scanf("%d", &value);
			MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
			printf("Proceso %d envió %d al proceso %d\n", rank, value, rank + 1);
		}
		else
		{
			MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
			printf("Proceso %d recibió %d del proceso %d\n", rank, value, rank - 1);

			if (rank < size - 1)
			{
				MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
				printf("Proceso %d envió %d al proceso %d\n", rank, value, rank + 1);
			}
		}
	} while (value >= 0);

	MPI_Finalize();
	return 0;
}
