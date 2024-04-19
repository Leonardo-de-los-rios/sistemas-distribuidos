#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define N 50000 // Elementos Arreglo

void generar_csv(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    srand(time(NULL)); // Semilla para la generación de números aleatorios

    for (int i = 0; i < N; i++)
    {
        double num = (double)rand() / RAND_MAX * 1000.0; // Generar número aleatorio entre 0 y 1000
        fprintf(fp, "%.9f\n", num);
    }

    fclose(fp);
}

void cargar_desde_csv(const char *filename, double vector[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (fscanf(fp, "%lf", &vector[i]) != 1)
        {
            printf("Error al leer el archivo.\n");
            break;
        }
    }

    fclose(fp);
}

double sumar(double vector1[], double vector2[], double resultado[])
{
    LARGE_INTEGER inicio, fin;
    QueryPerformanceCounter(&inicio);

    for (int i = 0; i < N; i++)
    {
        resultado[i] = vector1[i] + vector2[i];
    }

    QueryPerformanceCounter(&fin);
    LARGE_INTEGER frecuencia;
    QueryPerformanceFrequency(&frecuencia);
    double tiempo_inicio = (double)inicio.QuadPart;
    double tiempo_fin = (double)fin.QuadPart;
    double tiempo_diferencia = (tiempo_fin - tiempo_inicio) / (double)frecuencia.QuadPart;

    return tiempo_diferencia;
}

double promedio(double tiempos[], int total_elementos)
{
    double promedio = 0.0;

    for (int i = 0; i < total_elementos; i++)
    {
        promedio += tiempos[i];
    }
    promedio /= total_elementos;

    return promedio;
}

int main()
{
    LARGE_INTEGER inicio, fin;
    QueryPerformanceCounter(&inicio);

    /* generar_csv("vector1.csv");
    generar_csv("vector2.csv"); */

    double vector1[N];
    double vector2[N];
    double resultado[N];

    cargar_desde_csv("vector1.csv", vector1);
    cargar_desde_csv("vector2.csv", vector2);

    double tiempos[4000];
    int posicion = 0;

    while (posicion < sizeof(tiempos) / sizeof(tiempos[0]))
    {
        double tiempo_diferencia = sumar(vector1, vector2, resultado);

        tiempos[posicion] = tiempo_diferencia;
        posicion++;
    }

    int total_elementos = sizeof(tiempos) / sizeof(tiempos[0]);

    printf("Tiempo Promedio calculo de Suma: %.9f\n", promedio(tiempos, total_elementos));

    QueryPerformanceCounter(&fin);

    LARGE_INTEGER frecuencia;
    QueryPerformanceFrequency(&frecuencia);
    double tiempo_total = (double)(fin.QuadPart - inicio.QuadPart) / (double)frecuencia.QuadPart;

    printf("Tiempo total de ejecución: %.9f segundos\n", tiempo_total);

    return 0;
}
