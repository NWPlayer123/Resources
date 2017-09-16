void mString_aram_init(void) { //finished, pretty simple
	String_table_rom_start = JW_GetAramAddress(17); //string_data_table.bin
	String_rom_start = JW_GetAramAddress(16); //string_data.bin
}

mString_Get_StringDataAddressAndSize(index, address, size) {
	return mMsg_Get_BodyParam(&String_table_rom_start, &String_rom_start, index, address, size);
}
void mString_Load_StringFromRom(r3, r4, r5 index) { //finished, kinda sorta
	mString_Get_StringDataAddressAndSize(index, &address, &size); //needs to be allocated, uses stack
	if (size == 0) {
		return mem_clear(r3, r4, 0x20); //no string
	}
	if (address != 0) { //does translation, aram to main ram (offset in mem)
		_JW_GetResourceAram(aram_addr, buff$408, (size + 0x1F) & 0xFFFFFFE0); //size=r5
		if (size != 0) {
			for (int i = 0;i < size;i++) {
				r3[i] = buff$408[i]
			}
			for (int j = size; j < i;j++) {
				r3[i] = 0x20; // " ", space it out to full
			}
		}
	}
}
mString_Load_YearStringFromRom
mString_Load_MonthStringFromRom
mString_Load_WeekStringFromRom
mString_Load_DayStringFromRom
mString_Load_HourStringFromRom
mString_Load_HourStringFromRom2
mString_Load_MinStringFromRom
mString_Load_SecStringFromRom
mString_Load_NumberStringAddUnitFromRom