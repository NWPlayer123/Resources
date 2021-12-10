def make_function(addr, name, size, comm):
    print('set_name(0x%08X, "%s")' % (addr, name))
    print('create_insn(0x%08X)' % (addr))
    print('add_func(0x%08X, 0x%08X)' % (addr, addr+size))
    print('set_func_cmt(0x%08X, "%s", 0)' % (addr, comm))

def make_data(addr, name, comm):
    print('set_cmt(0x%08X, "%s", 0)' % (addr, comm))
    print('set_name(0x%08X, "%s")' % (addr, name))

def sanitize(line):
    line = line.strip()
    line = line.replace("\t", " ")
    for i in range(5):
        line = line.replace("  ", " ")
    return line.split(" ")

def get_name(func, addr):
    func = func.split("$")[0]
    if func.startswith("@"):
        func = "str_%08X" % addr
    if func not in funcs:
        funcs.append(func)
        return func
    else: #duplicate symbol
        incr = 1; name = "%s_%d" % (func, incr)
        while name in funcs:
            incr += 1
            name = "%s_%d" % (func, incr)
        funcs.append(name)
        return name

funcs = []
rel_addr = 0 #set to 0 for dol, base addr for rel

symbol_map = open("static.map", "rb").read()
symbol_map = symbol_map.replace('\r\n', '\n') #easier to work with
segments = symbol_map.split("\n\n\n")
'''for i in range(len(segments)):
    with open("segment%d.txt" % i, "wb") as o:
        o.write(segments[i])'''
for segment in segments:
    lines = segment.strip().split("\n") #first section has newline, strip()
    if "section layout" in lines[0]: #section I can parse
        segname = lines[0].split(" ")[0]
        if len(lines) > 4: #has entries
            for line in lines[4:]:
                if line.strip().startswith("00") and "(entry" not in line \
                 and segname not in line:
                    line = sanitize(line)
                    size = int(line[1], 16)
                    addr = rel_addr + int(line[2], 16)
                    name = get_name(line[4], addr)
                    comm = " ".join(line[5:])
                    if segname in [".init", ".text"]:
                        make_function(addr, name, size, comm)
                    else:
                        make_data(addr, name, comm)
                elif line.strip().startswith("00") and "(entry" in line \
                 and segname not in line:
                    line = sanitize(line)
                    size = int(line[1], 16)
                    addr = rel_addr + int(line[2], 16)
                    name = get_name(line[3], addr)
                    comm = " ".join(line[7:])
                    if segname in [".init", ".text"]:
                        make_function(addr, name, size, comm)
                    else:
                        make_data(addr, name, comm)
