#include <stdio.h>
#include <omp.h>

int main()
{
    int var_global = -1;

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        var_global = id * 1000; // cada hilo paralelo modifica la variable gl
        printf("[Ejecución Paralela] Hilo: %d\t| Variable Global: %d\n", id, var_global);
    }

    // Último hilo que modificó la variable global
    printf("[Después de la Ejecución] Variable Global: %d\n", var_global);
    return 0;
}