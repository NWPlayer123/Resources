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
	
	
	
	LoadStringTable("/static.str");
	LoadLink("/foresta.rel.szs");
	JW_Init2();
}