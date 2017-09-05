void ICFlashInvalidate(void) {
	asm("
		mfspr     r3, hid0
		ori       r3, r3, 0x800
		mtspr     hid0, r3
		blr
	");
}

__OSCacheInit(void) {
	
}