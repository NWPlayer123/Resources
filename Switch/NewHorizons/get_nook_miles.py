from bcsv_reader import BCSV
from msbt_reader import MSBT

ver = 200
bcsv_path = "../data%s/Bcsv" % ver
msbt_path = "../data%s/Message/USen/" % ver
output_name = "get_nook_miles%s.txt" % ver

labels, text = MSBT().read_msbt(msbt_path + "/System_USen/NookMilage/NookMilage_Keyword_Modifier.msbt")
modifier_lookup = {}
for entry in labels:
    try:
        assert len(entry[0].split("_")) == 2
        uid, num = entry[0].split("_")
        uid = int(uid)
        num = int(num)
        modifier_lookup[entry[0]] = text[entry[1]][0]
        #print(entry[0], text[entry[1]])
    except: pass

labels, text = MSBT().read_msbt(msbt_path + "/System_USen/NookMilage/NookMilage_Keyword_Noun.msbt")
noun_lookup = {}
for entry in labels:
    try:
        assert len(entry[0].split("_")) == 3
        uid, level, num = entry[0].split("_")
        uid = int(uid)
        level = int(level)
        num = int(num)
        noun_lookup[entry[0]] = text[entry[1]][0]
        #print(entry[0], text[entry[1]])
    except: pass

labels, text = MSBT().read_msbt(msbt_path + "/System_USen/NookMilage/NookMilage_List.msbt")
name_lookup = {}
for entry in labels:
    try:
        assert len(entry[0].split("_")) == 2
        uid, isdesc = entry[0].split("_")
        uid = int(uid)
        isdesc = int(isdesc)
        name_lookup[entry[0]] = text[entry[1]][0]
        #print(entry[0], text[entry[1]])
    except: pass

#get normal nook miles stuff
nookdata = BCSV().read_bcsv(bcsv_path + "/EventFlagsLifeSupportAchievementParam.bcsv")
sortme = []
lookup = {}
with open(output_name, "wb") as o:
    o.write('numItems | numMiles | "Modifier" | "Noun" (x2 sometimes, split with "+")\r\n')
    for entry in nookdata:
        MaxLevel = entry[0x1BE772F0]
        UniqueID  = entry[0x54706054] #text index
        IsSpecial = entry[0x895442DC]

        numItems = [entry[0xce0933fc], entry[0x89a9492c], entry[0xb4c9609c], entry[0x06e9bc8c], entry[0x3b89953c], 0] #MaxValue1-5
        numMiles = [entry[0x4e7f3849], entry[0x09df4299], entry[0x34bf6b29], entry[0x869fb739], entry[0xbbff9e89], entry[0xfc5fe459]] #Reward1-6
        
        Key = entry[0x45F320F2].rstrip('\0')
        Name = entry[0x85CF1615].rstrip('\0')
        o.write(name_lookup["%03d_%01d" % (UniqueID, 0)].encode("UTF-8") + "\r\n")
        o.write(Key + "\r\n")
        o.write(Name + "\r\n")
        o.write(name_lookup["%03d_%01d" % (UniqueID, 1)].encode("UTF-8") + "\r\n")
        for i in range(MaxLevel):
            modifier = modifier_lookup["%03d_%02d" % (UniqueID, i)]
            noun1 = noun_lookup["%03d_%02d_%01d" % (UniqueID, i, 0)]
            noun2 = noun_lookup["%03d_%02d_%01d" % (UniqueID, i, 1)]
            if noun2 != "":
                o.write("%8d | %4d | %s | %s + %s\r\n" % (numItems[i], numMiles[i], modifier, noun1, noun2))
            else:
                o.write("%8d | %4d | %s | %s\r\n" % (numItems[i], numMiles[i], modifier, noun1))
        o.write("\r\n")
    sortme.append([UniqueID, Key])
    lookup[UniqueID] = [Key, name_lookup["%03d_%01d" % (UniqueID, 0)]]

    '''uid = int(entry[0].split("_")[0])
    #level = entry[0].split("_")[1]'''
    '''print(lookup[uid])
    print(text[entry[1]])'''
    '''uid = int(entry[0].split("_")[0])
    level = int(entry[0].split("_")[1])'''

'''sortme.sort(key=lambda x: x[0])
for entry in sortme:
    print("0x%03X %04d %s" % (entry[0] + 1, entry[0] + 1, entry[1]))'''
'''for i in range(93):
    try: print("0x%03X %04d %s | %s" % (i, i, lookup[i][0], lookup[i][1]))
    except: print("0x%03X %04d %s" % (i, i, "UNUSED"))'''
