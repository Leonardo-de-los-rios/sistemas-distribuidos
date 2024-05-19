import socket


def proceso_cliente():
    serverName = 'localhost'
    serverPort = 12000

    # Se crea el socket TCP/IP (AF_INET especifica que la red subyacente es IPv4, 
    # SOCK_STREAM me indica que se usuara TCP)
    cliente_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Se define el ID del Cliente
    cliente_id = input("\nIngrese su ID de Cliente: ")

    # Conexion al servidor
    cliente_socket.connect((serverName, serverPort))
    print(f"Conectado al servidor {serverName} en el puerto {serverPort}...")

    # Cliente envia su ID al servidor
    cliente_socket.send(cliente_id.encode())  #envio del mensaje str codificado en bytes

    # Se recibe el ID del servidor
    # Recibe el paquete msg decodificado de tipo byte a str. Recv especifica tamaño del buffer TCP
    server_id = cliente_socket.recv(1024).decode()
    print(f"ID recibido del servidor: {server_id}")

    # Cierre de la conexión
    cliente_socket.close()

if __name__ == "__main__":
    proceso_cliente()