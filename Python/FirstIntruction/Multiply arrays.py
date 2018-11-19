import random as rand

N = 8
a1 = [[rand.randint(0, 10) for x in range(N)] for y in range(N)]
a2 = [[rand.randint(0, 10) for x in range(N)] for y in range(N)]
a3 = [[0 for x in range(N)] for y in range(N)]

for i in range(len(a1)):  # iteracja po rzędach macierzy a1
    for j in range(len(a2[0])):  # iteracja po kolumnach macierzy a2
        for k in range(len(a2)):  # iteracja po rzedach macierzy a2
            a3[i][j] += a1[i][k] * a2[k][j]

print(a3)