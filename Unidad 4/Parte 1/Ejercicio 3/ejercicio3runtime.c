#include <stdio.h>
#include <omp.h>

#define N 10

void main()
{
    int sum = 0;

#pragma omp parallel for schedule(runtime) reduction(+ : sum)
    for (int i = 0; i < N; i++)
    {
        sum += i;
    }
    printf("Suma en Tiempo de Ejecución: %d\n", sum);
}