//rlwinm.   r0, r0, 0,23,23 is (0x80000000 >> 23)
void step0_make_dl(stack) { //might just be void
	// unfinished??? not much important
	# JW_JUTReport(x, y, ??, msg, ...)
	diskID = DVDGetCurrentDiskID(); //always 0x80000000
	date = &boot_copyDate;
	if (date != 0) {
		JW_JUTReport(0x96, 0x190, 1, "COPYDATE: %.17s");
	}
	if  (diskID != 0) { // loaded in from apploader?
		JW_JUTReport(0x96, 0x14A, 1, "<DISK ID>");
		JW_JUTReport(0x96, 0x156, 1, "GAMENAME: %.4s", diskID);
		JW_JUTReport(0x96, 0x162, 1, " COMPANY: %.2s", diskID + 4);
		JW_JUTReport(0x96, 0x16E, 1, " VERSION: 0x%02X(%d)", (uint8_t)diskID + 7
	} //else just skip the info
	JW_JUTReport(0x96, 0x14A, 1, "<DISK ID>"); //prints twice ??
	JW_JUTReport(0x96, 0x32, 1, "SDK VERSION: 12Dec2001 Patch4");
	fontenc = OSGetFontEncode();
	fontenc &= 0xFF; //clrlwi r0, r3, 16 aka bits 16-31 aka 0xFFFF
	if (fontenc == 1) {
		JW_JUTReport(0x96, 0x64, 1, " ****** WARNING ******");
		JW_JUTReport(0x96, 0x70, 1, "The DISP SW is JAPAN MODE now");
		JW_JUTReport(0x96, 0x7C, 1, "but this GAME is NES version");
	}
	foo = osAppNMIBuffer[0x3C];
	if (foo == foo & 0x100) {
		JW_JUTReport(0x96, 0x19A, 1, "SHOP PROMOTE VERSION");
	}
		
}
make_dl_nintendo_logo
step1_make_dl
step2_make_dl
void make_dl() {
	step0_make_dl();
	if (menu_step == 1) {
		step1_make_dl();
	}
	else if (menu_step != 11) {
		if (menu_step != 2) {
			step2_make_dl();
		}
	}
	// some pointer stuff
}

exec_dl
keycheck
proc
my_alloc
my_free
initial_menu_init
initial_menu_cleanup