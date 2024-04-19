#include <stdio.h>
#include <omp.h>

void main()
{
#pragma omp parallel
    {
        printf("Numero de procesadores disponibles: %d\n", omp_get_num_procs());
    }
}