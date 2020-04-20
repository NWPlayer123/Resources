from struct import pack
import errno
import sys
import os

#MISC FUNCTIOSN

def pack_uint32(f): # PACK IT INTO BIG ENDIAN BYTES
    return pack(">I", int(f))


def writeHeader(dirF, fileCount): # WRITING A HEADER YEEET
    dirF.write(pack_uint32(fileCount))

def getSize(filename): # GET THE SIZE OF FILE IN BYTES
    st = os.stat(filename)
    return st.st_size

def writeFile(file, fileList, fileCount):
    contents = readFile(fileList[i])
    file.write(contents)

def getOffset(file):
    offset = file.tell()
    return offset

def readFile(filename): # JUST READING A FILE HERE
    currF = open(filename, mode = 'rb+')
    currF.seek(0)
    contents = currF.read()
    return contents

def returnIndicator(fextension): # RETURN THE INDICATOR TYPE
    if fextension.lower == ".pcr": #0
        return 0
    if fextension.lower() == ".bti": #1
        return 1
    if fextension.lower() == ".dca": #2
        return 2
    if fextension.lower() == ".dck": #3
        return 3
    else:
        exit(0) # ya dummy you did something wrong :((((
        
def listFilesInDirec(d): # LIST FILES AND INSERT EXTENSION INTO LIST
    fileList = []
    fileIndi = []
    for dirname, dirnames, filenames in os.walk(d):
        i = 0
        for filename in filenames:
            print(os.path.join(dirname, filename)[2:])
            pathname = os.path.join(dirname, filename)[2:]
            pathname  = pathname.replace("\\", "/")
            fileList.insert(i, pathname)
            fileIndi.insert(i, returnIndicator(os.path.splitext(os.path.basename(filename))[1])) # get extension of file and run it through return indicator, which then returns a value
            print(fileIndi[i])
            i=i+1
    return fileList, fileIndi

def writeStruct(file, fileList, fileCount, fileIndi, times): # write a struct you can read right?
    indicator = fileIndi[i]
    file.write(pack_uint32(indicator))

    file.write(pack_uint32(int(getSize(fileList[i]))))

    if times < 1:
        filenameLen = len(fileList[i]) + 3
    else:
        filenameLen = len(fileList[i])
    file.write(pack_uint32(filenameLen))

    currFile = fileList[i]
    if times < 1:
        file.write(currFile.encode() + b'\x00\x00\x00')
    else:
        file.write(currFile.encode())

folderToCompress = str(input("what directory do you want to bundle?: "))
fileName = str(input ('what will the file be called?: '))

fileList, fileIndi = listFilesInDirec(folderToCompress)
fileSize = []
fileOffset = []

fileCount = len(fileList)
#list idea: filename list, offset list and size list.
with open(fileName, mode = 'wb+') as f:
    f.seek(0)
    writeHeader(f, fileCount)
    print("created file ok... writing...")
    times = 0
    for i in range(fileCount):
        writeStruct(f, fileList, fileCount, fileIndi, times)
        writeFile(f, fileList, fileCount)
        times = times + 1
