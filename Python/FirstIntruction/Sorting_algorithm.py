import random

numbers = []

while len(numbers) < 51:
    number = random.randint(0, 1000)
    numbers.append(number)

print(numbers)

for iter_num in range(len(numbers) - 1, 0, -1):
    for number in range(iter_num):
        if numbers[number + 1] > numbers[number]:
            temp = numbers[number]
            numbers[number] = numbers[number + 1]
            numbers[number + 1] = temp

print("My own sorting argument:")
print(numbers)
