matriz1 = [[1, 2], [3, 4]]
matriz2 = [[5, 6], [7, 8]]
resultante = [[0, 0], [0, 0]]


for i in range(len(matriz1)):
    for j in range(len(matriz1)):
        for k in range(len(matriz2)):
            resultante[i][j] += matriz1[i][k] * matriz2[k][j]

print("Matriz resultante: ", resultante)
