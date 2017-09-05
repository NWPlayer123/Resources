JC_JFWSystem_setMaxStdHeap(unsigned int max) {
	unsigned int MaxStdHeap = max;
}

JC_JFWSystem_setSysHeapSize(unsigned int size) {
	unsigned int SysHeapSize = size;
}

JW_Init() {
	arena  = OSGetArenaHi();
	arena -= OSGetArenaLo();
	SystemHeapSize = arena - 0xD0;
	JC_JFWSystem_setMaxStdHeap(1);
	JC_JFWSystem_setSysHeapSize(SystemHeapSize);
	JC_JFWSystem_setFifoBufSize(0x10001);
	# soundAramSize=00000081 graphAramSize=006A3780 totalAramSize=00EB3780
	OSReport("soundAramSize=%08x graphAramSize=%08x totalAramSize=%08x\n", 0x81, 0x6A3780, 0xEB3780);
	JC_JFWSystem_setAramAudioBufSize(0x81);
	JC_JFWSystem_setAramGraphBufSize(0x6A3780);
	JC_JFWSystem_init();
	heap = JC_JFWSystem_getSystemHeap();
	JC_JKRExpHeap_changeGroupID(heap, 1);
	JC_JFWSystem_getSystemConsole();
	# lots of SDA stuff here
}

void JW_Free(uint32_t handle) {
	sysheap = JC_JFWSystem_getSystemHeap();
	JC_JKRHeap_free(sysheap, handle);
}

JC_JFWSystem_getSystemHeap(void) {
	asm("
		lwz       r3, -0x74EC(r13)
		blr
	");
}

JC_JKRHeap_free(sysheap, handle) {
	JKRHeap::free(void *);
}

void JW_Init2(void) {
	heap = JC_JFWSystem_getSystemHeap();
	JC_JKRExpHeap_changeGroupID(heap, 3);
	ReportDiskID();
	if (forest_arc_aram_p == 0) {
		forest_arc_aram_p = JC_JKRAramArchive_new();
		if (forest_arc_aram_p == 0) {
			OSDVDFatalError();
		}
		handle = JC__JKRMountFixedAramArchive(forest_arc_aram_p, "forest_1st.arc");
		if (handle == 0) {
			OSDVDFatalError();
		}
	}
	heap = JC_JFWSystem_getSystemHeap();
	freesize = JC_JKRHeap_getFreeSize(heap);
	gameheap_len = freesize + 0xFFFF; // ??? addis     r0, r3, -1
	heap = JC_JFWSystem_getSystemHeap();
	JC_JKRHeap_alloc(heap, 0x20);
	MallocInit(r3, gameheap_len); //need to fix
	heap = JC_JFWSystem_getSystemHeap();
	JC_JKRExpHeap_changeGroupID(heap, 4);
}

JC_JKRHeap_getFreeSize(void *heap) {
	
}

JC_JKRHeap_alloc(void *heap) {
	
}

ReportDiskID(void) {
	
}

void JC__JKRDvdToMainRam_byName(const char *name, uchar *asdf, JKRExpandSwitch sw) {
	JKRDvdRipper::loadToMainRAM(name, asdf, sw, 0, 0, 1, 0, 0);
}