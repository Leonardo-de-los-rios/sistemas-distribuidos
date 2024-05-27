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
        else:
            return calculadora_cliente.multiplica(op1, op2)
    except Exception as e:
        return e


def correr_cliente():
    # Se especifica la dirección IP del servidor
    server_ip = input("Ingrese la dirección del servidor: ")
    puerto = input("Ingrese el puerto del servicio: ")

    # Se crea un proxy para el objeto remoto registrado como "ejercicio1_rpc" en la IP y puerto especificados.

    operacion = int(
        input(
            "Ingrese la operacion a efectuar (1:Suma,2:Resta,3:Division,4:Producto,Cualquier otro numero:Salir)\n"
        )
    )
    while operacion == 1 or operacion == 2 or operacion == 3 or operacion == 4:
        print(
            "==================================================================================================="
        )
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
                    print(
                        "==================================================================================================="
                    )
            except TimeoutError:
                print(
                    "La llamada al servidor ha superado el tiempo de espera,retransmita el procedimiento."
                )
                break

        operacion = int(
            input(
                "Ingrese la operacion a efectuar (1:Suma,2:Resta,3:Division,4:Producto,Cualquier otro numero:Salir)\n"
            )
        )
    else:
        print("Adios Calculadora...")


if __name__ == "__main__":
    correr_cliente()
