void mainproc(int something) {
	ScreenWidth = 320;
	ScreenHeight = 240;
	JW_BeginFrame();
	JW_EndFrame();
	mCD_init_card();
	osCreateMesgQueue(prbuf[0xC1028 / 4], prbuf[0xC1048 / 4], 1); //812F4CC0 812F4CE0
	uint32_t somearray[0x10]; //r1+0x14, r1+0x34
	osCreateMesgQueue(somearray[0], somearray[8], 10);
	CreateIRQManager(prbuf[0xC29D8 / 4], 0x1000, 18, 1);
	uint32_t somearray2[2]; //r1+0xC
	irqmgr_AddClient(somearray2[0], somearray[0]);
	memset(prbuf[0xC29D8 / 4], 0xEB, 0x1000);
	padmgr_Create(prbuf[0xC1028 / 4], 7, 15, prbuf[0xC39D8 / 4], 0x1000);
	osCreateThread2(prbuf[0xC1050 / 4], 4, graph_proc, something, prbuf[0xC59D8 / 4], 0x2000, 8);
	JW_BeginFrame();
	JW_EndFrame();
	osStartThread(prbuf[0xC1050 / 4]);
	osSetThreadPri(0, 5); //ority
	JW_Init3();
	mMsg_aram_init2();
	mLd_StartFlagOn();
	famicom_mount_archive();
	JC_JKRAramHeap_dump(JC_JKRAram_getAramHeap());
	osSetThreadPri(0, 13);
	uint32_t somevar; //r1+8
	while (somevar != 0) {
		somevar = 0; //re-set at end of loop
		while (somearray[7] != 0) {
			osRecvMesg(somearray[0], 0, 0);
		}
		osRecvMesg(somearray[0], somevar, 1);
	}
}

uint32_t entry(void) {
	padmgr_Init(0);
	new_Debug_mode();
	prbuf[0x6043C / 4] = 0; //??????? 812940D4
	mainproc(0);
	return 0;
}

void main(int argc, const char **argv) {
	OSReport("Animal Crossing main2 start\n");
	HotStartEntry = entry; //it will be called later
}