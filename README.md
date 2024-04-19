# Sistemas Distribuidos 2024

## Ejecución

### Código Secuencial

#### Para **compilar** el programa:

```bash
  gcc nombre_archivo.c -o nombre_archivo.exe
```

#### Para **ejecutar** el programa:

```bash
  ./nombre_archivo
```

### Código Paralelo

#### Para **compilar** el programa:

```bash
  gcc -fopenmp nombre_archivo.c -o nombre_archivo.exe
```

#### Para **ejecutar** el programa:

```bash
  ./nombre_archivo
```

## Unidad 3

### Parte 1: Software Paralelo

#### Práctico introductorio de ejecución paralela en lenguaje C utilizando la librería openmp.

- #### [Suma de prefijos](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%201/ejercicio1.py)

- #### [Suma de los elementos de un vector](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%201/ejercicio2.py)

- #### [Multiplicación de matrices](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%201/ejercicio3.py)

- #### [Multiplicación de matrices en paralelo pseudocódigo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%201/producto_matrices_paralelo_pseudo.txt)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1At2Q5LabLE-xrAP-ujTwawipJ_woD0ub/view?usp=sharing)

### Parte 3: Métricas de eficiencia - Aplicación

#### Práctico para analizar el rendimiento de la ejecución en paralelo de la multiplicación de matrices.

- #### [Multiplicación de matrices secuencial](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%203/producto_matrices.c)

- #### [Multiplicación de matrices en paralelo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%203/producto_matrices_paralelo.c)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1LYEhnmU3-dzI5qxhPLBQD61AayaIDiQW/view?usp=sharing)

## Unidad 4

### Parte 1: Introducción a OpenMp

#### Ejercicios introductorios realizados en paralelo con OpenMp.

- #### [Introducción](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/tree/main/Unidad%204/Parte%201/Ejercicio%201)

- #### [Cláusula Private](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/tree/main/Unidad%204/Parte%201/Ejercicio%202)

- #### [Cláusula Schedule](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/tree/main/Unidad%204/Parte%201/Ejercicio%203)

- #### [Suma de Vectores](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/tree/main/Unidad%204/Parte%201/Ejercicio%204)

- #### [Mínimo, Máximo y desviación en un Vector](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%204/Parte%201/Ejercicio%205/ejercicio5.c)

- #### [Producto de Matrices](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/tree/main/Unidad%204/Parte%201/Ejercicio%206)

- #### [Analizar código](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%204/Parte%201/Ejercicio%207/ejercicio7.c)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/15eQUjvUwHxCePDV8lPwOu_1HLPl8XnWN/view?usp=sharing)

### Parte 2: Cálculo de Métricas con OpenMp

#### Práctico para analizar el código del programa para desenfocar una imagen en paralelo con OpenMp.

#### [Desenfocar imagen en paralelo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%204/Parte%201/Ejercicio%207/ejercicio7.c)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1L_ueY48exEGRn7nDAK4uEpOZu576Zm_4/view?usp=sharing)
