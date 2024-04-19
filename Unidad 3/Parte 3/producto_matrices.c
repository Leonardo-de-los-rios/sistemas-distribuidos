#include <stdio.h>
#include <stdlib.h>
#define N 10

void cargar_arreglo(int arr[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			arr[i][j] = rand() % 9 + 1; // generar numeros aleatorios entre 1 y 9
		}
	}
}

void mostrar_arreglo(int arr[N][N])
{
	for (int i = 0; i < N; i++)
	{
		printf("[ ");
		for (int j = 0; j < N; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("]\n");
	}
}

void cerear_matriz(int m[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			m[i][j] = 0;
		}
	}
}

void producto_matrices(int m1[N][N], int m2[N][N], int resultante[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				resultante[i][j] = resultante[i][j] + (m1[i][k] * m2[k][j]);
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
