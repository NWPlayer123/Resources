_prolog(void) {
	if (construct_skip == 0) {
		count = &ctors_addr;
		if (count != 0) {
			while (&ctors_addr != 0) {
				ctors_addr += 4;
			}
		}
	}
	main();
}
_epilog
_unresolved