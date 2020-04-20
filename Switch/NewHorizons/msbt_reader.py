#Very terrible msbt reader, only has the Aminal sections, just for
#scraping data/string names
#comment out a line in TXT2 if you want the raw strings returned
#comment out a line in read_msbt if you want the raw label groups, not an array
from struct import pack, unpack
from io import BytesIO
from binascii import hexlify, unhexlify

def full(f, endian):
    return unpack("%sI" % endian, f.read(4))[0]

def half(f, endian):
    return unpack("%sH" % endian, f.read(2))[0]

class MSBT:
    def __init__(self):
        self.endian = b">"

    #pass in file handle or BytesIO, strips/handles the dumb control codes
    #doesn't use for i cuz reading multiple bytes for the control codes
    def clean_str(self, f):
        f.seek(0, 2)
        full_size = f.tell()
        f.seek(0, 0)
        ret = b""; char = half(f, self.endian)
        while f.tell() < full_size:
            if char == 0x000E: #control code magic
                command = half(f, self.endian)
                command2 = half(f, self.endian)
                size = half(f, self.endian)
                if command2 == 0x16: #??? for Russian strings
                    f.read(2) #skip whatever this is
                    declension = half(f, self.endian)
                    if declension != 2: #???
                        ret += pack("%sH" % self.endian, declension)
                    f.read(size - 4)
                else:
                    data = f.read(size)
            else:
                ret += pack("%sH" % self.endian, char)
            char = half(f, self.endian)
        return ret
    
    def LBL1(self, f, start):
        count = full(f, self.endian)
        table = [unpack("%s2I" % self.endian, f.read(8)) for i in range(count)]
        entries = []
        for entry in table:
            group = []
            f.seek(entry[1] + start) #num_labels, section_offset
            for i in range(entry[0]):
                size = ord(f.read(1))
                name = f.read(size)
                value = full(f, self.endian)
                group.append([name, value])
            entries.append(group)
        return entries

    def TXT2(self, f, start, end):
        count = full(f, self.endian)
        table = [unpack("%sI" % self.endian, f.read(4))[0] for i in range(count)]
        table.append(end) # plus one so we don't OOB
        strings = []
        for i in range(count):
            f.seek(start + table[i]) #relative->absolute
            string = f.read(table[i+1] - table[i])
            string = self.clean_str(BytesIO(string)) #comment out for no filter
            strings.append([string.decode("UTF-16-LE"), i])
        return strings
    
    def read_msbt(self, name):
        with open(name, "rb") as f:
            assert f.read(8) == b"MsgStdBn" #magic
            if unpack(">H", f.read(2))[0] == 0xFFFE: self.endian = "<"
            assert unpack(">I", f.read(4))[0] == 0x00000103
            num_sections = half(f, self.endian)
            assert half(f, self.endian) == 0
            full_size = full(f, self.endian)
            f.seek(0, 2)
            assert f.tell() == full_size #make sure file not truncated
            f.seek(0x16)
            assert f.read(10) == b"\x00" * 10
            for i in range(num_sections): #for each section, parse and then stitch after
                header = unpack("%s4sI8x" % self.endian, f.read(16))
                start = f.tell()
                if header[0] == b"LBL1": #labels
                    labels = self.LBL1(f, start)
                if header[0] == b"ATR1": #attributes
                    pass
                if header[0] == b"TXT2": #text data
                    text = self.TXT2(f, start, header[1])
                f.seek(start + header[1])
                if f.tell() % 16: #align to next section
                    f.seek(16 - (f.tell() % 16), 1)

        labels2 = [] #process raw labels, 3D groups -> 2D array
        for entry in labels:
            for entry2 in entry:
                labels2.append(entry2)
        labels2.sort(key=lambda x: x[1]) #sort by text index

        return labels2, text #returns raw unsorted data, have to parse
