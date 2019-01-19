from struct import unpack
import errno
import sys
import os

def read_uint32(f):
    return unpack(">I", f.read(4))[0]

def readHeader(f):
    print ("reading header")
    structs = read_uint32(f)

    print ('structs: ' + str(structs) + '\n')
    
    return structs
    
def readEntry(f):
    indicator = read_uint32(f) #0x00	4	File content indicator
    size = read_uint32(f) #0x04	4	Enclosed file size
    filename_length = read_uint32(f) #0x08	4	Mock-directory string length
    filename_encoded = f.read(filename_length).strip(b"\x00") #0x0c	0x08 value	Mock-directory path
    filename = filename_encoded.decode(encoding="shift-jis")

    entry = f.read(size)
    
    return size, filename, entry

def writeContents(filename, filecontents):
    for file in fileList:
        dir = os.path.dirname(file)
        
        try:
            if not os.path.exists(dir):
                os.makedirs(dir)
                
            if not os.path.isfile(file):
                out = open (filename, mode = 'wb+')
                out.seek(0)
                out.write(filecontents)
                
        except OSError as e:
            if e.errno != errno.EEXIST:
                raise
   
with open(sys.argv[1], mode='rb') as f:
    fileContent = f.read()
    f.seek(0)

    fileList = []
    
    filecount = readHeader(f)
    
    print("reading bundle...")
    
    for i in range(filecount):
        size, filename, entry  = readEntry(f)
        print("File: ", filename)
        print("size: ", size)
        fileList.insert(i, filename)
        writeContents(filename, entry)

    f.close()
