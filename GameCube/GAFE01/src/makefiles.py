from os import listdir, mkdir
from os.path import exists

base = b"pad"

if not exists(base):
    mkdir(base)
    
names = \
    ['Pad.c', 'Padclamp.c']



for name in names:
    with open(base + "/" + name, "wb") as f:
        pass
