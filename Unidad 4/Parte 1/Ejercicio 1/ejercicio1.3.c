#include <stdio.h>
#include <omp.h>

void main()
{
#pragma omp parallel
    {
        printf("Máximo número disponible de hilos: %d.\n", omp_get_max_threads());
    }
}