#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

int matriz1[N][N];
int matriz2[N][N];
int resultante[N][N];

// Vario el numero de cores: 1,2,3 y 4 para esta compu gamer (esto para el miercoles xd)

void cargar_arreglo(int arr[N][N])
{
	int i, j;
	// double inicio, fin;
	// inicio = omp_get_wtime();
	omp_set_num_threads(8);						   // para que ejecute con 8 cores
#pragma omp parallel for private(i, j) shared(arr) // Carga paralelizable pues cada hilo genera numeros aleatorios para la matriz
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
	omp_set_num_threads(8); // para que ejecute con 8 cores
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
	omp_set_num_threads(8); // para que ejecute con 8 cores
#pragma omp parallel for collapse(2) private(k)
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			for (k = 0; k < N; k++)
			{
				resultante[i][j] += m1[i][k] * m2[k][j];
				// resultante[i][j] += (m1[i][k] * m2[k][j]);
			}
		}
	}
}

double multiplicacion_matrices(int matriz1[N][N], int matriz2[N][N], int resultante[N][N])
{
	double inicio, fin;
	inicio = omp_get_wtime();

	cargar_arreglo(matriz1);
	cargar_arreglo(matriz2);
	// printf("Mostramos la matriz 1:\n");
	// mostrar_arreglo(matriz1);
	// printf("\nMostramos la matriz 2:\n");
	// mostrar_arreglo(matriz2);

	cerear_matriz(resultante);
	producto_matrices(matriz1, matriz2, resultante);
	// printf("\nMostramos la matriz resultante:\n");
	// mostrar_arreglo(resultante);

	fin = omp_get_wtime();
	return fin - inicio;
}

int main()
{

	double tiempos[10], tpromedio;

	for (int i = 0; i < 10; i++)
	{ // realizo diez pasadas
		tiempos[i] = multiplicacion_matrices(matriz1, matriz2, resultante);
		// printf("\nTiempo de la pasada %d es: %.6f seg\n", i+1, tiempos[i]);
	}

	// Para sacar tiempo ponderado (entre 2da y 9na pasada)
	for (int i = 1; i < 9; i++)
	{
		tpromedio += tiempos[i];
	}
	tpromedio /= 8;
	printf("\nTiempo promedio de ejecucion paralelo: %.8f seg", tpromedio);

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
