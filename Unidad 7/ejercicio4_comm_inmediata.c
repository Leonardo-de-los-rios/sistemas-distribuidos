#include <stdio.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char **argv) {
	int rank, size;
	clock_t start, end;
	double cpu_time_used;
	
	MPI_Init(&argc, &argv);
	start = clock();
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	/*if (size < 2) {
		printf("Se necesitan al menos 2 procesos para la comunicacion\n");
		MPI_Finalize();
		return 0;
	} */	
	int dato = 777;
	MPI_Request request;	
	if (rank == 0) {
		MPI_Isend(&dato, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
		printf("Proceso %d envia el dato %d\n", rank, dato);
	} else if (rank == 1) {
		MPI_Recv(&dato, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Proceso %d recibe el dato %d\n", rank, dato);
	}	
	MPI_Finalize();
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;		
	//CLOCKS_PER_SEC constante que indica numero de ciclos por seg de la CPU
	
	printf("Tiempo de ejecucion: %.6f segundos\n", cpu_time_used);
	return 0;
}
