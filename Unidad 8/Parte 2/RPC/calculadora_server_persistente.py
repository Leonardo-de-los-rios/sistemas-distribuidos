import json
import os
import socket

import Pyro5.api

file_persistente = "operaciones_calculadora.json"


def leer_datos():
    if os.path.exists(file_persistente):
        with open(file_persistente, "r") as file:
            try:
                return json.load(file)
            except json.JSONDecodeError:
                return {}
    return {}


def guardar_datos(operaciones):
    with open(file_persistente, "w") as file:
        json.dump(operaciones, file)


@Pyro5.api.expose
class Calculadora(object):
    def __init__(self):
        self.__operaciones = leer_datos()

    def suma(self, id_cliente, op1, op2):
        resultado = op1 + op2
        self.registrar_operacion(id_cliente, op1, op2, resultado)
        return f"[{id_cliente}] Resultado de la suma: {resultado}"

    def resta(self, id_cliente, op1, op2):
        resultado = op1 - op2
        self.registrar_operacion(id_cliente, op1, op2, resultado)
        return f"[{id_cliente}] Resultado de la resta: {resultado}"

    def divide(self, id_cliente, op1, op2):
        try:
            resultado = op1 / op2
            self.registrar_operacion(id_cliente, op1, op2, resultado)
            return f"[{id_cliente}] Resultado de la division: {resultado}"
        except ZeroDivisionError:
            return "No se puede realizar la division por cero"

    def multiplica(self, id_cliente, op1, op2):
        resultado = op1 * op2
        self.registrar_operacion(id_cliente, op1, op2, resultado)
        return f"[{id_cliente}] Resultado del producto: {resultado}"

    def registrar_operacion(self, id_cliente, op1, op2, resultado):
        self.__operaciones[id_cliente] = {
            "numero1": op1,
            "numero2": op2,
            "resultado": resultado,
        }
        guardar_datos(self.__operaciones)

    def get_resultado_pendiente(self, id_cliente):
        resultado_pendiente = self.__operaciones.pop(id_cliente, None)
        if resultado_pendiente:
            # Guarda la actualizacion sin operaciones pendientes
            guardar_datos(self.__operaciones)
            return resultado_pendiente["resultado"]
        return None


def correr_servicio():
    # Obtener la dirección IP de la máquina del servidor
    hostname = socket.gethostname()
    direccion_ip = socket.gethostbyname(hostname)

    # Daemon Pyro es el componente del servidor Pyro que escucha las solicitudes RPC.
    daemon = Pyro5.api.Daemon(host="0.0.0.0")

    # Registrar la clase Calculadora como un objeto Pyro
    uri = daemon.register(Calculadora, "ejercicio2_rpc")
    print(f"Servidor listo. URI del objeto: {uri}")
    print(f"Dirección IP del servidor: {direccion_ip}")

    # Mantener el servidor corriendo para escuchar las llamadas RPC
    daemon.requestLoop()


if __name__ == "__main__":
    correr_servicio()
