import socket

import Pyro5.api


@Pyro5.api.expose
class ProductoVector:
    def producto_escalar(self, vector, escalar):
        return [v * escalar for v in vector]


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
