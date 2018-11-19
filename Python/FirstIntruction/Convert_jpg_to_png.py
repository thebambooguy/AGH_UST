import os

files = os.listdir()
for file in files:
    name, ext = file.split('.')
    if ext == 'jpg':
        os.rename(file, name + ".png")

print(files)