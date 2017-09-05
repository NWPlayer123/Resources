void Config24MB(void) {
	asm("
		mfmsr     r3
		rlwinm    r3, r3, 0,28,26
		mtmsr     r3
		isync
		li        r7, 0
		lis       r4, 0
		addi      r4, r4, 2
		lis       r3, -0x8000 # 0x800001FF
		addi      r3, r3, 0x1FF # 0x800001FF
		lis       r6, 0x100 # 0x1000002
		addi      r6, r6, 2 # 0x1000002
		lis       r5, -0x7F00 # 0x810000FF
		addi      r5, r5, 0xFF # 0x810000FF
		isync
		mtspr     dbat0u, r7
		mtspr     dbat0l, r4
		mtspr     dbat0u, r3
		isync
		mtspr     dbat2u, r7
		mtspr     dbat2l, r6
		mtspr     dbat2u, r5
		isync
		mfmsr     r3
		ori       r3, r3, 0x10
		mtmsr     r3
		isync
		blr
	");
}

void Config48MB(void) {
	asm("
		mfmsr     r3
		rlwinm    r3, r3, 0,28,26
		mtmsr     r3
		isync
		li        r7, 0
		lis       r4, 0
		addi      r4, r4, 2
		lis       r3, -0x8000 # 0x800003FF
		addi      r3, r3, 0x3FF # 0x800003FF
		lis       r6, 0x200 # 0x2000002
		addi      r6, r6, 2 # 0x2000002
		lis       r5, -0x7E00 # 0x820001FF
		addi      r5, r5, 0x1FF # 0x820001FF
		isync
		mtspr     dbat0u, r7
		mtspr     dbat0l, r4
		mtspr     dbat0u, r3
		isync
		mtspr     dbat2u, r7
		mtspr     dbat2l, r6
		mtspr     dbat2u, r5
		isync
		mfmsr     r3
		ori       r3, r3, 0x10
		mtmsr     r3
		isync
		blr
	");
}

void ReconfigBATs(void) {
	handle = OSDisableInterrupts();
	size = OSGetConsoleSimulatedMemSize();
	if (size > 0x180) {
		Config48MB();
	} else {
		Config24MB();
	}
	OSEnableInterrupts(handle);
}