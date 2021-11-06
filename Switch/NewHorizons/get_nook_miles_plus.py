from bcsv_reader import BCSV
from msbt_reader import MSBT
from os import listdir
import sys, string

ver = 200
bcsv_path = "../data%s/Bcsv" % ver
msg_path = "../data%s/Message/USen/" % ver
output_name = "get_nook_miles_plus%s.txt" % ver

#grab item ids and names
item_strings = []
item_id2str = {}
item_str2id = {}
for filename in listdir(msg_path + "/String_USen/Item/"):
    if filename.endswith(".msbt"):
        labels, text = MSBT().read_msbt("%s/String_USen/Item/%s" % (msg_path, filename))
        for entry in labels:
            if not entry[0].endswith(b"_pl"): #filter out plural
                itemid = int(entry[0].split(b"_")[1]) #Rug_07322 -> decimal 7322
                itemname = text[entry[1]][0]
                item_strings.append([itemid, itemname])
                item_id2str[itemid] = itemname
                item_str2id[itemname] = itemid

labels, text = MSBT().read_msbt(msg_path + "/System_USen/NookMilage/NookMilagePlus_Title.msbt")
name_lookup = {}
for entry in labels:
    name_lookup[entry[0]] = text[entry[1]][0]
    #print(entry[0], text[entry[1]][0])

#get normal nook miles stuff
nookdata = BCSV().read_bcsv(bcsv_path + "/EventFlagsLifeSupportDailyParam.bcsv")
#sortme = []
lookup = {}
#print('numItems | numMiles | "Modifier" | "Noun" (x2 sometimes, split with "+")')
with open(output_name, "wb") as o:
    for entry in nookdata:
        UniqueID = entry[0x74f1f060] #text index
        ItemNameUniqueID = entry[0xc33a894e] #check if not 65534
        if ItemNameUniqueID == 65534:
            o.write(name_lookup["%03d" % UniqueID].encode("UTF-8") + "\r\n")
        else:
            #print(UniqueID)
            o.write("%s%s\r\n" % (name_lookup["%03d" % UniqueID], item_id2str[ItemNameUniqueID]))
    '''MaxLevel = entry[0x1BE772F0]
    UniqueID  = entry[0x54706054] #text index
    IsSpecial = entry[0x895442DC]

    numItems = [entry[0xce0933fc], entry[0x89a9492c], entry[0xb4c9609c], entry[0x06e9bc8c], entry[0x3b89953c], 0]
    numMiles = [entry[0x4e7f3849], entry[0x09df4299], entry[0x34bf6b29], entry[0x869fb739], entry[0xbbff9e89], entry[0xfc5fe459]]
    
    InternalName = entry[0x45F320F2].rstrip('\0')
    InternalDesc = entry[0x85CF1615].rstrip('\0')
    print(name_lookup["%03d_%01d" % (UniqueID, 0)].encode("UTF-8"))
    print(InternalName)
    print(InternalDesc)
    print(name_lookup["%03d_%01d" % (UniqueID, 1)].encode("UTF-8"))
    for i in range(MaxLevel):
        modifier = modifier_lookup["%03d_%02d" % (UniqueID, i)]
        noun1 = noun_lookup["%03d_%02d_%01d" % (UniqueID, i, 0)]
        noun2 = noun_lookup["%03d_%02d_%01d" % (UniqueID, i, 1)]
        if noun2 != "":
            print("%8d | %4d | %s | %s + %s" % (numItems[i], numMiles[i], modifier, noun1, noun2))
        else:
            print("%8d | %4d | %s | %s" % (numItems[i], numMiles[i], modifier, noun1))
    print'''
    '''print(InternalName)
    print(InternalDesc)
    for i in range(MaxLevel):
        print("%8d %4d" % (numItems[i], numMiles[i]))
    print'''
    #lookup[UniqueID] = InternalName

    '''uid = int(entry[0].split("_")[0])
    #level = entry[0].split("_")[1]'''
    '''print(lookup[uid])
    print(text[entry[1]])'''
    '''uid = int(entry[0].split("_")[0])
    level = int(entry[0].split("_")[1])'''
'''sortme.append([entry[0x54706054], entry])

sortme.sort(key=lambda x: x[0])
for entry in sortme:
    entry = entry[1]
    print(entry[0x45F320F2])'''
