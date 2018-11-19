import os

def dirs_and_files(rootdir):
    files = []
    directories = os.listdir(rootdir)
    for dir in directories:
        path = os.path.join(rootdir,dir)
        if os.path.isdir(path):
            files = files + dirs_and_files(path)
        else:
            files.append(path)

    return files


rootdir = input('Podaj sciezke:')
files_dirs = dirs_and_files(rootdir)
print(files_dirs, '\n')