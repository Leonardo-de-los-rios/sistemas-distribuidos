#include <stdio.h>
#include <omp.h>

void main()
{
#pragma omp parallel
    {
        printf("Número de hilos que ese están ejecutando: %d\n", omp_get_num_threads());
    }
}