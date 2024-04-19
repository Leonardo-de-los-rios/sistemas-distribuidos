#include <stdio.h>
#include <omp.h>

#define N 10

void main()
{
    int sum = 0;

#pragma omp parallel for schedule(guided) reduction(+ : sum)
    for (int i = 0; i < N; i++)
    {
        sum += i;
    }
    printf("Suma Guiada: %d\n", sum);
}