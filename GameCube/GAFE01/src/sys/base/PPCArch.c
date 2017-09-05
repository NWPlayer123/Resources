void PPCMfhid2(void) {
	asm("
		mfspr     r3, 0x398
		blr
	");
}

void PPCMthid2(void) {
	asm("
		mtspr     0x398, r3
		blr
	");
}