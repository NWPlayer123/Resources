#for use with scrape_data, ", " separator was having issues, switched it
sorttype = 0
textpath = "scrape_data.txt"

def do_sort(sortme, sorttype):
    if sorttype == 0: #sort by item id
        sortme.sort(key=lambda x: x[0])
    elif sorttype == 1: #sort by buy price
        sortme.sort(key=lambda x: x[1])
    elif sorttype == 2: #sort by sell price
        sortme.sort(key=lambda x: x[2])
    elif sorttype == 3: #sort by item name
        sortme.sort(key=lambda x: x[3].lower())
    elif sorttype == 4: #sort by item_type
        sortme.sort(key=lambda x: x[4].lower())
    elif sorttype == 5: #sort by file_name
        sortme.sort(key=lambda x: x[5].lower())
    elif sorttype == 6: #sort by file_desc
        sortme.sort(key=lambda x: x[6].lower())
    return sortme

separator = " | "

sortme = []
#sortme2 = []
with open(textpath, "rb") as f:
    print(f.readline().strip()) #csv header
    for line in f.readlines():
        line = line.rstrip("\r\n").rstrip("\n").split(" | ")
        '''if line[4] not in sortme2:
            sortme2.append(line[4])'''
        sortme.append([int(line[0], 16), int(line[1]), int(line[2]), line[3], line[4], line[5], line[6]])

'''sortme = do_sort(sortme, 3) #item name
sortme = do_sort(sortme, 4) #item_type'''
'''sortme2.sort(key=lambda x: x.lower())
for entry in sortme2:
    print(entry)'''
for entry in sortme:
    print("%04X%s%d%s%d%s%s%s%s%s%s%s%s" % (entry[0], separator, entry[1], separator, entry[2],
                separator, entry[3], separator, entry[4], separator, entry[5], separator, entry[6]))
