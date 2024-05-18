import socket

def proceso_servidor():
    serverName = 'localhost'
    serverPort = 12000
    # Se crea el socket Servidor TCP/IP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Se define el ID del Servidor
    server_id = input("\nIngrese su ID de Servidor: ")

    # Se enlaza el socket al puerto
    # bind es la forma de definir un evento (todo paquete enviado a esta ip y puerto, lo recibe el server)
    server_socket.bind((serverName, serverPort)) 
        
    # Espera pasiva ante conexiones TCP entrantes
    # 1 indica que el numero maximo de conexiones simultaneas en la cola es uno.
    server_socket.listen(1)        
    print(f"Servidor {serverName} esperando conexiones en el puerto {serverPort}...")
    
    # Se acepta y se crea la conexion TCP con socket cliente
    conectionSocket, addr = server_socket.accept()
    print(f"Conexión establecida con {addr}")

    # Recibe el ID del cliente
    # Recibe el paquete msg decodificado de tipo byte a str. Recv especifica tamaño del buffer TCP
    client_id = conectionSocket.recv(1024).decode() 
    print(f"ID recibido del cliente: {client_id}")

    # Se envia el ID del servidor al cliente
    conectionSocket.send(server_id.encode())
    # Cierre de la conexión TCP
    conectionSocket.close()

if __name__ == "__main__":
    proceso_servidor()