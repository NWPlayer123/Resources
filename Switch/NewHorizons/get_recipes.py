from bcsv_reader import BCSV
from msbt_reader import MSBT
from os import listdir
from binascii import hexlify
import sys

ver = 200
bcsv_path = "../data%s/Bcsv" % ver
msg_path = "../data%s/Message/USen/" % ver
output_name = "get_recipes%s.txt" % ver

'''Stolen from scrape_data cuz I need all the IDs'''
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

#grab cloth group ids and names
cloth_strings = []
cloth_id2str = {}
cloth_str2id = {}
for filename in listdir(msg_path + "/String_USen/Outfit/GroupName/"):
    if filename.endswith(".msbt"):
        labels, text = MSBT().read_msbt("%s/String_USen/Outfit/GroupName/%s" % (msg_path, filename))
        for entry in labels:
            itemid = int(entry[0])
            itemname = text[entry[1]][0]
            cloth_strings.append([itemid, itemname])
            cloth_id2str[itemid] = itemname
            cloth_str2id[itemname] = itemid

#grab cloth color ids and names
cloth_color_data = []
for filename in listdir(msg_path + "/String_USen/Outfit/GroupColor/"):
    if filename.endswith(".msbt"):
        labels, text = MSBT().read_msbt("%s/String_USen/Outfit/GroupColor/%s" % (msg_path, filename))
        for entry in labels:
            label = entry[0].split("_")
            baseid = int(label[0])
            itemid = int(label[2])
            itemname = text[entry[1]][0]
            cloth_color_data.append([baseid, itemid, itemname])

#convert cloth_baseid -> item_id
cloth_data = BCSV().read_bcsv(bcsv_path + "/ItemClothGroup.bcsv")
cloth_lookup = {}
cloth_lookup2 = {}
cloth_data2 = []
for entry in cloth_data:
    clothid  = entry[0x54706054] #string id
    itemid   = entry[0x65503F9F] #item id
    itemname = entry[0x13AB5198].decode("UTF-8").rstrip(u"\0").encode("UTF-8") #TODO: assert at end?
    itemdesc = entry[0x036E8EBE].decode("UTF-8").rstrip(u"\0").encode("UTF-8")
    cloth_lookup[clothid] = itemid
    cloth_lookup2[itemname] = itemid
    cloth_data2.append([clothid, itemid, itemname, itemdesc])

#store base IDs, will store color IDs in a bit
for entry in cloth_data2:
    try: item_strings.append([entry[1], cloth_id2str[entry[0]]])
    except: pass #skip the "None" entry

#base clothID -> item name
for entry in cloth_color_data:
    #if entry[0] != 1232: #TODO: swap for 1.4/1.5
    if ver < 200:
        full_itemname = "%s %s" % (entry[2], cloth_id2str[entry[0]])
        item_strings.append([entry[1], full_itemname])
    else:
        if entry[2] == "No Variations":
            full_itemname = "%s" % (cloth_id2str[entry[0]])
            item_strings.append([entry[1], full_itemname])
        else:
            full_itemname = "%s %s" % (entry[2], cloth_id2str[entry[0]])
            item_strings.append([entry[1], full_itemname])

#create lookup table for everything
item_lookup = {}
for entry in item_strings:
    item_lookup[entry[0]] = entry[1]

'''all data'''

recipe_data = BCSV().read_bcsv(bcsv_path + "/RecipeCraftParam.bcsv")
sort_data = []
for entry in recipe_data:
    Item = entry[0x89a3482c]
    SerialID = entry[0x39dede36]
    UniqueID = entry[0x54706054]

    event_type = entry[0x33DDEFC8].rstrip('\0')
    items_req = [entry[0x1bbfa75e], entry[0x5c1fdd8e], entry[0x617ff43e],
        entry[0xd35f282e], entry[0xee3f019e], entry[0xa99f7b4e]]
    number_req = [entry[0x13a65775], entry[0x54062da5], entry[0x69660415],
        entry[0xdb46d805], entry[0xe626f1b5], entry[0xa1868b65]]
    sort_data.append([Item, event_type, SerialID, UniqueID, items_req, number_req, item_lookup[Item]])
    '''print("%s (%s, %s, %s)" % (item_lookup[Item], event_type, SerialID, UniqueID))
    i = 0
    while items_req[i] != 65534 and i < 5:
        print("%d %s" % (number_req[i], item_lookup[items_req[i]]))
        i += 1
    print'''

errors = 1

sort_data.sort(key=lambda x: x[3])
with open(output_name, "wb") as o:
    for entry in sort_data:
        try: o.write("%s (%04X, EventType %s, SerialID %s, UniqueID %s)\r\n" % (item_lookup[entry[0]], entry[0], entry[1], entry[2], entry[3]))
        except:
            o.write("%s (%04X, EventType %s, SerialID %s, UniqueID %s)\r\n" % (item_lookup[entry[0]].encode("UTF-8"), entry[0], entry[1], entry[2], entry[3]))
            '''o.write("insertme %d\r\n" % errors)
            errors += 1'''
        i = 0
        while entry[4][i] != 65534 and i < 5:
            o.write("%d %s (%04X)\r\n" % (entry[5][i], item_lookup[entry[4][i]], entry[4][i]))
            i += 1
        o.write("\r\n")
        
    
