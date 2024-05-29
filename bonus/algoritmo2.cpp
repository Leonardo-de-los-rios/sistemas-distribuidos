#include <iostream>
#include <chrono>
#define ROWS 10000000
#define COLS 200

int main(void)
{
    char *A = new char[ROWS * COLS];

    int max = 5;

    auto start = std::chrono::high_resolution_clock::now(); // Inicia la medición de tiempo
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            A[i * COLS + j] = i + j;
            if (max > 0)
            {
                std::cout << "Posición: " << i * COLS + j << "\n";
                max -= 1;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now(); // Termina la medición de tiempo

    delete[] A;

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos\n";

    return 0;
}
