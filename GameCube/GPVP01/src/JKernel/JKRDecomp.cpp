JKRDecomp::create(long)
JKRDecomp::JKRDecomp(long)
JKRDecomp::~JKRDecomp(void)
JKRDecomp::run(void)
JKRDecomp::prepareCommand(unsigned char *, unsigned char *, unsigned long, unsigned long, void( *)(unsigned long))
JKRDecomp::sendCommand(JKRDecompCommand *)
JKRDecomp::orderAsync(unsigned char *, unsigned char *, unsigned long, unsigned long, void( *)(unsigned long))
JKRDecomp::sync(JKRDecompCommand *, int)
JKRDecomp::orderSync(unsigned char *, unsigned char *, unsigned long, unsigned long)
void decode(unsigned char *r3, unsigned char *r4, unsigned long r5, unsigned long r6) {
	uint32_t type = checkCompressed(r3);
	if (type == 1) {
		decodeSZP(r3, r4, r5, r6);
	} else if (type == 2) {
		decodeSZS(r3, r4, r5, r6);
	}
	//no need to return anything
}

void JKRDecomp::decodeSZP(unsigned char *, unsigned char *, unsigned long, unsigned long) {
	
}

void JKRDecomp::decodeSZS(unsigned char *, unsigned char *, unsigned long, unsigned long) {
	
}

int checkCompressed(unsigned char *magic) {
	if (magic[0] == "Y" && magic[1] == "a" && magic[3] == "0") {
		if (magic[2] == "y") { //SZP
			return 1;
		}
		else if (magic[2] == "z") { //SZS
			return 2;
		}
	}
	return 0;
}

JKRDecompCommand::JKRDecompCommand(void) {
	
}

JKRDecompCommand::~JKRDecompCommand(void) {
	
}