import socket
import time

import Pyro5.api


@Pyro5.api.expose  # Decorador que expone la clase remota
class Calculadora(object):
    def suma(self, op1, op2):
        return f"Resultado de la suma: {op1 + op2}"

    def resta(self, op1, op2):
        return f"Resultado de la resta: {op1 - op2}"

    def divide(self, op1, op2):
        # Para producir explicitamente una simulacion de fallo en el servidor
        while op2 == 0:
            print("...")
            time.sleep(6)
            break
        if op2 == 0:
            self.shutdown()
        else:
            return f"Resultado de la division: {op1 / op2}"
        """try: 
            return f'Resultado de la division: {op1 / op2}'
        except ZeroDivisionError:
            return 'No se puede realizar la division por cero'"""

    def multiplica(self, op1, op2):
        return f"Resultado del producto: {op1 * op2}"

    def shutdown(self):
        print("Servidor falla ante bucle infinito.")
        Pyro5.api.current_context().daemon.shutdown()


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
