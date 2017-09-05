__start(void) {
	__init_registers();
	__init_hardware();
}

__init_registers(void) {
	asm("
		lis       r1, -0x7FDF # 0x8021A710
		ori       r1, r1, 0xA710 # 0x8021A710
		lis       r2, -0x7FDE # 0x80220BE0
		ori       r2, r2, 0xBE0 # 0x80220BE0
		lis       r13, -0x7FDF # 0x8021FB80
		ori       r13, r13, 0xFB80 # 0x8021FB80
		blr
	");
}