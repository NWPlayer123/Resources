void LoadStringTable(const char name) {
	OSReport("ストリングテーブル読み込み開始\n"); //start reading string table
	uint64_t time = osGetTime();
	table = JC__JKRDvdToMainRam_byName(name, 0, 1);
	if (table == 0) {
		OSDVDFatalError();
	}
	*StringTable = table;
	OSSetStringTable(&StringTable);
	uint64_t time = osGetTime();
	OSReport("ストリングテーブル読み込み 完了\n"); //string table read done
}

void LoadLink(const char name) {
	r28 = 0;
	OSReport("モジュール(%s)の読み込み中\n", name); //Loading module (/foresta.rel.szs)
	handle = JC__JKRDvdToMainRam_byName(name, 0, 1);
	if (handle == 0) {
		OSReport("モジュール(%s)の読み込みに失敗しました\n", name); //Failed to load module (/foresta.rel.szs)
		OSDVDFatalError();
	}
	OSReport("モジュール(%s)の読み込み完了\n", name); //Loading module (/foresta.rel.szs) is completed
	OSReport("module=%08x\n", handle); //determined at runtime
	OSReport("result=%08x\n", handlemath);
	length = JW_GetMemBlockSize(handle);
	OSReport("length=%08x\n", length);
	ret = JC__JKRDetachResource(handle);
	if (ret == 0) {
		alloc = soundArenaAlloc();
		if (alloc = 0) { //which will always happen cause soundArenaAlloc is shit
			OSReport("サウンドアリーナ %08x 使用 bss=%08x\n", handle[0x20], alloc);
		}
	}
	JW_Free(r28);
	JW_Free(handle);
	return 0;
}

uint64_t osGetTime(void) {
	OSGetTime
}

uint32_t soundArenaAlloc(void) {
	return 0;
}

int __cdecl main(int argc, const char **argv, const char **envp) {
	ReconfigBATs();
	if (fakemain_check != 0) {
		return -1;
	}
	fakemain_check = 1;
	OSReport("NDEBUG defined.\x1B\x5B\x6D\n");
	OSReport("_DEBUG not defined.\x1B\x5B\x6D\n");
	OSReport("DEBUG=%d\x1B\x5B\x6D\n", 0);
	uint64_t *800E2288 = osGetTime();
	OSInit()
	OSInitAlarm();
	asdf = OSGetStackPointer() - 0x100;
	handle = OSGetCurrentThread()
	if (asdf <= handle[0x304]) {
		if (asdf > handle[0x308] + 4) {
			memset(handle[0x308] + 4, 0xFD, asdf - handle[0x308] + 4)
		}
	}
	
	
	OSReport("システムパワーオン\n"); // System Power On
	
	
	OSReport("リスタート\n"); // Restart
	OSGetSaveRegion(); //TODO
	OSReport("OSGetSaveRegion %08x %08x\n", , );
	
	
	OSReport("ホットリセット\n"); //Hot Reset
	code = OSGetResetCode();
	OSReport("OSGetResetCode=0x%08x\n", code);
	OSReport("リリース版ではリセットコードを無視します\n"); //Ignore Reset Code in Release Version
	
	
	OSReport("デベロップメントモードに戻します。そしてリセット\x1B\x5B\x6D\n"); //Return to development mode. And reset
	OSChangeBootMode(0);
	OSResetSystem(1, dword_80206F9C, 0);
	
	OSReport("どうぶつの森ブートローダ起動\n"); //Animal Crossing Bootloader Start
	
	
	JC_JUTException_setMapFile("/static.map");
	
	
	
	
	
	OSReport("InitialStartTime=%u us\n", dosomemath); //unfinished
	sound_initial();
	initial_menu_init();
	dvderr_init();
	sound_initial2();
	
	
	
	
	
	
	if (rlwinm.   r0, r3, 0,3,3 | OSGetConsoleType()) {
		OSReport("以降OSReportを無効\n"); //calling OSReportDisable
		OSReportDisable();
	}
	OSReport("Loging COPYDATE\n");
	handle = JC__JKRDvdToMainRam_byName("/COPYDATE", 0, 1);
	if (handle == 0) {
		OSDVDFatalError();
	}
	LoadStringTable("/static.str");
	link = LoadLink("/foresta.rel.szs");
	JW_Init2();
	initial_menu_cleanup();
	if (link == 0) { //try again ???
		link = LoadLink("/foresta.rel.szs");
	}
	heap = JC_JFWSystem_getSystemHeap();
	JC_JKRExpHeap_changeGroupID(heap, 5);
	if (0x90(r30) != 0) { // 800065DC
		OSReport("ホットスタート(%08x)", 0x90(r30));
	}
	UnLink(link);
	
	OSReport("どうぶつの森ブートローダ終了\n"); //Animal Crossing Bootloader End
	JW_Cleanup();
	return 0;
}