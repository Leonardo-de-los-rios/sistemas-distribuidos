import os
import time
from multiprocessing import Event, Process, Queue


def sender(queue, event_send, event_recv):
    messages = ["Mensaje 1", "Mensaje 2"]
    
    print("==========================Proceso Emisor (Sender)==========================")
    for message in messages:
        print(f"Proceso Sender {os.getpid()} envia mensaje: {message}")
        queue.put(message)  #Enviar mensaje al receptor
        
        # Señalar al receptor que el mensaje fue enviado
        event_send.set()
        
        # Esperar confirmación del receptor
        event_recv.wait()
        ack = queue.get()
        print(f"Proceso Sender {os.getpid()} recibe ACK: {ack}")
        
        # Resetear eventos para la siguiente iteración
        event_send.clear()
        event_recv.clear()
        
        time.sleep(1)  # Simular un retardo...

def receiver(queue, event_send, event_recv):
    print("\n==========================Proceso Receptor (Receiver)==========================")
    for i in range(2):  # Esperar dos mensajes
        event_send.wait() # Esperar a que el sender envíe el mensaje
        
        message = queue.get()   # Recibir mensaje del sender
        print(f"Proceso Receiver {os.getpid()} recibe mensaje: {message}")
        
        # Enviar confirmación al sender
        ack_message = f"ACK para [{message}]"
        print(f"Proceso Receiver {os.getpid()} envia ACK: {ack_message}")
        queue.put(ack_message)
        
        # Señalar al sender que el ACK fue enviado
        event_recv.set()
        
        time.sleep(1)  # Simular un retardo...

if __name__ == "__main__":
    queue = Queue()  # Cola compartida para mensajes y ACKs
    
    # Eventos para sincronización
    event_send = Event()
    event_recv = Event()

    # Crear procesos de envío y recepción
    p_sender = Process(target=sender, args=(queue, event_send, event_recv))
    p_receiver = Process(target=receiver, args=(queue, event_send, event_recv))

    # Inicio de los procesos
    p_sender.start()
    p_receiver.start()

    # Esperar a que los procesos terminen
    p_sender.join()
    p_receiver.join()
