#include <stdio.h>
#include <omp.h>

int main()
{
    int var_global = -1;

#pragma omp parallel private(var_global)
    {
        int id = omp_get_thread_num();
        var_global = id * 1000; // cada hilo paralelo tendra como valor id*1000
        printf("[Ejecución Paralela] Hilo: %d | Variable Global: %d\n", id, var_global);
    }

    printf("[Después de la Ejecución] Variable Global: %d\n", var_global); // valor -1
    return 0;
}