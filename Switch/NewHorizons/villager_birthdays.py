from bcsv_reader import BCSV
from msbt_reader import MSBT

bcsv_path = "./Bcsv"
msbt_path = "../message1.1"

months = ["", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]

labels, text = MSBT().read_msbt(msbt_path + "/String_USen/Npc/STR_NNpcName.msbt")

#create lookup, npcid (dog03) -> string name
lookup = {}
for entry in labels:
    lookup[entry[0]] = text[entry[1]][0]

#parse NmlNpcParam
data = BCSV().read_bcsv(bcsv_path + "/NmlNpcParam.bcsv")
sortme = []
for entry in data:
    internal_name = entry[0x2F1B930D].rstrip("\0")
    birthmonth = entry[0x9456B6A3]
    birthday = entry[0x919EA52A]
    sortme.append([lookup[internal_name], internal_name, birthmonth, birthday])

sortme.sort(key=lambda x: x[3]) #sort by day
sortme.sort(key=lambda x: x[2]) #sort by month
for entry in sortme:
    print("%s (%s) = %s %d" % (entry[0].encode("UTF-8"), entry[1], months[entry[2]], entry[3]))
