import random as rand

N = 128
array_1 = [[rand.randint(0, 100) for x in range(N)] for y in range(N)]
array_2 = [[rand.randint(0, 100) for x in range(N)] for y in range(N)]
array_3 = [[0 for x in range(N)] for y in range(N)]

for i in range(N):
    for j in range(N):
        array_3[i][j] = array_1[i][j] + array_2[i][j]

print('First 3 columns of first array: {} {} {}'.format(array_1[1][0], array_1[1][1], array_1[1][2]))
print('First 3 columns of second array:{} {} {}'.format(array_2[1][0], array_2[1][1], array_2[1][2]))
print('First 3 columns of third array: {} {} {}'.format(array_3[1][0], array_3[1][1], array_3[1][2]))