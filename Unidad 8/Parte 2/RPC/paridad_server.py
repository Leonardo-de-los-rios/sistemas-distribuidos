import socket
import time

import Pyro5.api


@Pyro5.api.expose
class Paridad(object):
    def es_par(self, numero):
        try:
            numero = int(numero)
        except ValueError:
            pass

        while type(numero) != int:
            print(
                "..."
            )  # Simulacion de que el servidor entra en un bucle infinito al procesar numero -1
            time.sleep(6)
            break
        if type(numero) != int:
            self.shutdown()  # Despues de (6 seg por ej) de que el servidor no responde, se corta el servicio RPC

        if numero % 2 == 0:
            return f"El número {numero} es par."
        else:
            return f"El número {numero} es impar."

    def shutdown(self):
        print("Servidor falla ante bucle infinito.")
        Pyro5.api.current_context().daemon.shutdown()


def correr_servicio():
    # Obtener la dirección IP de la máquina del servidor
    hostname = socket.gethostname()
    direccion_ip = socket.gethostbyname(hostname)

    # Daemon Pyro es el componente del servidor Pyro que escucha las solicitudes RPC.
    # En este caso, escucha en todas las interfaces de red ("0.0.0.0")
    daemon = Pyro5.api.Daemon(host="0.0.0.0")

    # Registrar la clase Paridad como un objeto Pyro
    # daemon.register expone la clase Paridad en el servidor bajo el nombre "ejercicio1_rpc".
    uri = daemon.register(Paridad, "ejercicio1_rpc")
    print(f"Servidor listo. URI del objeto: {uri}")
    print(f"Dirección IP del servidor: {direccion_ip}")

    # Mantener el servidor corriendo para escuchar las llamadas RPC
    try:
        daemon.requestLoop()
    finally:
        daemon.close()


if __name__ == "__main__":
    correr_servicio()
