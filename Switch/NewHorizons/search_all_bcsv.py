from os import listdir

bcsv_path = "./Bcsv"
search_str = "TopsTexTopOuterLChristmas"

for name in listdir(bcsv_path):
    if name.endswith(".bcsv"):
        data = open("%s/%s" % (bcsv_path, name), "rb").read()
        if search_str.lower() in data.lower():
            print(name)

