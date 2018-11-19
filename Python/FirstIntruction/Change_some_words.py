file = open("9.txt","r")
change_words= {'i': 'oraz', 'oraz': 'i', 'nigdy': 'prawie nigdy', 'dlaczego': 'czemu','Nigdy': 'Prawie nigdy' }

words = list(file.read().split())
print(words)

for i,word in enumerate(words):
    if word in change_words:
            words[i] = change_words[word]

print('\n')
new_text = ' '.join(words)
print(new_text)