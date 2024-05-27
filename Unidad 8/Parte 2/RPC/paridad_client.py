import Pyro5.api


def correr_cliente():
    # Se especifica la dirección IP del servidor al correr primero el servidor

    server_ip = input("Ingrese la dirección del servidor: ")
    puerto = input("Ingrese el puerto del servicio: ")

    # Se crea un proxy para el objeto remoto registrado como "ejercicio1_rpc" en la IP y puerto especificados.
    paridad = Pyro5.api.Proxy(f"PYRO:ejercicioA_rpc@{server_ip}:{puerto}")

    # Envía un número al servidor
    numero = int(input("Introduce un número: "))
    resultado = paridad.es_par(numero)
    print(resultado)


if __name__ == "__main__":
    correr_cliente()
