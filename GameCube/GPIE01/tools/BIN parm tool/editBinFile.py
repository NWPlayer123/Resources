import struct
import sys
import os

def pack_uint32(data): # PACK IT INTO BIG ENDIAN BYTES
    return struct.pack(">I", int(data))

def read_uint32(fin):
    return struct.unpack('>i', fin.read(4))[0]

def readFile(filename): # JUST READING A FILE HERE
    currF = open(filename, mode = 'rb+')
    currF.seek(0)
    contents = currF.read()
    return contents

fileName = sys.argv[1]
