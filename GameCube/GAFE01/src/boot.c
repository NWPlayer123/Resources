uint32_t soundArenaAlloc(void) {
	return 0; //stubbed ??
}

int search_partial_address(uint32_t address) {
	if (address == 0) {
		return -1;
	}
	//unfinished, irritating
}

uint32_t convert_partial_address(uint32_t address) { //unfinished
	ret = search_partial_address(address, <stack r4 r5 r6>);
	if (ret != 0) {
		return address;
	}
	asm("
		lwz	   r3, 0xC(r1)
		lwz	   r0, 8(r1)
		slwi	  r3, r3, 28
		clrlwi	r0, r0, 7
		add	   r3, r3, r0
	");
	//restore stack frame, return
	
}

void LoadStringTable(const char name) {
	OSReport(﻿"ストリングテーブル読み込み開始\n"); //Start Reading String Table
	uint64_t time = osGetTime(); // ???
	uint32_t table = JC__JKRDvdToMainRam_byName(name, 0, 1);
	if (table == 0) {
		OSDVDFatalError();
	}
	*StringTable = table;
	OSSetStringTable(&StringTable);
	uint64_t time = osGetTime(); // ???
	OSReport("ストリングテーブル読み込み 完了\n"); //String Table Loading Complete
}

void UnLink(uint32_t link) {
	if (link != 0) {
		value = link[0x38];
		if (value != 0) {
			OSReport("エピローグ開始\n"); //Epilogue Start
			goto value; //mtctr, bctrl
			OSReport("エピローグ完了\n"); //Epilogue Complete
		}
		OSReport("アンリンク中\n"); //Unlink Start
		OSUnlink(link);
		OSReport("アンリンク完了\n"); //Unlink Complete
	}
	JW_Free(link);
}

LoadLink(const char name) { //unfinished
	OSReport("モジュール(%s)の読み込み中\n", name); //Loading Module (/foresta.rel.szs)
	uint32_t handle = JC__JKRDvdToMainRam_byName(name, 0, 1);
	if (handle == 0) { //couldn't load file
		OSReport("モジュール(%s)の読み込みに失敗しました\n");
		OSDVDFatalError();
	} else {
		OSReport("モジュール(%s)の読み込み完了\n");
		OSReport("module=%08x\n");
		OSReport("result=%08x\n");
		size = JW_GetMemBlockSize(handle);
		OSReport("length=%08x\n", size);
		JC__JKRDetachResource(handle);
	}
	OSReport("サウンドアリーナ %08x 使用 bss=%08x\n");
	
	
	
	return OSLink(handle, smth); // we want this to happen
	goto handle[0x34]; //mtctr, bctrl
}

void audioFatalCallback(void) {
	OSReport("audioFatalCallback\x1B[m\n");
	OSDVDFatalError();
}

void sound_initial(void) {
	Na_InitAudio(*audioFatalCallback, 0, 0, *nintendo_hi_0, 0x66A0, 0);
	OSReport("sizeof(nintendo_hi_0)=%08x\n", 0x9900); //sizeof(nintendo_hi_0)=00009900
	OSReport("実際のnintendo_hi_0.awのサイズ=%08x \n", 0x66A0); //Actual size of nintendo_hi_0.aw = 000066A0
	OSReport("ニンテンドー発生タイムラグまで寝てます(%dms)\x1B[m\n", 0x9C4);
	msleep(0x9C4);
}

void sound_initial2(void) {
	while (Na_CheckNeosBoot() & 0xFF == 0) {
		VIWaitForRetrace();
		Na_GameFrame();
	}
	bzero(nintendo_hi_0, 0x9900);
}

void HotResetIplMenu(void) {
	if (80206F9C & 0x10)
		OSChangeBootMode(1);
	OSResetSystem(1, &80206F9C, 1);
}

fault_callback_keyCheck() { //unfinished
	fault_Printf("PUSH %s\n");
}

void fault_callback_OK(void) {
	fault_Printf("\nOK! YOU ARE GREAT!\n");
	fault_WaitTime(0x7D0);
}

void fault_callback_Setumei(void) {
	fault_Printf(
		""
		"+ KEY to SCROLL UP/DOWN"
		"B BUTTON : TOP OF CONSOLE"
		"A BUTTON : BOTTOM OF CONSOLE");
}
void fault_callback_vimode() { //unfinished
	OSReport("貸し出しバージョンなのでコードは出しません\n");
	OSReport("B+X+STARTでリスタートします\n");
	JW_SetFamicomMode(0);
	JW_SetLowResoMode(0);
}
void fault_callback_scroll() { //unfinished
	
}
adjustOSArena() { //unfinished
	OSReport("ARENA %08x-%08x\x1B[m\n");
	OSReport("搭載メモリが 24MB を超えていますが、24MB に限定します。\x1B[m\n");
	OSReport("搭載メモリが 32MB を超えていますが、32MB に限定します。\x1B[m\n");
	OSReport("搭載メモリが 32MB を超えています。\x1B[m\n");
	OSReport("搭載メモリが 24MB 以下なので動かない事がありえます。\x1B[m\n");
}

//	OSReport("L+R+X+Y+Down, START BUTTON");

main() { //unfinished
	ReconfigBATS();
	if (fakemain_check != 0) {
		return -1;
	}
	fakemain_check = 1;
	OSReport("NDEBUG defined.\x1B[m\n");
	OSReport("_DEBUG not defined.\x1B[m\n");
	OSReport("DEBUG=%d\x1B[m\n", 0);
	uint64_t time = osGetTime(); // 800E2288
	OSInit();
	OSInitAlarm();
	OSGetStackPointer();
	
	bzero(osAppNMIBuffer, 0x40);
	int code = OSGetResetCode(); //can be negative
	if (code == 0) {
		OSReport("システムパワーオン\n");
	} else if (code > 0 || code > 0x80000001) {
		OSReport("ホットリセット\n");
		OSReport("OSGetResetCode=0x%08x\n", OSGetResetCode());
	} else {
		OSReport("リスタート\n");
		OSGetSaveRegion(); //unfinished, gets stack vars something
		OSReport("OSGetSaveRegion %08x %08x\n");
		bcopy(0x811FFFC0, osAppNMIBuffer, 0x40);
	}
	
	
	
	
	OSReport("リリース版ではリセットコードを無視します\n");
	OSChangeBootMode(0);
	OSResetSystem(1, &80206F9C, 0);
	DVDGetCurrentDiskID();
	OSReport("デベロップメントモードに戻します。そしてリセット\x1B[m\n");
	OSReport("ZURUMODE2 ENABLE\n");
	OSReport("osAppNMIBuffer[15]=0x%08x\n");
	OSReport("異常状態でのリセット検出ゆえリセットさん免除フラグをセットしました\x1B[m\n");
	
	
	
	
	OSReport("どうぶつの森ブートローダ起動\n");
	adjustOSArena();
	JW_init();
	
	
	JC_JUTException_setMapFile("/static.map");
	JC_JUTException_enterAllPad(JC_JUTException_getManager());
	fault_Init();
	fault_AddClientEx(StringTable + 0x10, fault_callback_vimode, 0, 0, 0xA, 0xE);
	fault_AddClientEx(StringTable + 0x24, fault_callback_keyCheck, &tbl_544, &800A97E4, 0xA, 0xE);
	fault_AddClientEx(StringTable + 0x38, fault_callback_OK, 0, 0, 0xA, 0xE);
	fault_AddClientEx(StringTable + 0x4C, fault_callback_Setumei, 0, 0, 0xA, 9);
	fault_AddClientEx(StringTable + 0x60, fault_callback_scroll, 0, 0, 1, 9);
	fault_AddClient(StringTable + 0x74, DisplayArena, 0, 0);
	
	//math here
	
	OSReport("InitialStartTime=%u us\n");
	sound_initial();
	initial_menu_init();
	dvderr_init();
	sound_initial2();
	if(!(OSGetConsoleType() & 0x10000000)) { //Retail Mode
		OSReport("以降OSReportを無効\n");
		OSReportDisable();
	}
	OSReport("Loging COPYDATE\n");
	uint32_t handle = JC__JKRDvdToMainRam_byName("/COPYDATE", 0, 1);
	if (handle == 0) {
		OSDVDFatalError();
	}
	LoadStringTable("/static.str");
	uint32_t link = LoadLink("/foresta.rel.szs");
	JW_Init2();
	initial_menu_cleanup();
	if (link == 0) {
		LoadLink("/foresta.rel.szs"); //try again ??
	}
	uint32_t heap = JC_JFWSystem_getSystemHeap();
	JC_JKRExpHeap_changeGroupID(heap, 5);
	while (0x90(r30) == 0) { //callback loop ???
		OSReport("ホットスタート(%08x)\n", 0x90(r30));
		goto 0x90(r30); //mtctr, bctrl, callback something
	}
	Unlink(link);
	link = 0;
	if (&r30 != 0) {
		JW_Free();
		&r30 = 0; //some var
	}
	OSReport("どうぶつの森ブートローダ終了\n");
	JW_Cleanup();
	return 0;
}