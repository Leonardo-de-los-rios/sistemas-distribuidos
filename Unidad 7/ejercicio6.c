#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ROOT 0
#define ARRAY_SIZE 8
#define PORTION_SIZE 2

int main(int argc, char **argv)
{
	int rank, size;
	int value;
	int array[ARRAY_SIZE];
	int recv_portion[PORTION_SIZE];
	int gathered_array[ARRAY_SIZE];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// 1: El proceso raíz envía un valor a todos los procesos
	if (rank == ROOT)
	{
		value = 777; // Valor a enviar
	}
	MPI_Bcast(&value, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
	printf("\nPaso 1: Id Proceso %d recibe el valor %d\n", rank, value);

	// Para Paso 2 y 3: Inicializar el arreglo en el proceso raíz
	if (rank == ROOT)
	{
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			array[i] = rand() % 9; // llenar el arreglo con numeros aleatorios entre 0 y 9
		}
		printf("\nSe muestra el arreglo generado por Raíz: ");
		printf("[");
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			printf(" %d", array[i]);
		}
		printf("]\n");
	}

	// 2: El proceso raíz envía una porción del arreglo a cada proceso
	MPI_Scatter(array, PORTION_SIZE, MPI_INT, recv_portion, PORTION_SIZE, MPI_INT, ROOT, MPI_COMM_WORLD);
	printf("\nPaso 2: Id Proceso %d recibe una porción del arreglo: ", rank);
	printf("[");
	for (int i = 0; i < PORTION_SIZE; i++)
	{
		printf(" %d", recv_portion[i]);
		// cada proceso incrementa en uno cada elemento de la porción recibida
		recv_portion[i] += 1;
	}
	printf("]\n");

	// 3: Cada proceso envía una porción del arreglo al proceso raíz
	MPI_Gather(recv_portion, PORTION_SIZE, MPI_INT, gathered_array, PORTION_SIZE, MPI_INT, ROOT, MPI_COMM_WORLD);

	if (rank == ROOT)
	{
		printf("\nPaso 3: Proceso raíz reune el arreglo:\n");
		printf("[");
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			printf(" %d", gathered_array[i]);
		}
		printf("]\n");
	}

	MPI_Finalize();
	return 0;
}
