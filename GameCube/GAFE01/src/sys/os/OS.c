uint32_t OSGetConsoleType(void) {
	type = &0x802188B0; //uses r13
	if (type != 0) {
		type = &type[0x2C];
		if (type != 0) {
			return type;
		}
	} //fallthru, default
	return 0x10000002;
}

ClearArena(void) { //unfinished
	reset = OSGetResetCode();
	reset += 0x8000;
	#if (reset
}

InquiryCallback
OSInit(void) {
	handle = &0x802188B0; //???, uses r13
	
	
	OSReport("\nDolphin OS $Revision: 54 $.\n");
	OSReport("Kernel built : %s %s\n", "Jun  5 2002", "02:09:12");
	OSReport("Console Type : ");
	type = OSGetConsoleType();
	type &= 0x10000000;
	if (type != 0) { //get console type
		if (type == 0x10000000) {
			OSReport("Mac Emulator\n");
		}
		else if (type == 0x10000001) {
			OSReport("PC Emulator\n");
		}
		else if (type == 0x10000002) {
			OSReport("EPPC Arthur\n");
		}
		else if (type == 0x10000004) {
			OSReport("EPPC Minnow\n");
		} else {
			OSReport("Development HW%d\n", type);
		}
	} else {
		OSReport("Retail %d\n", type);
	}
}
OSExceptionInit
__OSDBIntegrator
SDBINTSTART
__OSDBJump
SDBINTEND
SDBJUMPSTART
SDBJUMPEND
__OSSetExceptionHandler
__OSGetExceptionHandler
OSExceptionVector
SEVStart
BVECTOR
SEVSetNumber
SEVEnd
OSDefaultExceptionHandler
__OSPSInit
__OSGetDIConfig