void OSSetStringTable (uint32_t* table) {
	//set in global data before .init
	asm("
		lis       r4, -0x8000 # 0x800030D0
		stw       r3, 0x30D0(r4) # 0x800030D0
		blr
	");
}