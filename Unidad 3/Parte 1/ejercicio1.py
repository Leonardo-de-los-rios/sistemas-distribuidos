lista = [1, 1]

for i in range(8):
    lista.append(lista[i] + lista[i + 1])

print("Lista con diez elementos: ", lista)
