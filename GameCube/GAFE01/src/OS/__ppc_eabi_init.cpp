__init_hardware(void) {
	asm("
		mfmsr     r0
		ori       r0, r0, 0x2000
		mtmsr     r0
		mflr      r31
		bl        __OSPSInit
		bl        __OSCacheInit
		mtlr      r31
		blr
	");
}