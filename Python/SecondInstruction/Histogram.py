import random
from multiprocessing import Pool

def create_histogram(size):
    l = []
    for i in range(0, size):
        l.append(random.randint(0, 100))

    histogram = [0] * (size + 1)
    for j in l:
        histogram[j] = histogram[j] + 1
    return histogram


p = Pool()
hist = p.map(create_histogram, (500000,) ) #pool.map tylko jeden argument przyjmuje i musi to być tupla