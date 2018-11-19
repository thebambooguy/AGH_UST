import random as rand

N = rand.randint(0, 5)
X = [[rand.randint(0, 10) for x in range(N)] for y in range(N)]


def getMatrixMinor(matrix, i, j):
    return [row[:j] + row[j + 1:] for row in (matrix[:i] + matrix[i + 1:])]


def getMatrixDeterminant(matrix):
    if len(matrix) == 2:
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]

    determinant = 0
    for c in range(len(matrix)):
        determinant += ((-1) ** c) * matrix[0][c] * getMatrixDeterminant(getMatrixMinor(matrix, 0, c))
    return determinant


print(X)
det = getMatrixDeterminant(X)
print(det)