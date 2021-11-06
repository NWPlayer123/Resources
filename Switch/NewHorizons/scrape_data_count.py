infile = "scrape_data200.txt"

valid_itemids = []
with open(infile, "rb") as f:
    for line in f.readlines()[1:]:
        itemid = line.strip().split(" | ")[0]
        valid_itemids.append(itemid)

missing_itemids = []
for i in range(int(valid_itemids[-1], 16) + 1):
    if ("%04X" % i) not in valid_itemids:
        missing_itemids.append("%04X" % i)

print(len(missing_itemids))
