#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define N 30			//despues modificar para 10.000, 100.000 y 500.000

void cargar_vector (int *v) {
	int i;
	for (i=0; i < N; i++) {
		v[i] = rand() % 1000;		//genero vector con numeros aleatorios entre 0 y 999.
	}
}

void mostrar_vector (int *v) {
	printf("==========Se muestra Vector==========\n");
	printf("[ ");
	for (int i=0; i < N; i++) {
		printf("%d ", v[i]);
	}
	printf("]\n");
}

void operaciones_vector (int *v) {
	int i, min, max;
	float prom, desvio, suma;
	suma = 0.0;
	//omp_set_num_threads(2);			//Lo coloco para los otros apartados de modificar hilos y secciones
	
	printf("\nCantidad de Hilos disponibles: %d\n", omp_get_max_threads());		//Hilo maestro muestra la cantidad de hilos de trabajo
	
	#pragma omp parallel sections shared(v)		//Conjunto de secciones (3 en este caso)
	{
		#pragma omp section		//Seccion 1: Calculo del minimo del vector
		{
			min=v[0];
			for (i=1;i < N;i++) {
				if (v[i] < min) {
					min = v[i];
				}
			}
			printf("Seccion 1 Minimo, Hilo: %d, Minimo: %d\n", omp_get_thread_num(), min);
		}
		#pragma omp section		//Seccion 2: Calculo del maximo del vector
		{
			max=v[0];
			for (i=1;i < N;i++) {
				if (v[i] > max) {
					max = v[i];
				}
			}
			printf("Seccion 2 Maximo, Hilo: %d, Maximo: %d\n", omp_get_thread_num(), max);
		}
		#pragma omp section 	//Seccion 3: Calculo del desvio/desviacion estandar entre los datos del vector
		{
			for (i = 0; i < N; i++) {
				suma += v[i];
			}
			prom = suma / N;
			
			// Calculo de la desviacion estandar
			suma = 0.0;
			for (i = 0; i < N; i++) {
				suma += (v[i] - prom) * (v[i] - prom);
				//suma += pow(v[i]-promedio, 2);
			}
			desvio = sqrt(suma / N);			//varianza es suma/N
			printf("Seccion 3 Desviacion, Hilo: %d - Desviacion Estandar: %.2f\n", omp_get_thread_num(), desvio);	
		}
	}
	
}

int main () {			//Ejecutar este programa con -lm al final (para libreria math): gcc ejercicio5.c -o ejercicio5 -fopenmp -lm
	int vector[N];
	cargar_vector(vector);
	mostrar_vector(vector);
	operaciones_vector(vector);
	return 0;
}
