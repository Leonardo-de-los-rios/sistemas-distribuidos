import os

import Pyro5.api


def correr_cliente():
    server_ip = input("Ingrese la dirección del servidor: ")
    puerto = input("Ingrese el puerto del servicio: ")

    # Se crea un proxy para el objeto remoto registrado en la IP y puerto especificados.
    producto_vector = Pyro5.api.Proxy(f"PYRO:ejercicio3_rpc@{server_ip}:{puerto}")

    # Identificador único del cliente
    id_cliente = input("Ingrese su id unico como cliente: ")
    print(f"Bienvenido cliente {id_cliente}!")

    # Intentar obtener cualquier resultado pendiente primero
    resultado_pendiente = producto_vector.get_resultado_pendiente(id_cliente)
    if resultado_pendiente:
        print(f"Resultado pendiente para {id_cliente}: {resultado_pendiente}")

    n = int(input("Ingrese la cantidad de numeros del vector: "))
    vector = []
    for i in range(n):
        dato = int(input(f"Ingrese el numero {i+1}: "))
        vector.append(dato)
    print(vector)
    escalar = int(input("Ingrese el numero escalar: "))
    resultado = producto_vector.producto_escalar(id_cliente, vector, escalar)

    # Simula la desconexión del cliente antes de recibir la respuesta
    opcion = input("Desea simular la desconexion con el servidor?(s/n): ")
    if opcion.lower() == "s" or opcion.lower() == "si":
        print(f"Se produce la caida del cliente {id_cliente} de manera abrupta!")
        os._exit(1)

    # En este punto, no hay resultado pendiente a resguardar, por ende se borra el guardado pendiente
    resultado_no_pendiente = producto_vector.get_resultado_pendiente(id_cliente)
    print(
        f"[{id_cliente}] Resultado del Producto entre un Vector y Escalar: {resultado}"
    )


if __name__ == "__main__":
    correr_cliente()
