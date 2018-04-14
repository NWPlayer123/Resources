.text
graph_setup_double_buffer
game_get_next_game_dlftbl
graph_ct
graph_dt
graph_task_set00
graph_draw_finish
void do_soft_reset(void) { //is passed something in code, unused
	(uint8_t)(*prbuf + 0xBF554) = 0;
	mBGM_reset();
	mVibctl_reset();
	sAdo_SoftReset();
	(uint64_t)(*prbuf + 0xBF8D0) = osGetTime();
	prbuf[0xBF8C8 / 4] = 1;
}

void reset_check(void) { //is passed two vars, neither used
	if ((uint8_t)(*prbuf + 0xBF554) != 0) {
		if (osShutdown != 0) {
			do_soft_reset();
		}
	}
}

graph_main(int varA, uint32_t* alloc) {
	(alloc + 0xA4) = 0;
	graph_setup_double_buffer(varA); //double check vars passed
	game_get_controller(alloc);
	(uint8_t*)(alloc + 0x9E) = 0;
	(uint8_t*)(varA + 0x348) = 4;
	game_main(alloc);
	(uint8_t*)(varA + 0x348) = 11;
	if (prbuf[0xBF8C8 / 4] < 2) {
		//not doing the rest of this shit tonight, it does important stuff get it done
	}
}

void graph_proc(void) { //double check this later, confidence level: 8
	graph_ct(prbuf[0xBF560 / 4]);
	uint32_t this_table = &game_dlftbls; //get addr
	uint32_t alloc = 0;
	uint8_t *somevar = (uint8_t)(*prbuf + 0xBF8A8); //shorthand, check compilation
	while (this_table != 0) {
		alloc = malloc(game_dlftbls[0x2C / 4]); //TODO: check if off-by-one
		prbuf[0xBF54C / 4] = alloc;
		bzero(alloc, game_dlftbls[0x2C / 4]);
		somevar = 2;
		game_ct(alloc, game_dlftbls[0x18 / 4], prbuf[0xBF560 / 4]);
		emu64_refresh();
		somevar = 3;
		while (game_is_doing(alloc) != 0) {
			if (dvderr_draw() == 0) {
				graph_main(prbuf[0xBF560 / 4], alloc);
			}
		}
		this_table = game_get_next_game_dlftbl(alloc);
		somevar = 0x12;
		somevar = 0x13; //???
		game_dt(alloc);
		somevar = 0x14;
		free(alloc);
		alloc = 0;
	}
	graph_dt(prbuf[0xBF560 / 4]);
}
.data
@465
.bss
frame$403
SoftResetEnable
skip_frame$483
graph_class