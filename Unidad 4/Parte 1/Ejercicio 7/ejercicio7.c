#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 10
#define N 100

int main(int argc, char *argv[])
{
	int nthreads, tid, i, chunk; // chunk => porcion,pedazo,trozo..
	float a[N], b[N], c[N];

	/* Some initializations */
	for (i = 0; i < N; i++)
		a[i] = b[i] = i * 1.0;

	chunk = CHUNKSIZE; // chunksize tama�o de la porcion
#pragma omp parallel shared(a, b, c, nthreads, chunk) private(i, tid)
	{
		tid = omp_get_thread_num(); // id del hilo que lo llama
		if (tid == 0)
		{
			nthreads = omp_get_num_threads(); // numero total de hilos en la region paralela
			printf("Number of threads = %d\n", nthreads);
		}
		printf("Thread %d starting...\n", tid);
#pragma omp for schedule(dynamic, chunk)
		for (i = 0; i < N; i++)
		{
			c[i] = a[i] + b[i];
			printf("Thread %d: c[%d]= %f\n", tid, i, c[i]);
		}
	}
	/* end of parallel section */
	return 0;
}
