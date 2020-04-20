# File notes:
# u32 numEntries, u32 entrySize (strings are fixed, can be truncated), (u16) numFields
# u8 flag1, u8 flag2, "BCSV", game version? 0x2710 = 10000/1.0.0, 0x2774 = 10100/1.1.0
# u64 align(?), doesn't line up with a "first entry",
# <field table>, <field data * numEntries>
# Field table: u32 hash(?), u32 offset (within an entry)
# Field data: indeterminate, use nextOffset-thisOffset to get size, guess u8/16/32/str
from struct import unpack

class BCSV: #for importing into other programs
    def read_bcsv(self, name): #BCSV().read_bcsv("<filename>")
        with open(name, "rb") as f:
            header = unpack("<2IH2B2I8x", f.read(0x1C))
            numEntries = header[0]
            entrySize = header[1]
            numFields = header[2]
            flag1 = header[3]
            flag2 = header[4]
            magic = header[5]
            version = header[6]
            fields = [unpack("<2I", f.read(8)) for i in range(numFields)]
            fields.append((0, entrySize)) #for nextOffset so not off-by-one
            entries = []
            for i in range(numEntries): #read each entry
                entry = {} #dictionary, X hash -> Y data
                offset_smth = unpack("<I", f.read(4))[0]
                for j in range(numFields): #read each field
                    size = fields[j+1][1] - fields[j][1]
                    if size == 1: #treat as u8
                        entry[fields[j][0]] = unpack("<B", f.read(1))[0]
                    elif size == 2: #treat as u16
                        entry[fields[j][0]] = unpack("<H", f.read(2))[0]
                    elif size == 4: #treat as u32
                        entry[fields[j][0]] = unpack("<I", f.read(4))[0]
                    else: #treat as string
                        entry[fields[j][0]] = f.read(size)
                entries.append(entry)
        return entries
    
