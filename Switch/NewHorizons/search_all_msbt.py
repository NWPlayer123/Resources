# -*- coding: utf-8 -*-
from os import listdir
from msbt_reader import MSBT

msbt_path = "../message1.1/String_JPja/Item/"
search_str = "プラチナコガネ"

did_print_filename = False
for name in listdir(msbt_path):
    if name.endswith(".msbt"):
        labels, text = MSBT().read_msbt("%s/%s" % (msbt_path, name))
        for i in range(len(labels)):
            if text[i][0].encode("UTF-8") == search_str:
                if not did_print_filename:
                    print(name)
                    did_print_filename = True
                print("%s: %s" % (labels[i][0], text[i][0]))
        did_print_filename = False
