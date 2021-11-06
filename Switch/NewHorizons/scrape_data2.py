from bcsv_reader import BCSV
from msbt_reader import MSBT
from os import listdir
import sys, string

#ease-of-use strings
ver = 200
bcsv_path = "../data%s/Bcsv" % ver
msg_path = "../data%s/Message/USen/" % ver
output_name = "scrape_data%s.txt" % ver
output_name2 = "scrape_remake%s.txt" % ver

#grab item ids and names
itemname_lookup = {}
for filename in listdir(msg_path + "/String_USen/Item/"):
    if filename.endswith(".msbt"):
        labels, text = MSBT().read_msbt("%s/String_USen/Item/%s" % (msg_path, filename))
        for entry in labels:
            if not entry[0].endswith(b"_pl"): #filter out plural
                itemid = int(entry[0].split(b"_")[1]) #Rug_07322 -> decimal 7322
                itemname = text[entry[1]][0]
                itemname_lookup[itemid] = itemname

#grab cloth group ids and names
clothid_lookup = {}
for filename in listdir(msg_path + "/String_USen/Outfit/GroupName/"):
    if filename.endswith(".msbt"):
        labels, text = MSBT().read_msbt("%s/String_USen/Outfit/GroupName/%s" % (msg_path, filename))
        for entry in labels:
            clothid = int(entry[0])
            itemname = text[entry[1]][0]
            clothid_lookup[clothid] = itemname

#grab cloth color ids and names
cloth_color_data = {}
for filename in listdir(msg_path + "/String_USen/Outfit/GroupColor/"):
    if filename.endswith(".msbt"):
        labels, text = MSBT().read_msbt("%s/String_USen/Outfit/GroupColor/%s" % (msg_path, filename))
        for entry in labels:
            label = entry[0].split("_")
            ClothID = int(label[0])
            ItemID = int(label[2])
            ItemColor = text[entry[1]][0]
            try: cloth_color_data[ClothID].append([ItemID, ItemColor]) #append
            except: cloth_color_data[ClothID] = [[ItemID, ItemColor]] #create

#process cloth data
clothname_lookup = {}
for key in cloth_color_data.keys():
    entry = cloth_color_data[key]
    if entry[0][1] not in ["No Variations", "Hair Color"]:
        for variant in entry:
            clothname_lookup[variant[0]] = "%s / %s" % (variant[1], clothid_lookup[key])
    else:
        clothname_lookup[entry[0][0]] = "%s" % clothid_lookup[key]

#grab remake strings
bodycolor_lookup = {}
labels, text = MSBT().read_msbt("%s/String_USen/Remake/STR_Remake_BodyColor.msbt" % msg_path)
for entry in labels:
    label = entry[0].split("_")
    itemtype = label[0]
    itemid = int(label[1])
    colorid = int(label[2])
    colorname = text[entry[1]][0]
    try: bodycolor_lookup[itemid][1].append([colorid, colorname])
    except: bodycolor_lookup[itemid] = [itemtype, [[colorid, colorname]]]

fabriccolor_lookup = {}
labels, text = MSBT().read_msbt("%s/String_USen/Remake/STR_Remake_FabricColor.msbt" % msg_path)
for entry in labels:
    label = entry[0].split("_")
    itemtype = label[0]
    itemid = int(label[1])
    colorid = int(label[2])
    colorname = text[entry[1]][0]
    try: fabriccolor_lookup[itemid][1].append([colorid, colorname])
    except: fabriccolor_lookup[itemid] = [itemtype, [[colorid, colorname]]]

#grab remake data
remake_data = BCSV().read_bcsv(bcsv_path + "/ItemRemake.bcsv")
remake_lookup = {}
for entry in remake_data:
    ItemUniqueID = entry[0xFD9AF1E1]
    UniqueID = entry[0x54706054]
    RemakeKitNum = entry[0x29ECB129]
    
    ReBodyPattern0Color0 = entry[0x1B98FDF8]
    ReBodyPattern0Color1 = entry[0xA3249A9D]
    ReBodyPattern1Color0 = entry[0xF45A96C6]
    ReBodyPattern1Color1 = entry[0x4CE6F1A3]
    ReBodyPattern2Color0 = entry[0x1F6D2DC5]
    ReBodyPattern2Color1 = entry[0xA7D14AA0]
    ReBodyPattern3Color0 = entry[0xF0AF46FB]
    ReBodyPattern3Color1 = entry[0x4813219E]
    ReBodyPattern4Color0 = entry[0x12735D82]
    ReBodyPattern4Color1 = entry[0xAACF3AE7]
    ReBodyPattern5Color0 = entry[0xFDB136BC]
    ReBodyPattern5Color1 = entry[0x450D51D9]
    ReBodyPattern6Color0 = entry[0x16868DBF]
    ReBodyPattern6Color1 = entry[0xAE3AEADA]
    ReBodyPattern7Color0 = entry[0xF944E681]
    ReBodyPattern7Color1 = entry[0x41F881E4]
    ReBodyPatternNum = entry[0xB0304B0D]
    
    ReFabricPattern0Color0 = entry[0x545F8769]
    ReFabricPattern0Color1 = entry[0xECE3E00C]
    ReFabricPattern1Color0 = entry[0xBB9DEC57]
    ReFabricPattern1Color1 = entry[0x03218B32]
    ReFabricPattern2Color0 = entry[0x50AA5754]
    ReFabricPattern2Color1 = entry[0xE8163031]
    ReFabricPattern3Color0 = entry[0xBF683C6A]
    ReFabricPattern3Color1 = entry[0x07D45B0F]
    ReFabricPattern4Color0 = entry[0x5DB42713]
    ReFabricPattern4Color1 = entry[0xE5084076]
    ReFabricPattern5Color0 = entry[0xB2764C2D]
    ReFabricPattern5Color1 = entry[0x0ACA2B48]
    ReFabricPattern6Color0 = entry[0x5941F72E]
    ReFabricPattern6Color1 = entry[0xE1FD904B]
    ReFabricPattern7Color0 = entry[0xB6839C10]
    ReFabricPattern7Color1 = entry[0x0E3FFB75]
    ReFabricPatternNum = entry[0x0CB402A3]

    #process data, only include what's needed
    BodyData = []
    if ReBodyPatternNum == 1:
        BodyData = [[ReBodyPattern0Color0, ReBodyPattern0Color1],
                    [ReBodyPattern1Color0, ReBodyPattern1Color1]]
    elif ReBodyPatternNum == 2:
        BodyData = [[ReBodyPattern0Color0, ReBodyPattern0Color1],
                    [ReBodyPattern1Color0, ReBodyPattern1Color1],
                    [ReBodyPattern2Color0, ReBodyPattern2Color1]]
    elif ReBodyPatternNum == 3:
        BodyData = [[ReBodyPattern0Color0, ReBodyPattern0Color1],
                    [ReBodyPattern1Color0, ReBodyPattern1Color1],
                    [ReBodyPattern2Color0, ReBodyPattern2Color1],
                    [ReBodyPattern3Color0, ReBodyPattern3Color1]]
    elif ReBodyPatternNum == 4:
        BodyData = [[ReBodyPattern0Color0, ReBodyPattern0Color1],
                    [ReBodyPattern1Color0, ReBodyPattern1Color1],
                    [ReBodyPattern2Color0, ReBodyPattern2Color1],
                    [ReBodyPattern3Color0, ReBodyPattern3Color1],
                    [ReBodyPattern4Color0, ReBodyPattern4Color1]]
    elif ReBodyPatternNum == 5:
        BodyData = [[ReBodyPattern0Color0, ReBodyPattern0Color1],
                    [ReBodyPattern1Color0, ReBodyPattern1Color1],
                    [ReBodyPattern2Color0, ReBodyPattern2Color1],
                    [ReBodyPattern3Color0, ReBodyPattern3Color1],
                    [ReBodyPattern4Color0, ReBodyPattern4Color1],
                    [ReBodyPattern5Color0, ReBodyPattern5Color1]]
    elif ReBodyPatternNum == 6:
        BodyData = [[ReBodyPattern0Color0, ReBodyPattern0Color1],
                    [ReBodyPattern1Color0, ReBodyPattern1Color1],
                    [ReBodyPattern2Color0, ReBodyPattern2Color1],
                    [ReBodyPattern3Color0, ReBodyPattern3Color1],
                    [ReBodyPattern4Color0, ReBodyPattern4Color1],
                    [ReBodyPattern5Color0, ReBodyPattern5Color1],
                    [ReBodyPattern6Color0, ReBodyPattern6Color1]]
    elif ReBodyPatternNum == 7:
        BodyData = [[ReBodyPattern0Color0, ReBodyPattern0Color1],
                    [ReBodyPattern1Color0, ReBodyPattern1Color1],
                    [ReBodyPattern2Color0, ReBodyPattern2Color1],
                    [ReBodyPattern3Color0, ReBodyPattern3Color1],
                    [ReBodyPattern4Color0, ReBodyPattern4Color1],
                    [ReBodyPattern5Color0, ReBodyPattern5Color1],
                    [ReBodyPattern6Color0, ReBodyPattern6Color1],
                    [ReBodyPattern7Color0, ReBodyPattern7Color1]]

    FabricData = []
    if ReFabricPatternNum == 1:
        FabricData = [[ReFabricPattern0Color0, ReFabricPattern0Color1],
                      [ReFabricPattern1Color0, ReFabricPattern1Color1]]
    elif ReFabricPatternNum == 2:
        FabricData = [[ReFabricPattern0Color0, ReFabricPattern0Color1],
                      [ReFabricPattern1Color0, ReFabricPattern1Color1],
                      [ReFabricPattern2Color0, ReFabricPattern2Color1]]
    elif ReFabricPatternNum == 3:
        FabricData = [[ReFabricPattern0Color0, ReFabricPattern0Color1],
                      [ReFabricPattern1Color0, ReFabricPattern1Color1],
                      [ReFabricPattern2Color0, ReFabricPattern2Color1],
                      [ReFabricPattern3Color0, ReFabricPattern3Color1]]
    elif ReFabricPatternNum == 4:
        FabricData = [[ReFabricPattern0Color0, ReFabricPattern0Color1],
                      [ReFabricPattern1Color0, ReFabricPattern1Color1],
                      [ReFabricPattern2Color0, ReFabricPattern2Color1],
                      [ReFabricPattern3Color0, ReFabricPattern3Color1],
                      [ReFabricPattern4Color0, ReFabricPattern4Color1]]
    elif ReFabricPatternNum == 5:
        FabricData = [[ReFabricPattern0Color0, ReFabricPattern0Color1],
                      [ReFabricPattern1Color0, ReFabricPattern1Color1],
                      [ReFabricPattern2Color0, ReFabricPattern2Color1],
                      [ReFabricPattern3Color0, ReFabricPattern3Color1],
                      [ReFabricPattern4Color0, ReFabricPattern4Color1],
                      [ReFabricPattern5Color0, ReFabricPattern5Color1]]
    elif ReFabricPatternNum == 6:
        FabricData = [[ReFabricPattern0Color0, ReFabricPattern0Color1],
                      [ReFabricPattern1Color0, ReFabricPattern1Color1],
                      [ReFabricPattern2Color0, ReFabricPattern2Color1],
                      [ReFabricPattern3Color0, ReFabricPattern3Color1],
                      [ReFabricPattern4Color0, ReFabricPattern4Color1],
                      [ReFabricPattern5Color0, ReFabricPattern5Color1],
                      [ReFabricPattern6Color0, ReFabricPattern6Color1]]
    elif ReFabricPatternNum == 7:
        FabricData = [[ReFabricPattern0Color0, ReFabricPattern0Color1],
                      [ReFabricPattern1Color0, ReFabricPattern1Color1],
                      [ReFabricPattern2Color0, ReFabricPattern2Color1],
                      [ReFabricPattern3Color0, ReFabricPattern3Color1],
                      [ReFabricPattern4Color0, ReFabricPattern4Color1],
                      [ReFabricPattern5Color0, ReFabricPattern5Color1],
                      [ReFabricPattern6Color0, ReFabricPattern6Color1],
                      [ReFabricPattern7Color0, ReFabricPattern7Color1]]

    remake_lookup[ItemUniqueID] = [UniqueID, RemakeKitNum, BodyData, FabricData]

item_data = BCSV().read_bcsv(bcsv_path + "/ItemParam.bcsv")
sortme = []
release_lookup = {}
with open(output_name, "wb") as o:
    o.write("ItemID (hex) | Release Version | Buy Price (Sell Price*4) | (Variation /) Item Name | Resource Name | Item Type | File Description\r\n")
    for entry in item_data:
        UniqueID = entry[0x54706054] #Internal ItemID
        Price = entry[0x718B024D] #buy price, sell price is / 4
        RemakeID = entry[0xCB5EB33F] #lookup using ItemRemake
        ItemReleaseVersion = entry[0x805CDABB]
        ResName = entry[0x48EF0398].decode("UTF-8").rstrip(u"\0").encode("UTF-8") #Item Name
        CapturePreset = entry[0xFC275E86].decode("UTF-8").rstrip(u"\0").encode("UTF-8") #Item Type
        try: #File Description
            ItemName = entry[0xB8CC232C].decode("UTF-8").rstrip(u"\0").encode("UTF-8")
        except: #bcsv stupid limit, 0x40 truncated string
            ItemName = "FILE_DESC_TRUNCATED " + entry[0xB8CC232C].decode("UTF-8", "ignore").encode("UTF-8")
        try: ItemString = itemname_lookup[UniqueID].encode("UTF-8")
        except:
            try: ItemString = clothname_lookup[UniqueID].encode("UTF-8")
            except: ItemString = "UNUSED" #Default furniture, NPC items, etc
        sortme.append([UniqueID, Price, RemakeID, ItemReleaseVersion, ResName, CapturePreset, ItemName, ItemString])
        release_lookup[UniqueID] = ItemReleaseVersion

    sortme.sort(key=lambda x: x[0])
    sortme.sort(key=lambda x: x[3])
    for entry in sortme:
        o.write("%04X | %d | %d | %s | %s | %s | %s\r\n" % (entry[0], entry[3], entry[1], entry[7], entry[4], entry[5], entry[6]))
    
with open(output_name2, "wb") as o:
    o.write("Base ItemID | Kits Required | Release Version | Item Name | Variations | Patterns\r\n")
    color_lookup = ["Orange", "Red", "Pink", "Purple", "Blue", "Aqua", "Green", "Yellow", "Beige", "Brown", "Black", "Gray", "White", "Colorful"]

    sortme = []
    for key in remake_lookup.keys():
        entry = remake_lookup[key]
        try: itemname = itemname_lookup[key]
        except:
            try: itemname = clothname_lookup[key]
            except: itemname = "UNUSED" #SmartPhone, EventObjFtr
        
        BodyColor = []
        for i in range(len(entry[2])):
            Color1, Color2 = entry[2][i]
            BodyName = bodycolor_lookup[key][1][i][1].encode("UTF-8")
            if Color1 == 14 and Color2 == 14:
                BodyColor.append("%s ()" % BodyName)
            elif Color1 == 14: #null
                BodyColor.append("%s (%s)" % (BodyName, color_lookup[Color2]))
            elif Color2 == 14: #null
                BodyColor.append("%s (%s)" % (BodyName, color_lookup[Color1]))
            elif Color1 == Color2: #just emit one
                BodyColor.append("%s (%s)" % (BodyName, color_lookup[Color1]))
            else:
                BodyColor.append("%s (%s, %s)" % (BodyName, color_lookup[Color1], color_lookup[Color2]))
        if BodyColor == []:
            BodyColor = ["N/A"]

        FabricColor = []
        for i in range(len(entry[3])):
            Color1, Color2 = entry[3][i]
            FabricName = fabriccolor_lookup[key][1][i][1].encode("UTF-8")
            print(FabricName)
            if Color1 == 14 and Color2 == 14:
                FabricColor.append("%s ()" % FabricName)
            elif Color1 == 14: #null
                FabricColor.append("%s (%s)" % (FabricName, color_lookup[Color2]))
            elif Color2 == 14: #null
                FabricColor.append("%s (%s)" % (FabricName, color_lookup[Color1]))
            elif Color1 == Color2: #just emit one
                FabricColor.append("%s (%s)" % (FabricName, color_lookup[Color1]))
            else:
                FabricColor.append("%s (%s, %s)" % (FabricName, color_lookup[Color1], color_lookup[Color2]))
        if FabricColor == []:
            FabricColor = ["N/A"]

        sortme.append([key, entry[1], release_lookup[key], itemname.encode("UTF-8"), BodyColor, FabricColor])

    sortme.sort(key=lambda x: x[0])
    sortme.sort(key=lambda x: x[2])
    for entry in sortme:
        o.write("%04X | %d | %d | %s | %s | %s\r\n" % (entry[0], entry[1], entry[2], entry[3], ", ".join(entry[4]), ", ".join(entry[5])))
