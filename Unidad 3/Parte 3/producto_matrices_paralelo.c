#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10

void cargar_arreglo(int arr[N][N])
{
	int i, j;
// double inicio, fin;
// inicio = omp_get_wtime();
#pragma omp parallel for private(i, j) shared(arr)
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			arr[i][j] = rand() % 9 + 1; // generar numeros aleatorios entre 1 y 9
		}
	}
	// fin = omp_get_wtime();
	// printf("\nTiempo de ejecucion %.6f seg", fin-inicio);
}

void mostrar_arreglo(int arr[N][N])
{
	int i, j;
	// seccion de codigo que debe ejecutarse secuencial para mostrar bien los elementos del arreglo
	for (i = 0; i < N; i++)
	{
		printf("[ ");
		for (j = 0; j < N; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("]\n");
	}
}

void cerear_matriz(int m[N][N])
{
	int i, j;
#pragma omp parallel for private(i, j) shared(m)
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			m[i][j] = 0;
		}
	}
}

void producto_matrices(int m1[N][N], int m2[N][N], int resultante[N][N])
{
	int i, j, k;
#pragma omp parallel for collapse(2) private(k)
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < N; k++)
			{
				resultante[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
}

int main()
{
	int matriz1[N][N];
	int matriz2[N][N];
	int resultante[N][N];
	cargar_arreglo(matriz1);
	cargar_arreglo(matriz2);
	printf("Mostramos la matriz 1:\n");
	mostrar_arreglo(matriz1);
	printf("\nMostramos la matriz 2:\n");
	mostrar_arreglo(matriz2);

	cerear_matriz(resultante);
	producto_matrices(matriz1, matriz2, resultante);
	printf("\nMostramos la matriz resultante:\n");
	mostrar_arreglo(resultante);
	return 0;
}

/*
Porque trabajar con for colapse() y no con for private() shared()
Collapse(2) con private(k): Se colapsan los dos primeros bucles en uno solo. Esto significa que cada hilo de OpenMP manejara
una porcion del trabajo total que antes estaba distribuido entre los dos bucles. Cada hilo tendra su
propia copia de las variables de iteracion i y j, y si se aplica clausula private(k) como se hizo en el ejemplo,
cada hilo tambien tendra su propia copia de la variable k en el bucle mas interno.

Por lo tanto, cada hilo trabajara de forma independiente con sus propias variables de iteracion i, j y k,
evitando asi� cualquier problema de concurrencia o condicion de carrera que pudiera surgir debido a la modificacion
concurrente de estas variables por multiples hilos.
Ventaja: Util si la ejecucion del bucle interno (k) es intensiva en calculos y no depende de valores
de iteracion externos.

Private(i,j,k): Esta opcion hace que cada hilo tenga su propia copia de todas las variables de iteracion
i, j y k. Esto puede ser util si la ejecucion del bucle interno (k) depende de valores de iteracion
externos o si hay otros calculos que dependen de estas variables fuera del bucle interno.
Sin embargo, puede haber un mayor costo de administracion de hilos y consumo de memoria.

*/
