#include <iostream>
#include <chrono>
#include <omp.h>
#define ROWS 10000000
#define COLS 200

int main(void)
{
    char *A = new char[ROWS * COLS];

    auto start = std::chrono::high_resolution_clock::now(); // Inicia la medición de tiempo
#pragma omp parallel for
    for (int j = 0; j < COLS; ++j)
    {
        for (int i = 0; i < ROWS; ++i)
        {
            A[j * ROWS + i] = i + j;
        }
    }
    auto end = std::chrono::high_resolution_clock::now(); // Termina la medición de tiempo

    delete[] A;

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos\n";

    return 0;
}
