from struct import unpack
import errno
import sys
import os

def read_uint32(f):
    return unpack(">I", f.read(4))[0]

def readHeader(f):
    print ("reading header")
    dirfile_size = read_uint32(f)
    filecount = read_uint32(f)

    print ('size of dir file: ' + str(dirfile_size) + ' bytes... \n')
    
    return dirfile_size, filecount
    
def readDirEntry(f):
    offset = read_uint32(f)
    size = read_uint32(f)
    filename_length = read_uint32(f)
    filename_encoded = f.read(filename_length).strip(b"\x00")
    filename = filename_encoded.decode(encoding="shift-jis")
    
    return offset, size, filename

def readArcEntry(offset, size, filename):
    with open(dirToArc(sys.argv[1]), mode='rb') as arcf:
    
        arcf.seek(offset,0)
        fileContents = arcf.read(size)
        
        return fileContents

def writeArcContents(filename, filecontents):
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

def dirToArc(dirFile):
    originName = os.path.splitext(dirFile)
    originName = list(originName)
    if originName[1] == ".dir":
        originName[1] = ".arc"
    return "".join(originName)
   
with open(sys.argv[1], mode='rb') as f:
    fileContent = f.read()
    f.seek(0)

    fileList = []
    
    dirsize, filecount = readHeader(f)
    
    print("reading dirs")
    
    for i in range(filecount):
        offset, size, filename = readDirEntry(f)
        print("File", filename)
        fileList.insert(i, filename)
        writeArcContents(filename, readArcEntry(offset,size,filename))

    f.close()
