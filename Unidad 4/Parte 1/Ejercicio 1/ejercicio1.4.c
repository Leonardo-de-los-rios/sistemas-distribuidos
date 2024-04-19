#include <stdio.h>
#include <omp.h>

void main()
{
#pragma omp parallel
    {
#pragma omp parallel
        {
            printf("Ejecución paralela anidada.\n");
        }
    }
}
