step0_make_dl
make_dl_nintendo_logo
step1_make_dl
step2_make_dl() {
	r6 = *r3;
	*r6 = 0xDB060020;
}


void make_dl(var) { //incomplete
	uint32_t var = var;
	step0_make_dl(var);
	if (menu_step == 1 || menu_step != 11) { //???
		step1_make_dl(var);
	} else if (menu_step == 0) {
		step2_make_dl(var);
	}
	//??????????
	var += 8;
	*var[0] = 0xE9000000;
	*var[1] = 0;
	var += 8;
	*var[0] = 0xDF000000;
	*var[1] = 0;
}


void exec_dl(r3) { //incomplete
	emu64_init();
	emu64_taskstart(r3);
	emu64_cleanup();
}

keycheck
void proc() {
	uint32_t mesg = 0;
	osRecvMesg(commandQ, mesg, 1);
	progressive_mode = 0;
	fadeout_step = 0;
	menu_step = 0;
	select_done = 0;
	load_game_done = 0;
	start_time = osGetTime();
	pad_good_frame_count = -1;
	frame_count = 0;
	limit_time = 202500000; //not bothering to do math, is constant
	if (OSGetResetSwitchState() != 0)
		__osResetSwitchPressed = 1;
	else {
		if (__osResetSwitchPressed != 0)
			osShutdownStart(0);
	}
	uint32_t ret = osRecvMesg(commandQ, mesg, 0);
	if (ret == 0) {
		if (mesg == 0x8888)
			fadeout_step = 2;
		if (mesg == 0x9999)
			load_game_done = 1;
	}
	if (fadeout_step == 0 && select_done != 0 && load_game_done != 0) {
		fadeout_step = 1;
		osSetTimer(something); //I'm not doing this shit
		JC_JFWDisplay_startFadeOut(JC_JFWDisplay_getManager(), 0x20);
		
	}
	if (menu_step == 0)
		dvderr_draw();
	
	
	
	
	
	osSendMesg(statusQ, mesg, 0);
}

uint32_t my_alloc(uint32_t size) {
	return JW_Alloc(size, 0x20); //alignment
}

void my_free(uint32_t* addr) {
	JW_Free(addr);
}

void initial_menu_init(void) {
	Thread_p = my_alloc(0x310);
	initialMenuStack = my_alloc(0x2800);
	if (*Thread_p == 0 || initialMenuStack == 0) {
		OSReport("initial_menu_init: Memory insufficiency.\n");
		my_free(Thread_p);
		*Thread_p = 0;
		my_free(initialMenuStack);
		*initialMenuStack = 0;
	} else {
		osCreateMesgQueue(commandQ, commandMsg, 2);
		osCreateMesgQueue(commandQ, commandMsg, 1);
		//r4 aka 1 gets optimized out ? sigh
		osCreateThread2(*Thread_p, 1, proc, 0, *initialMenuStack + 0x2800, 0x2800, 1);
		osStartThread(*Thread_p);
		JC_JFWDisplay_startFadeIn(JC_JFWDisplay_getManager(), 0x20);
		osSendMesg(commandQ, 0x1234, 0);
	}
	//if invalid, fallthrough and return
}

void initial_menu_cleanup(void) {
	if (*Thread_p != 0) {
		uint32_t mesg = 0;
		uint32_t ret = osRecvMesg(commandQ, &mesg, 0); //stores in mesg
		if (ret == 0) { //returned valid
			osSendMesg(commandQ, 0x9999, 0);
			osRecvMesg(statusQ, &mesg, 1);
		}
		osDestroyThread(*Thread_p);
	} //fallthrough
	JW_SetLogoMode(0);
	JC_JFWDisplay_startFadeIn(JC_JFWDisplay_getManager(), 0x20);
	my_free(Thread_p);
	*Thread_p = 0;
	my_free(initialMenuStack);
	*initialMenuStack = 0;
}