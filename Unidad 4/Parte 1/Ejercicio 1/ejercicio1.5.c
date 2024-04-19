#include <stdio.h>
#include <omp.h>

void main()
{
    int num_threads;

#pragma omp parallel
    {
        num_threads = omp_get_num_threads();
        printf("[Generación] Número de hilos en la región paralela: %d.\n", num_threads);
    }

    omp_set_num_threads(8);
#pragma omp parallel
    {
        num_threads = omp_get_num_threads();
        printf("[Modificación] Número de hilos en la región paralela: %d.\n", num_threads);
    }
}