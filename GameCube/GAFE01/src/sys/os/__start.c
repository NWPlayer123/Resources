__check_pad3
__start(void) { //entrypoint after apploader
	__init_registers();
	__init_hardware();
	//stack frame
}
__init_registers(void) {
	asm("
		lis       r1, 0x8021       //r1  = 0x80210000
		ori       r1, r1, 0xA710   //r1  = 0x8021A710
		lis       r2, 0x8022       //r2  = 0x80220000
		ori       r2, r2, 0x0BE0   //r2  = 0x80220BE0
		lis       r13, 0x8021      //r13 = 0x80210000
		ori       r13, r13, 0xFB80 //r13 = 0x8021FB80
		blr                        //return to __start
	");
}

__init_data