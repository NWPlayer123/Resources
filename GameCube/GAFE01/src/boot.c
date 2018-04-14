soundArenaAlloc
search_partial_address
convert_partial_address
LoadStringTable
UnLink
LoadLink
audioFatalCallback
sound_initial
sound_initial2
HotResetIplMenu
fault_callback_keyCheck
fault_callback_OK
fault_callback_Setumei
fault_callback_vimode
fault_callback_scroll
adjustOSArena
int main(int argc, const char **argv) { //mostly finished :D
	ReconfigBATs();
	if (fakemain_check == 0) {
		//some dumb debug print, NDEBUG defined, _DEBUG not defined, DEBUG=0
		InitialStartTime = osGetTime(); //uint64_t
		OSInit();
		OSInitAlarm();
		if (OSGetStackPointer() - 0x100 <= OSGetCurrentThread()[0x304 / 4]) { //should be right math???
			if (OSGetStackPointer() - 0x100 >= OSGetCurrentThread()[0x308 / 4] + 4) { //messy, fix this when you get thread shit in
				memset(OSGetCurrentThread()[0x308 / 4] + 4, 0xFD, (OSGetStackPointer() - 0x100) - (OSGetCurrentThread()[0x308 / 4] + 4));
			}
		}
		bzero(osAppNMIBuffer, 0x40); //zero out
		if (OSGetResetCode() == 0) {
			OSReport("System Power On\n");
		} else if (OSGetResetCode() > 0x80000001) {
			OSReport("Restart\n"); //Resetti's gonna be angery
			uint32_t start, end;
			OSGetSaveRegion(start, end);
			OSReport("OSGetSaveRegion %08x %08x\n", start, end);
			bcopy(0x811FFFC0, osAppNMIBuffer, 0x40); //bcopy osAppNMIBuffer to 0x811FFFC0
		} else {
			OSReport("Hot Reset\n"); //not sure that's the right term but okie
			OSReport("OSGetResetCode=0x%08x\n", OSGetResetCode());
			OSReport("Ignore the reset code in release version\n"); //well you left this comment so ¯\_(ツ)_/¯
		}
		__osInitialize_common();
		if (OSGetConsoleType() & 0x10000000 != 0) {
			osAppNMIBuffer[15] |= 0x10;
		} else if (osAppNMIBuffer[15] & 0x10 != 0) {
			OSReport("Resetting and returning to development mode\n");
			OSChangeBootMode(0);
			OSResetSystem(1, osAppNMIBuffer[15], 0);
		}
		//normally uses DVDGetCurrentDiskID for the +7 but fuck dat
		if ((uint8_t)*0x80000007 == 0x99) { //Version ID
			OSReport("ZURUMODE2 ENABLE\n");
			osAppNMIBuffer[15] |= 0x68; //combining several checks
		}
		OSReport("osAppNMIBuffer[15]=0x%08x\n", osAppNMIBuffer[15]);
		if (osAppNMIBuffer[15] & 4 != 0) {
			osAppNMIBuffer[15] &= 0xE;
			osAppNMIBuffer[15] |= 0x2;
			OSReport("Set an exception flag that was reset due to resetting an irregular status.\n");
		} else {
			osAppNMIBuffer[15] &= 7;
		}
		osAppNMIBuffer[15] |= 4;
		OSReport("Animal Crossing Bootloader Start\n");
		adjustOSArena();
		JW_Init();
		if (osAppNMIBuffer[15] & 0x20 != 0) {
			JC_JUTProcBar_setVisible(JC_JUTProcBar_getManager(), (osAppNMIBuffer[15] >> 6) & 1);
			JC_JUTProcBar_setVisibleHeapBar(JC_JUTProcBar_getManager(), (osAppNMIBuffer[15] >> 6) & 1);
		}
		JC_JUTException_setMapFile("/static.map");
		JC_JUTException_enterAllPad(JC_JUTException_getManager());
		fault_AddClientEx(my_fault_client5, fault_callback_vimode, 0, 0, 10, 14);
		fault_AddClientEx(my_fault_client1, fault_callback_keyCheck, tbl, tbl[1] << 8 | tbl[2], 10, 14); //load uint16s
		fault_AddClientEx(my_fault_client2, fault_callback_OK, 0, 0, 10, 14);
		fault_AddClientEx(my_fault_client3, fault_callback_Setumei, 0, 0, 10, 9);
		fault_AddClientEx(my_fault_client6, fault_callback_scroll, 0, 0, 1, 9);
		fault_AddClient(my_fault_client4, DisplayArena, 0, 0); //0, 1);
		if (osAppNMIBuffer[15] & 0x40 != 0) {
			JC_JUTAssertion_changeDevice(3);
			JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), 1);
		} else {
			JC_JUTAssertion_changeDevice(2);
			JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), 0);
		}
		JC_JUTAssertion_changeDisplayTime(600);
		//OSReport("InitialStartTime=%u us\n", __div2u(somemathIdontwannado));
		sound_initial();
		initial_menu_init();
		dvderr_init();
		sound_initial2();
		if (OSGetConsoleType() & 0x10000000 == 0) {
			OSReport("Disabling OSReport\n");
			OSReportDisable();
		}
		OSReport("Logging COPYDATE\n");
		boot_copyDate = JC__JKRDvdToMainRam_byName("/COPYDATE", 0, 1);
		if (boot_copyDate == 0) {
			OSDVDFatalError();
		}
		LoadStringTable("/static.str");
		moduleA = LoadLink("/foresta.rel.szs");
		JW_Init2();
		initial_menu_cleanup();
		if (moduleA == 0) {
			moduleA = LoadLink("/foresta.rel.szs");
		}
		JC_JKRExpHeap_changeGroupID(JC_JFWSystem_getSystemHeap(), 5);
		while (HotStartEntry != 0) { //main loop
			OSReport("Entry Point: %08x\n");
			HotStartEntry = HotStartEntry(); //call and store ret
		}
		UnLink(moduleA);
		moduleA = 0;
		if (StringTable != 0) {
			JW_Free(StringTable);
			StringTable = 0;
		}
		OSReport("Animal Crossing Bootloader End\n");
		JW_Cleanup();
		return 0;
	}
	return -1;
}