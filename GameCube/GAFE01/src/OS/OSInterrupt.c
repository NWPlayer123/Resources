uint32_t OSDisableInterrupts(void) {
	asm("
		mfmsr     r3
		rlwinm    r4, r3, 0,17,15
		mtmsr     r4
		extrwi    r3, r3, 1,16
		blr
	");
}

uint32_t OSRestoreInterrupts(uint32_t handle) { //TODO: figure out handle ??
	asm("
		cmpwi     r3, 0
		mfmsr     r4
		beq       tag1
		ori       r5, r4, 0x8000
		b         tag2
	tag1:
		rlwinm    r5, r4, 0,17,15
	tag2:
		mtmsr     r5
		extrwi    r3, r4, 1,16
		blr
	");
	
}