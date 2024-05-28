import json
import os
import socket

import Pyro5.api

# Archivo donde se guardarán las operaciones
file_persistente = "operaciones_vector.json"


def leer_datos():
    if os.path.exists(file_persistente):
        with open(file_persistente, "r") as file:
            try:
                return json.load(file)
            except json.JSONDecodeError:
                return (
                    {}
                )  # Retorna un diccionario vacío si el archivo está vacío o no es válido
    return {}


def guardar_datos(operaciones):
    with open(file_persistente, "w") as file:
        json.dump(operaciones, file)


@Pyro5.api.expose
class ProductoVector(object):
    def __init__(self):
        self.__operaciones = leer_datos()

    def producto_escalar(self, id_cliente, vector, escalar):
        """# Verificar si ya hay una operación pendiente para este cliente
        if id_cliente in self.__operaciones:
            print(f"Se proporciona la respuesta pendiente a {id_cliente}")
            return self.__operaciones[id_cliente]['resultado']"""

        # Si no hay operaciones pendientes, realiza la nueva operacion
        resultado = [v * escalar for v in vector]
        self.__operaciones[id_cliente] = {
            "vector": vector,
            "escalar": escalar,
            "resultado": resultado,
        }
        guardar_datos(self.__operaciones)
        return resultado

    def get_resultado_pendiente(self, id_cliente):
        resultado_pendiente = self.__operaciones.pop(id_cliente, None)
        if resultado_pendiente:
            guardar_datos(self.__operaciones)  # Guarda la actualizacion
            return resultado_pendiente["resultado"]
        return None


def correr_servicio():
    hostname = socket.gethostname()
    direccion_ip = socket.gethostbyname(hostname)
    daemon = Pyro5.api.Daemon(host="0.0.0.0")
    uri = daemon.register(ProductoVector, "ejercicio3_rpc")
    print(f"Servidor listo. URI del objeto: {uri}")
    print(f"Dirección IP del servidor: {direccion_ip}")
    daemon.requestLoop()


if __name__ == "__main__":
    correr_servicio()
