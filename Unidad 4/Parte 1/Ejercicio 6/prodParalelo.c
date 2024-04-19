/*Producto Paralelo entre una matriz y un vector:
A es un vector (orden m), B una matriz (orden mxn) y C un vector (orden n). A = B . C
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void cargar_vector(double *v, int longitud) {
	int i;
	printf("Se cargan los %d elementos del vector:\n", longitud);
	for (i = 0; i < longitud; i++) {
		v[i] = rand() % 9 +1; 		//generar numeros aleatorios entre 1 y 9
	}
}

void cargar_matriz(double *matriz, int filas, int columnas) {
	int i, j;
	printf("Se cargan los elementos de la matriz (%d x %d):\n", filas, columnas);
	for (i = 0; i < filas; i++) {
		for (j = 0; j < columnas; j++) {
			//Para acceder a cada elemento:
			//1ra Fila: i(0) * columnas(3 ej) + j(1,..,n) va accediendo a los primeros n elementos
			//1ra Fila: i(1) * columnas(3 ej) + j(1,..,n) va accediendo a partir de n+3 elementos
			matriz[i * columnas + j] = rand() % 9 + 1; 	
			
		}
	}
}

void mostrar_matriz (double *m, int filas, int columnas) {
	int i, j;
	printf("Se muestra Matriz (%d x %d):\n", filas, columnas);
	for (i = 0; i < filas; i++) {
		for (j = 0; j < columnas; j++) {
			printf("%.2f ", m[i*columnas + j]);
		}
		printf("\n");
	}
	printf("\n");
}

void mxv_row(int m, int n, double *A, double *B, double *C) {
	int i, j;
	#pragma omp parallel for private(i,j) shared(A,B,C)		//deberia trabajar con 4 hilos de mi compu
	
	for (i = 0; i < m; i++) {
		//printf("%d\n", omp_get_num_threads());			//efectivamente me muestra 4, si quiero hacer más hilos debo usar omp_set
		A[i] = 0.0;
		for (j = 0; j < n; j++) {
			A[i] += B[i * n + j] * C[j];
		}
	}
}

void mostrar_vector(double *v, int longitud) {
	int i;
	printf("[");
	for (i = 0; i < longitud; i++) {
		printf("%.2f ", v[i]);
	}
	printf("]\n");
}

int main() {
	int m, n;
	
	printf("Ingrese el numero de filas de la matriz B: ");
	scanf("%d", &m);
	
	printf("Ingrese el numero de columnas de la matriz B (y la longitud del vector C): ");
	scanf("%d", &n);
	
	double A[m];
	double B[m * n];			//arreglo unidimensional: Los n primeros elementos representan 1era Fila, los n siguientes 2da fila y asi...
	double C[n];
	
	cargar_matriz(B, m, n);
	printf("\nSe muestra Matriz B\n");
	mostrar_matriz(B,m,n);
	cargar_vector(C, n);
	printf("\nSe muestra Vector C\n");
	mostrar_vector(C,n);
	
	mxv_row(m, n, A, B, C);
	
	printf("El resultado del producto A = B . C es:\n");
	mostrar_vector(A, m);
	
	return 0;
}
