import socket

import Pyro5.api


@Pyro5.api.expose
class Materias(object):
    __materias = {
        "lunes": ["Base de Datos", "Ingenieria de Software II"],
        "martes": ["Ingenieria de Software II"],
        "miercoles": ["Base de Datos", "Legislacion Profesional"],
        "jueves": ["Paradigmas de Lenguaje"],
        "viernes": ["Paradigmas de Lenguaje", "Base de Datos"],
    }

    def get_materias(self, dia):
        while dia == "sabado" or dia == "domingo":
            if dia not in self.__materias:
                raise ValueError(f"No hay materias para el día {dia}.")
        else:
            return self.__materias[dia]


def correr_servicio():
    hostname = socket.gethostname()
    direccion_ip = socket.gethostbyname(hostname)
    daemon = Pyro5.api.Daemon(host="0.0.0.0")
    uri = daemon.register(Materias, "ejercicio4_rpc")
    print(f"Servidor listo. URI del objeto: {uri}")
    print(f"Dirección IP del servidor: {direccion_ip}")
    daemon.requestLoop()


if __name__ == "__main__":
    correr_servicio()
