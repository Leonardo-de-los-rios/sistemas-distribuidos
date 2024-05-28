import Pyro5.api


def correr_cliente():
    server_ip = input("Ingrese la dirección del servidor: ")
    puerto = input("Ingrese el puerto del servicio: ")

    # Se crea un proxy para el objeto remoto registrado en la IP y puerto especificados.
    producto_vector = Pyro5.api.Proxy(f"PYRO:ejercicio3_rpc@{server_ip}:{puerto}")

    n = int(input("Ingrese la cantidad de numeros del vector: "))
    vector = []
    for i in range(n):
        dato = int(input(f"Ingrese el numero {i+1}: "))
        vector.append(dato)
    print(vector)
    escalar = int(input("Ingrese el numero escalar: "))

    resultado = producto_vector.producto_escalar(vector, escalar)
    print(f"Resultado del Producto entre un Vector y Escalar: {resultado}")


if __name__ == "__main__":
    correr_cliente()
