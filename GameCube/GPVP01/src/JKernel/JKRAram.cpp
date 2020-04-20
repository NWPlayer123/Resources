JKRAram::create(unsigned long r3, unsigned long r4, long r5, long r6, long r7) { //finished, besides varnames
	if (JKRAram::sAramObject == 0) { //initialize
		AramObject = new JKRHeap(0x88, JKRHeap::sSystemHeap, 0);
		if (AramObject == 0) {
			AramObject = JKRAram::JKRAram(r3, r4, r7);
		}
		JKRAram::sAramObject = AramObject;
	}
	JKRAramStream::create(r5);
	JKRDecomp::create(r6);
	OSResumeThread(&JKRAram::sAramObject[0x2C]);
	return JKRAram::sAramObject;
}

JKRAram::JKRAram(unsigned long r3, unsigned long r4, long r5) { //unfinished
	JKRThread::JKRThread(r3, 0x4000, 0x10);
	ARInit(*r3 + 0x7C, 3); //looks to be only r3 and r4
	ARQInit();
	ARGetSize();
}

__dt__7JKRAramFv


JKRAram::run(void) { //does some loop, incomplete
	OSInitMessageQueue(JKRAram::sMessageQueue, JKRAram::sMessageBuffer, 4);
	OSReceiveMessage(JKRAram::sMessageQueue, [stack+8], 1); //needs to pass array ?
	
	ret = delete //something;
	
	JKRAramPiece::startDMA((JKRAMCommand *))
}

int JKRAram::checkOkAddress(unsigned char *, unsigned long, JKRAramBlock *, unsigned long) {
	if ((r3 & 0x1F) or (r4 & 0x1F)) {
		OSPanic("JKRAram.cpp", 0xE1, ":::address not 32Byte aligned.");
		return 0;
	}
	if (r5 != 0) {
		if ((r5[0x14] + r6) & 0x1F) {
			OSPanic("JKRAram.cpp", 0xEA, ":::address not 32Byte aligned.");
			return 0;
		}
	}
	return 1;
}

JKRAram::changeGroupIdIfNeed(unsigned char *, int) { //a pain, unfinished
	
}

mainRamToAram__7JKRAramFPUcUlUl15JKRExpandSwitchUlP7JKRHeapi
mainRamToAram__7JKRAramFPUcP12JKRAramBlockUl15JKRExpandSwitchUlP7JKRHeapi
aramToMainRam__7JKRAramFUlPUcUl15JKRExpandSwitchUlP7JKRHeapiPUl
aramToMainRam__7JKRAramFP12JKRAramBlockPUcUlUl15JKRExpandSwitchUlP7JKRHeapiPUl
JKRDecompressFromAramToMainRam__FUlPvUlUlUl
decompSZS_subroutine__FPUcPUc
firstSrcData__Fv
nextSrcData__FPUc
__sinit_JKRAram_cpp
__dt__23JSUList_12JKRAMCommand_Fv