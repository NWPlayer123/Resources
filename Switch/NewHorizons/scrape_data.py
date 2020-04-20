#Aminal Crossing Item Data Scrape Script
# 1) Grab labels + strings from String_/Item/*.msbt, label has ItemID
# 2) Grab labels + strings from String_/Outfit/GroupName/*.msbt, need to translate ClothID
# 3) Grab labels + strings from String_/Outfit/GroupColor/*.msbt, has all the alt colors for ClothIDs
# 4) Read ItemClothGroup, has ClothID -> ItemID for the base item, need to add alt colors separate
# 5) add ClothID -> ItemIDs to the list
# 6) alt colors have the Item ID already in the label, add them to ItemIDs
# 7) create a lookup for ItemID -> string name
# 8) Read ItemParam, has prices and lots of other stuff (TODO?), check lookup and spit out csv table
from bcsv_reader import BCSV
from msbt_reader import MSBT
from os import listdir
import sys, string

#ease-of-use strings
msg_path = "../message1.1"
bcsv_path = "./Bcsv"
output_name = "scrape_data.txt"

def getindices(s): #grab index of all uppercase letters for lookup
    return [i for i, c in enumerate(s) if c.isupper()]

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
    full_itemname = "%s %s" % (entry[2], cloth_id2str[entry[0]])
    item_strings.append([entry[1], full_itemname])

#create lookup table for everything
item_lookup = {}
for entry in item_strings:
    item_lookup[entry[0]] = entry[1]

#parse table for IDs and filenames
item_data = BCSV().read_bcsv(bcsv_path + "/ItemParam.bcsv")
sortme = []
with open(output_name, "wb") as o:
    o.write("Item ID (hex), Buy Price, Sell Price, Item Name, item_type, file_name, file_desc\r\n") #pseudo-csv
    for entry in item_data:
        item_id = entry[0x54706054]
        buy_price = entry[0x718B024D]
        sell_price = int(buy_price / 4.0)
        file_name = entry[0x3FEBC642].decode("UTF-8").rstrip(u"\0").encode("UTF-8")
        item_type = entry[0xFC275E86].decode("UTF-8").rstrip(u"\0").encode("UTF-8")
        try:
            file_desc = entry[0xB8CC232C].decode("UTF-8").rstrip(u"\0").encode("UTF-8")
        except: #bcsv stupid limit, 0x40 truncated string
            file_desc = "FILE_DESC_TRUNCATED " + entry[0xB8CC232C].decode("UTF-8", "ignore").encode("UTF-8")
        try: item_name = item_lookup[item_id]
        except: item_name = "UNUSED" #Default furniture, NPC items, etc
        sortme.append([item_id, buy_price, sell_price, item_name, item_type, file_name, file_desc])

    sortme.sort(key=lambda x: x[0]) #sort by item ID by default
    for entry in sortme:
        separator = " | "
        o.write("%04X%s%d%s%d%s%s%s%s%s%s%s%s\r\n" % (entry[0], separator, entry[1], separator, entry[2], separator,
                            entry[3].encode("UTF-8"), separator, entry[4], separator, entry[5], separator, entry[6]))
