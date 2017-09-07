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
OSLink
Undo
OSUnlink
__OSModuleInit