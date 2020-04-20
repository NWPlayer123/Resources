from msbt_reader import MSBT
from binascii import hexlify

msbt_path = "../message1.1"
msbt_path2 = "System_USen/NookMilage/NookMilage_List.msbt"

labels, text = MSBT().read_msbt("%s/%s" % (msbt_path, msbt_path2))
for i in range(0, len(labels), 2):
    print(text[i][0].encode("UTF-8"))
    print(text[i + 1][0].encode("UTF-8"))
    #print(hexlify(text[i+1][0].encode("UTF-8")))
    print
