#Reading Keyboard Input
text = input('Napisz cos: ')
print('Operacje wejscia i wyjscia są super. Twój tekst to: {}'.format(text))

#Opening and Closing Files

file_handle = open('IO operations.txt','w+')
print('Name of file: ', file_handle.name)
print('Closed or not: ', file_handle.closed)
print('Opening mode: ', file_handle.mode)

filetext = file_handle.read()
print(filetext)
filetext += 'Teraz to co pobrałem z klawiatury zapiszę do pliku. Patrz: ' + text

file_handle.write(filetext)
file_handle.close()

