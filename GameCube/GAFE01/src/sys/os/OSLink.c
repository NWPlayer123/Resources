void OSNotifyLink(void) {
	return; //stubbed
}

void OSNotifyUnlink(void) {
	return; //stubbed
}

void OSSetStringTable(void* table) {
	// 0x800030D0 = table
	asm("
		lis       r4, -0x8000
		stw       r3, 0x30D0(r4)
		blr
	");
}
Relocate

//http://www.metroid2002.com/retromodding/wiki/REL_(File_Format)
OSLink(uint32_t* data, uint32_t bss_alloc) {
	module_version = data[0x1C];
	if (module_version > 2) {
		return 0;
	}
	else if (module_version == 2) {
		module_alignment = data[0x40];
		if (module_alignment != 0) {
			if (data - ((data / module_alignment) * module_alignment) == 0) {
				return 0;
			}
		}
		bss_alignment = data[0x44];
		
		
		
		r4 = &0x800030CC;
		if (r4 == 0) {
			0x800030CC = *data;
		} else {
			r4[4] = *data;
		}
		data[8] == r4;
		
		
		
		memset(
	}
	else {
		
	}
}
Undo
OSUnlink
void __OSModuleInit(void) {
	*0x800030C8 = 0;
	*0x800030CC = 0;
	*0x800030D0 = 0;
}