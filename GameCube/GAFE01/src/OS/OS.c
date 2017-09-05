__OSPSInit(void) {
	asm("
		mflr      r0
		stw       r0, 4(r1)
		stwu      r1, -8(r1)
		bl        PPCMfhid2
		oris      r3, r3, 0xA000
		bl        PPCMthid2
		bl        ICFlashInvalidate
		sync
		li        r3, 0
		mtspr     0x390, r3
		lwz       r0, 0xC(r1)
		addi      r1, r1, 8
		mtlr      r0
		blr
	");
}