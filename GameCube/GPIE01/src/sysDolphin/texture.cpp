Texture::Texture(void) {
	
}

Texture::getAlpha(int, int) {
	
}

Texture::read(RandomAccessStream *stream) { //very wonky, maybe finished?
	size = strlen(&stream); //filename
	result = strcmp(&stream + size - 3, "txe"); //uses SDA/r13
	if (result == 0) { //is equal
		alloc = System::alloc(0x34);
		if (alloc != 0) {
			alloc[0x00] = 0x8022738C; // ???
			alloc[0x00] = 0x8022737C; // ???
			alloc[0x10] = 0;
			alloc[0x0C] = 0;
			alloc[0x08] = 0;
			alloc[0x04] = 0x803DD4A4;
			alloc[0x00] = TexImg::`vtbl';
			alloc[0x24] = 1;
			alloc[0x30] = 0;
		}
		TexImg::importTxe(alloc, stream);
	} else {
		size = strlen(&stream); //filename
		result = strcmp(&stream + size - 3, "bti"); //uses SDA/r13
		if (result == 0) {
			alloc = System::alloc(0x34);
			if (alloc != 0) {
				alloc[0x00] = 0x8022738C; // ???
				alloc[0x00] = 0x8022737C; // ???
				alloc[0x10] = 0;
				alloc[0x0C] = 0;
				alloc[0x08] = 0;
				alloc[0x04] = 0x803DD4A4;
				alloc[0x00] = TexImg::`vtbl';
				alloc[0x24] = 1;
				alloc[0x30] = 0;
			} //else it'll probably handle no alloc
			TexImg::importBti(alloc, stream, 0);
		} else {
			strlen(&stream); //??? immediately discarded
		}
	}
	StdSystem::addTexture(gsys, stream);
}

Texture::detach(void) {
	
}

Texture::attach(void) {
	
}

Texture::createBuffer(int, int, int, void *) {
	
}

Texture::grabBuffer(int, int, bool, bool) {
	
}

Texture::decodeData(TexImg *) {
	
}

void Texture::makeResident(void) {
	return; //stubbed
}
