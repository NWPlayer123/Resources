void mString_aram_init(void) { //finished, pretty simple
	String_table_rom_start = JW_GetAramAddress(17); //string_data_table.bin
	String_rom_start = JW_GetAramAddress(16); //string_data.bin
}

mString_Get_StringDataAddressAndSize(index, address, size) {
	return mMsg_Get_BodyParam(&String_table_rom_start, &String_rom_start, index, address, size);
}
void mString_Load_StringFromRom(const char* alloc, uint32_t alloc_size, int index) { //finished
	if (0x7FF >= index >= 0) {
		uint32_t address = 0, size = 0; //prob invalid but w/e not compiling rn
		mString_Get_StringDataAddressAndSize(index, &address, &size);
		if (size != 0) {
			if (address != 0) { //does translation, aram to main ram (offset in mem)
				var = ((size + 0x1F) + (address - (address & 0xFFFFFFE0))) & 0xFFFFFFE0; //not actually here
				_JW_GetResourceAram(address, buff$408, var); //address = aram_addr, size = ???
				if (addr_size < size) {
					size = addr_size;
				}
				//time to copy string
				if (size > 0) { //copy it to output
					for (int i = 0;i < size;i++) {
						alloc[i] = buff$408[i]
					}
				}
				for (int j = size; j < i;j++) {
					alloc[i] = 0x20; // " ", space it out to full
				}
			}
		} else {
			mem_clear(alloc, alloc_size, 0x20); //no string, " "
		}
	}
	//doesn't return a value
}

void mString_Load_YearStringFromRom(const char *alloc, uint32_t year) {
	if (year > 2099 || 1901 > year)
		year = 2000;
	mFont_UnintToString(alloc, 6, year & 0xFFFF, 6, 1, 0, 0);
	//alloc is assumed to have string, no return
}

uint32_t mString_Load_MonthStringFromRom(const char *alloc, int month) {
	if (month > 12 || month < 1)
		month = 1;
	mString_Load_StringFromRom(alloc, 9, (month & 0xFF) + 0x66C); //September = 9 chars
	return mMsg_Get_Length_String(alloc, 9);
}
mString_Load_WeekStringFromRom
mString_Load_DayStringFromRom
mString_Load_HourStringFromRom
mString_Load_HourStringFromRom2
mString_Load_MinStringFromRom
mString_Load_SecStringFromRom
mString_Load_NumberStringAddUnitFromRom