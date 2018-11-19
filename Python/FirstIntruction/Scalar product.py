a = [1,2,12,4]
b = [2,4,2,8]
v = 0

for i in range(len(a)):
    v += a[i]*b[i]

print('Iloczyn skalarny wektora a i b wynosi: {}'.format(v))