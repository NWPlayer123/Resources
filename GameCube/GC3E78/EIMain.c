int main(int argc, const char **argv) {
	OSInit();
	VIInit();
	DVDInit();
	PADInit();
	CARDInit();
	PADRead(gpadInfo);
	if ((uint16_t*)gpadInfo[0] &  0x400 != 0 &&
		(uint16_t*)gpadInfo[0] &  0x200 != 0 &&
		(uint16_t*)gpadInfo[0] & 0x1000 != 0) {
		gui32ControllerResetDown[0] = 1;
	}
	if ((uint16_t*)gpadInfo[6] &  0x400 != 0 &&
		(uint16_t*)gpadInfo[6] &  0x200 != 0 &&
		(uint16_t*)gpadInfo[6] & 0x1000 != 0) {
		gui32ControllerResetDown[1] = 1;
	}
	if ((uint16_t*)gpadInfo[12] &  0x400 != 0 &&
		(uint16_t*)gpadInfo[12] &  0x200 != 0 &&
		(uint16_t*)gpadInfo[12] & 0x1000 != 0) {
		gui32ControllerResetDown[2] = 1;
	}
	if ((uint16_t*)gpadInfo[18] &  0x400 != 0 &&
		(uint16_t*)gpadInfo[18] &  0x200 != 0 &&
		(uint16_t*)gpadInfo[18] & 0x1000 != 0) {
		gui32ControllerResetDown[3] = 1;
	}
	
	DVDSetAutoFatalMessaging(1);
	MMSwapToGlobalHeap();
	pFontData = MMMalloc(0x20140) & 0xFFFFFFE0; //align to 32-byte
	OSGetFontEncode();
	OSInitFont();
	MMReplaceHeap();
	//TODO: Check these ^^^
	InitGraphic();
	EFIniFile::Read(EFIniFile::GetInstance(), "ENGINE.INI"); //TODO: C++ this shit
	uint64_t time = OSGetTime();
	OSTicksToCalendarTime(time, (uint32_t*) calendarTime); //TODO: define this cuz stack
	
	//TODO: some math srand seed shit
}