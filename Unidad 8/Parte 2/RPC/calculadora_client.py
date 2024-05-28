import Pyro5.api


def correr_cliente():
    # Se especifica la dirección IP del servidor
    server_ip = input("Ingrese la dirección del servidor: ")
    puerto = input("Ingrese el puerto del servicio: ")

    # Se crea un proxy para el objeto remoto registrado en la IP y puerto especificados.
    calculadora_cliente = Pyro5.api.Proxy(f"PYRO:ejercicio2_rpc@{server_ip}:{puerto}")

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
        if operacion == 1:
            resultado = calculadora_cliente.suma(op1, op2)
        elif operacion == 2:
            resultado = calculadora_cliente.resta(op1, op2)
        elif operacion == 3:
            resultado = calculadora_cliente.divide(op1, op2)
        elif operacion == 4:
            resultado = calculadora_cliente.multiplica(op1, op2)
        else:
            print("Adios Calculadora...")

        print(resultado)
        print("=" * 100)
        print("Operaciones:")
        print("1: Suma")
        print("2: Resta")
        print("3: Division")
        print("4: Producto")
        print("0: Salir")

        operacion = int(input("Ingrese la operacion a efectuar: "))
    else:
        print("No ingresaste una opción correcta.\n")


if __name__ == "__main__":
    correr_cliente()
