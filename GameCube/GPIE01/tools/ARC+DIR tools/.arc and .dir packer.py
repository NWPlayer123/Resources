from struct import pack
import errno
import sys
import os

#MISC FUNCTIOSN

def pack_uint32(f): # PACK IT INTO BIG ENDIAN BYTES
    return pack(">I", int(f))

def getSize(filename): # GET THE SIZE OF FILE IN BYTES
    st = os.stat(filename)
    return st.st_size

def readFile(filename): # JUST READING A FILE HERE
    currF = open(filename, mode = 'rb+')
    currF.seek(0)
    contents = currF.read()
    return contents

def write_pad32(f): # IMPORTANT
    next_aligned_pos = (f.tell() + 0x1F) & ~0x1F

    f.write(b"\xCC"*(next_aligned_pos - f.tell()))

def listFilesInDirec(d): # IMPORTANT
    fileList = []
    for dirname, dirnames, filenames in os.walk(d):
        i = 0
        for filename in filenames:
            print(os.path.join(dirname, filename)[2:])
            pathname = os.path.join(dirname, filename)
            fileList.insert(i, pathname[2:].replace("\\", "/"))
            i=i+1
    return fileList

def writeArcStruct(arcF, fileList, fileCount): # WRITING THE ARC STRUCTS ;)
    contents = readFile(fileList[i])
    arcF.write(contents)
    offset = arcF.tell()
    write_pad32(arcF)
    return offset

def writeDirHeaderPass1(dirF, fileCount): # PASS 1 BECAUSE CANT GET FILESIZE WHEN IT HASNT BEEN WRITTEN
    dirF.write(b'\x00\x00\x00\x00')
    dirF.write(pack_uint32(fileCount))

def writeDirHeaderPass2(dirF, fileCount, filenamedir): # REWRITE HEADER ACCOUNTING FOR FILESIZE
    dirF.seek(0)
    dirF.write(pack_uint32(getSize(filenamedir))) # get the size of dirf then pack it and write it]
    dirF.write(pack_uint32(fileCount))

def writeDirStruct(dirF, fileList, fileCount, fileOffset, fileSize):
    for i in range(fileCount):
        offsetArc = fileOffset[i]
        dirF.write(pack_uint32(offsetArc))

        sizeArc = fileSize[i]
        dirF.write(pack_uint32(sizeArc))

        filenameLen = len(fileList[i]) + 2
        dirF.write(pack_uint32(filenameLen))

        currFile = fileList[i]
        dirF.write(currFile.encode() + b'\x00\x00')
        

folderToCompress = str(input("what directory do you want to arc+dir?: \n Make sure it has .\ at the start of it when typing it here!\n"))
fileName = str(input ('what will the file be called?\noptions are:\nblo_eng\nblo_kodomo\nblo_otona\nbomb\nbosses\nbridges\neffshapes\nfl_water\ngates\ngoal\npelletsbin\npikihead\nplants\nrope\ntekikey\ntekipara\ntekis\nufopartsbin\nwater\nweeds\n'))

fileList = listFilesInDirec(folderToCompress)
fileOffset = []
fileSize = []

fileCount = len(fileList)

fileNameDir = fileName + ".dir"
fileNameArc = fileName + ".arc"
#list idea: filename list, offset list and size list.
with open(fileNameArc, mode = 'wb+') as f:
    f.seek(0)
    print("created arc file ok... writing...")
    for i in range(fileCount):
        start_offset = f.tell()
        offset = writeArcStruct(f,fileList, fileCount)
        fileOffset.insert(i, start_offset)
        filesyze = offset - start_offset
        fileSize.insert(i, filesyze)
        
with open(fileNameDir, mode = 'wb+') as f:
    f.seek(0)
    print("created dir file ok... writing...")
    print(str(fileSize))
    print(str(fileOffset))
    writeDirHeaderPass1(f, fileCount)
    writeDirStruct(f,fileList,fileCount, fileOffset, fileSize)
    writeDirHeaderPass2(f, fileCount, fileNameDir)    
