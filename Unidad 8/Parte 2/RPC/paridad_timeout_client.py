from concurrent.futures import ThreadPoolExecutor, TimeoutError

import Pyro5.api


def call_remote_method(server_ip, puerto, numero):
    try:
        paridad = Pyro5.api.Proxy(f"PYRO:ejercicio1_rpc@{server_ip}:{puerto}")
        return paridad.es_par(numero)
    except Exception as e:
        return e


def correr_cliente():
    # Se especifica la dirección IP del servidor
    server_ip = input("Ingrese la dirección del servidor: ")
    puerto = input("Ingrese el puerto del servicio: ")

    # Se crea un proxy para el objeto remoto registrado como "ejercicio1_rpc" en la IP y puerto especificados.

    numero = input("Introduce un número: ")

    try:
        numero = int(numero)
    except ValueError:
        numero = float(numero)
    except:
        print("No ingresaste un número.")

    with ThreadPoolExecutor() as executor:
        future = executor.submit(call_remote_method, server_ip, puerto, numero)

        try:
            resultado = future.result(timeout=5)  # Espera hasta 5 segundos
            if isinstance(resultado, Exception):
                print(f"Error Inesperado: {resultado}")
            else:
                print(resultado)
        except TimeoutError:
            print(
                "La llamada al servidor ha superado el tiempo de espera,retransmita el procedimiento."
            )


if __name__ == "__main__":
    correr_cliente()
