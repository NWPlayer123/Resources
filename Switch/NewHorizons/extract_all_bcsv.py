from bcsv_reader import BCSV
from os import listdir, makedirs
from os.path import exists

bcsv_path = "./Bcsv"
text_path = "./Text"

if not exists(text_path): makedirs(text_path) #make output path if it doesn't exist
for name in listdir(bcsv_path):
    if name.endswith(".bcsv"):
        data = BCSV().read_bcsv("%s/%s" % (bcsv_path, name))
        with open("%s/%s.txt" % (text_path, ".".join(name.split(".")[:-1])), "wb") as o:
            for i in range(1, len(data) + 1): #start at entry 1
                entry = data[i-1]
                o.write("Entry_%d:\r\n" % i)
                for key in entry.keys(): #do either string or hex, stupid format but easy to read
                    if type(entry[key]) == str:
                        string = entry[key].partition('\0')[0] #TODO: better way?
                        o.write("    %08X: %s\r\n" % (key, string))
                    else:
                        o.write("    %08X: %X\r\n" % (key, entry[key]))
                o.write("\r\n")
