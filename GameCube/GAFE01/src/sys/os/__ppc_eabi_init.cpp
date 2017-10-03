__init_hardware(void) {
	asm("
		mfmsr     r0
		ori       r0, r0, 0x2000 //turn on FP
		mtmsr     r0
		mflr      r31            //need to restore LR later
		bl        __OSPSInit
		bl        __OSCacheInit
		mtlr      r31
		blr
	");
}
__flush_cache
__init_user
__init_cpp
_ExitProcess