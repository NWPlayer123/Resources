#very incomplete
from bcsv_reader import BCSV
from msbt_reader import MSBT

bcsv_path = "./Bcsv"
msbt_path = "../message1.1"

lookup = {}
labels, text = MSBT().read_msbt(msbt_path + "/String_USen/Npc/STR_NNpcName.msbt")
for i in range(len(text)):
    lookup[labels[i][0]] = text[i][0]

labels, text = MSBT().read_msbt(msbt_path + "/String_USen/Npc/STR_SNpcName.msbt")
for i in range(len(text)):
    lookup[labels[i][0]] = text[i][0]

data = BCSV().read_bcsv(bcsv_path + "/AmiiboData.bcsv")
sortme = []
for entry in data:
    try: sortme.append(lookup[entry[0x34C8EED5].rstrip(u'\0')])
    except: pass

sortme.sort(key=lambda x: x.lower())
for entry in sortme:
    print(entry)
