import platform
import struct  # módulo que permite trabajar con datos binarios

#Formato de los strings
formats = ['@lhl', '@llh', '<qqh6x', '@llh0l']

#Tipo de arquitectura
architectura = platform.architecture()[0]
print(f'Arquitectura del sistema: {architectura}')

#Calcula e imprime el tamaño de cada formato
for fmt in formats:
    #calcsize se usa para determinar el tamaño (en bytes) que ocupará
    #la estructura de datos especificada en la cadena de formato
    size = struct.calcsize(fmt)     
    print(f"Tamaño del formato '{fmt}' es: {size} bytes")


# @lhl: @ de la arquitec, l Entero largo (4 bytes en 32 bits, 8 bytes en 64 bits), h entero corto(2 bytes), l otro entero largo.
# @llh: Similar al anterior, pero dos enteros largos seguidos de un entero corto.
# <qqh6x: '<' Little-endian, q Entero Largo (8 bytes) x2, h Entero Corto (2 bytes), 6x seis bytes de relleno (padding).
# @llh0l: @ de la arq, l Entero largo x2, h Entero corto y 0l entero largo con cero bytes de relleno.