file = open("9.txt","r")
words_to_remove = ['nigdy', 'dlaczego', 'się', 'i', 'oraz', 'Nigdy', 'Dlaczego']

words = list(file.read().split())
print(words)

for word in words:
    if word in words_to_remove:
        words.remove(word)

print("\n")
print(words)