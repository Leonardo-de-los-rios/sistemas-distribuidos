from concurrent.futures import ThreadPoolExecutor, TimeoutError

import Pyro5.api


def call_remote_method(server_ip, puerto, operacion, op1, op2):
    try:
        calculadora_cliente = Pyro5.api.Proxy(
            f"PYRO:ejercicio2_rpc@{server_ip}:{puerto}"
        )
        if operacion == 1:
            return calculadora_cliente.suma(op1, op2)
        elif operacion == 2:
            return calculadora_cliente.resta(op1, op2)
        elif operacion == 3:
            return calculadora_cliente.divide(op1, op2)
        elif operacion == 4:
            return calculadora_cliente.multiplica(op1, op2)
        else:
            print("Adios Calculadora...")
    except Exception as e:
        return e


def correr_cliente():
    # Se especifica la dirección IP del servidor
    server_ip = input("Ingrese la dirección del servidor: ")
    puerto = input("Ingrese el puerto del servicio: ")

    # Se crea un proxy para el objeto remoto registrado como "ejercicio1_rpc" en la IP y puerto especificados.

    print("Calculadora Premium\n")
    print("Operaciones:")
    print("1: Suma")
    print("2: Resta")
    print("3: Division")
    print("4: Producto")
    print("0: Salir")
    # Se envian los numeros y la operacion al servidor
    operacion = int(input("Ingrese la operacion a efectuar: "))

    while operacion in [1, 2, 3, 4, 0]:
        print("=" * 100)
        op1 = int(input("Ingrese el operando 1: "))
        op2 = int(input("Ingrese el operando 2: "))
        with ThreadPoolExecutor() as executor:
            future = executor.submit(
                call_remote_method, server_ip, puerto, operacion, op1, op2
            )

            try:
                resultado = future.result(timeout=5)  # Espera hasta 5 segundos
                if isinstance(resultado, Exception):
                    print(f"Error Inesperado: {resultado}")
                    break
                else:
                    print(resultado)
                    print("=" * 100)

            except TimeoutError:
                print(
                    "La llamada al servidor ha superado el tiempo de espera,retransmita el procedimiento."
                )
                break

        print("Operaciones:")
        print("1: Suma")
        print("2: Resta")
        print("3: Division")
        print("4: Producto")
        print("0: Salir")
        # Se envian los numeros y la operacion al servidor
        operacion = int(input("Ingrese la operacion a efectuar: "))
    else:
        print("No ingresaste una opción correcta.\n")


if __name__ == "__main__":
    correr_cliente()
