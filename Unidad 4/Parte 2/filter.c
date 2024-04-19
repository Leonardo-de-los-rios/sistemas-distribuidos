#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// This method returns the index to find the pixels
int GetIdx(int idx, int i, int j, int width)
{
    return (int)(idx + 3 * (i * width + j));
}

int main(int argc, char const *argv[])
{

    char *imagePath = "original.jpg";
    double t1, t2;
    int width, height, channels;

    // The image is load in sourceImage
    unsigned char *sourceImage = stbi_load(imagePath, &width, &height, &channels, 0);
    if (sourceImage == NULL)
    {
        printf("Error, can't load the image %s\n", imagePath);
        return -1;
    }
    else
    {
        printf("Loaded image of %d x %d with %d channels\n", width, height, channels);
    }

    // Differents kernels produces differents results, if the kernel is larger, the blur will be more noticeable

    unsigned char K[21][21] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    // Reserving memory for the processed image
    // blurImg almacena la imagen procesada
    unsigned char *blurImg;
    blurImg = (unsigned char *)malloc(width * height * channels);

    int a = (int)(sizeof(K[0]) - 1) / 2;
    float suma;
    int idx = 0, idx2 = 0;
    int valor = sizeof(K) - 10;

    /*  Start the sequential code
     *  The sequential code works with five "for" cicle
     *
     */

    t1 = omp_get_wtime();
    for (int idxChannel = 0; idxChannel < channels; idxChannel++)
    {
        for (int j = a; j < height - a; j++)
        {
            for (int k = a; k < width - a; k++)
            {

                idx = GetIdx(idxChannel, j, k, width); // Getting index to save the pixel value
                suma = 0.0;

                for (int kerH = -a; kerH < a; kerH++)
                {
                    for (int kerW = -a; kerW < a; kerW++)
                    {

                        idx2 = GetIdx(idxChannel, j + kerH, k + kerW, width);              // Getting index to multiply for kernel
                        suma += (float)sourceImage[idx2] * (float)(K[kerH + a][kerW + a]); // Adding up the values
                    }
                }
                suma = (float)(suma * (1.0 / valor));
                blurImg[idx] = (unsigned char)suma; // Assignment the value to pixel
            }
        }
    }
    t2 = omp_get_wtime();

    // Saving the processed image with sequential procedure
    stbi_write_jpg("original_secuencial.jpg", width, height, 3, blurImg, 100);
    stbi_image_free(blurImg);

    // Getting the total time
    printf("Fin de secuencial en tiempo de: %f\n", t2 - t1);

    /*  Start the parallel code
     *  The parallel code works with the same number of threads that the channels on the image
     */

    // Reserving memory for the second processed image
    unsigned char *blurImgPara;
    blurImgPara = (unsigned char *)malloc(width * height * channels);

    // Creating the variables for work with threads, one thread for each channel on the image
    int tid, j, k;
    omp_set_num_threads(channels);

    t1 = omp_get_wtime();
#pragma omp parallel private(tid, suma, idx, idx2, j, k)
    {
        // Getting the thread ID
        tid = omp_get_thread_num();

        // Each thread works with different channel of the image, this is possible with thread ID
        for (int idxChannel = tid; idxChannel < tid + 1; idxChannel++)
        {
            printf("Trabajando hilo: %d\n", tid);
            for (int j = a; j < height - a; j++)
            {
                for (int k = a; k < width - a; k++)
                {

                    idx = GetIdx(idxChannel, j, k, width);
                    suma = 0.0;

                    for (int kerH = -a; kerH < a; kerH++)
                    {
                        for (int kerW = -a; kerW < a; kerW++)
                        {

                            idx2 = GetIdx(idxChannel, j + kerH, k + kerW, width);
                            suma += (float)sourceImage[idx2] * (float)(K[kerH + a][kerW + a]);
                        }
                    }
                    suma = (float)(suma * (1.0 / valor));
                    blurImgPara[idx] = (unsigned char)suma;
                }
            }
        }
    }
    t2 = omp_get_wtime();

    // Saving the processed image with parallel procedure
    stbi_write_jpg("original_parallel.jpg", width, height, 3, blurImgPara, 100);
    stbi_image_free(blurImgPara);

    // Getting the total time
    printf("Fin de paralelo en tiempo: %f\n", t2 - t1);

    return 0;
}