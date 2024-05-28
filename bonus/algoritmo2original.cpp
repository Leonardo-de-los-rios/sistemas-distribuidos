#include <stdio.h>
#define ROWS 10000000
#define COLS 200

int main(void)
{
    char *A = new char[ROWS * COLS];
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            A[i * COLS + j] = i + j;
        }
    }
    delete[] A;
    return 0;
}
