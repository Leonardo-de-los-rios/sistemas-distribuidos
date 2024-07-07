# Sistemas Distribuidos y Paralelos 2024

## Instalación Lenguaje C

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

### MPI

#### Para **compilar** el programa:

```bash
  mpicc -o nombre_archivo.c nombre_archivo.exe
```

#### Para **ejecutar** el programa:

```bash
  mpirun -np numero_procesos nombre_archivo
```

## Instalación Lenguaje C++

### Código Secuencial

#### Para **compilar** el programa:

```bash
  gpp nombre_archivo.c -o nombre_archivo.exe
```

#### Para **ejecutar** el programa:

```bash
  ./nombre_archivo
```

### Código Paralelo

#### Para **compilar** el programa:

```bash
  gpp -fopenmp nombre_archivo.c -o nombre_archivo.exe
```

#### Para **ejecutar** el programa:

```bash
  ./nombre_archivo
```

## Instalación Python

#### Descargar [Python 3.12.2](https://www.python.org/downloads/release/python-3122/)

#### Descargar repositorio

#### Crear entorno virtual

```bash
  python -m venv env
```

#### Activar entorno virtual

```bash
  env\Scripts\activate
```

#### Instalar librerías:

```bash
  pip install -r requirements.txt
```

#### Ejecutar programa:

```bash
  python .\nombre_programa.py
```

# Unidad 3

## Parte 1: Software Paralelo

#### Práctico introductorio de ejecución paralela en lenguaje C utilizando la librería openmp.

- #### [Suma de prefijos](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%201/ejercicio1.py)

- #### [Suma de los elementos de un vector](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%201/ejercicio2.py)

- #### [Multiplicación de matrices](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%201/ejercicio3.py)

- #### [Multiplicación de matrices en paralelo pseudocódigo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%201/producto_matrices_paralelo_pseudo.txt)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1At2Q5LabLE-xrAP-ujTwawipJ_woD0ub/view?usp=sharing)

## Parte 3: Métricas de eficiencia - Aplicación

#### Práctico para analizar el rendimiento de la ejecución en paralelo de la multiplicación de matrices.

- #### [Multiplicación de matrices secuencial](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%203/producto_matrices.c)

- #### [Multiplicación de matrices en paralelo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%203/Parte%203/producto_matrices_paralelo.c)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1LYEhnmU3-dzI5qxhPLBQD61AayaIDiQW/view?usp=sharing)

# Unidad 4

## Parte 1: Introducción a OpenMp

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

## Parte 2: Cálculo de Métricas con OpenMp

#### Práctico para analizar el código del programa para desenfocar una imagen en paralelo con OpenMp.

- #### [Desenfocar imagen en paralelo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/tree/main/Unidad%204/Parte%202)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1L_ueY48exEGRn7nDAK4uEpOZu576Zm_4/view?usp=sharing)

# Unidad 7

#### Ejercicios introductorios de MPI.

- #### [Introducción](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%207/ejercicio1.c)

- #### [Comunicación entre Procesos Introductorio](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%207/ejercicio2.c)

- #### [Comunicación entre Procesos Avanzado](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%207/ejercicio3.c)

- #### [Comunicación Inmediata](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%207/ejercicio4_comm_inmediata.c)

- #### [Comunicación Síncrona](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%207/ejercicio4_comm_sincrona.c)

- #### [Comunicación Bloqueante](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%207/ejercicio5bloqueante.c)

- #### [Comunicación No Bloqueante](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%207/ejercicio5nobloqueante.c)

- #### [Broadcast](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%207/ejercicio6.c)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1YQeNcpxG6OFXVFnyRI-BMh_RIUzG24nj/view?usp=sharing)

# Unidad 8

## Parte 1: Comunicación en SSDD - Comunicación a Grupo

#### Ejercicios introductorios de comunicación a grupo.

- #### [Pasaje de Memoria Compartida](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%201/pasaje_mjs_memoria_compartida.py)

- #### [TCP Cliente](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%201/tcp_cliente.py)

- #### [TCP Servidor](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%201/tcp_servidor.py)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1XFYiMxjXw7C51338Vhv6Sa_ozWKzPdHx/view?usp=sharing)

## Parte 2: RPC (Remote Procedure Call)

#### Ejercicios de comunicación entre cliente y servidor por medio de RPC en Python.

- #### [Calcular Tamaño](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/Ejercicio%205/calcsize.py)

- #### [Paridad Cliente](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/paridad_client.py)

- #### [Paridad Servidor](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/paridad_server.py)

- #### [Calculadora Cliente](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/calculadora_client.py)

- #### [Calculadora Servidor](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/calculadora_server.py)

- #### [Paridad Cliente Timeout](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/paridad_timeout_client.py)

- #### [Calculadora Cliente Timeout](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/calculadora_timeout_client.py)

- #### [Producto Escalar Cliente](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/producto_escalar_client.py)

- #### [Producto Escalar Servidor](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/producto_escalar_server.py)

- #### [Materias Cliente](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/materias_client.py)

- #### [Materias Servidor](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/materias_server.py)

- #### [Producto Escalar Cliente Fail](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/producto_escalar_client_fail.py)

- #### [Producto Escalar Servidor Persistente](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/producto_escalar_server_persistente.py)

- #### [Calculadora Cliente Fail](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/calculadora_client_fail.py)

- #### [Calculadora Servidor Persistente](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%208/Parte%202/RPC/calculadora_server_persistente.py)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1Ys4mNqcnWVD-mHvrJIvZd1ntitagR0QC/view?usp=sharing)

# Unidad 9

## Parte 2: Relojes Físicos

- #### [GPS](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%209/Parte%202/gps.py)

- #### [GPS UTC](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Unidad%209/Parte%202/gps_utc.py)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1_e_MMVLigyh_rEZybk-NgpHnccF5eLrt/view?usp=drive_link)

# Integrador

## Buscar máximo y mínimo en un arreglo de forma secuencial y paralela.

- #### [Secuencial](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Integrador/secuencial.c)

- #### [OpenMP](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Integrador/openmp.c)

- #### [MPI](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/Integrador/mpi.c)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1LAoAs1P9FZa4Fj719umeR3_xr7SgI18G/view?usp=drive_link)

# Bonustrack

#### Ejercicio de comparación entre inserción continua y no continua.

- #### [Algoritmo 1 - Original](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/bonus/algoritmo1original.cpp)

- #### [Algoritmo 1 - Secuencial](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/bonus/algoritmo1.cpp)

- #### [Algoritmo 1 - Paralelo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/bonus/algoritmo1paralelo.cpp)

- #### [Algoritmo 1 - Inserción Continua Secuencial](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/bonus/algoritmo1insercion_continua.cpp)

- #### [Algoritmo 1 - Inserción Continua Paralelo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/bonus/algoritmo1insercion_continua_paralelo.cpp)

- #### [Algoritmo 2 - Original](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/bonus/algoritmo2original.cpp)

- #### [Algoritmo 2 - Secuencial](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/bonus/algoritmo2.cpp)

- #### [Algoritmo 2 - Paralelo](https://github.com/Leonardo-de-los-rios/sistemas-distribuidos/blob/main/bonus/algoritmo2paralelo.cpp)

#### Link del pdf resuelto:

[![Download as PDF Button](https://camo.githubusercontent.com/4b7e2df20c344127c85b210653959ea7cd2ddb1c1862f27c715cd460703e76d3/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f446f776e6c6f616425323061732532305044462d4546333933393f7374796c653d666c6174266c6f676f3d61646f62656163726f626174726561646572266c6f676f436f6c6f723d776869746526636f6c6f723d626c61636b266c6162656c436f6c6f723d656331633234)](https://drive.google.com/file/d/1Zdo3HJE8cu_JZ9eLjF1nigW5T5pyL6Aa/view?usp=sharing)
