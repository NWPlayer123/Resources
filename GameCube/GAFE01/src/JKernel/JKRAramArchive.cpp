JKRAramArchive::JKRAramArchive(void) { //constructor

}

JKRAramArchive::JKRAramArchive(long, JKRArchive::EMountDirection) { //constructor

}

JKRAramArchive::~JKRAramArchive(void) { //destructor
	
}

JKRAramArchive::fixedInit(long, JKRArchive::EMountDirection) {
	
}

JKRAramArchive::mountFixed(long, JKRArchive::EMountDirection) {
	if (r4 < 0) {
		return 0;
	} //otherwise
	ret = JKRArchive::check_mount_already(r4);
	if (ret != 0) {
		return 0;
	}
	fixedInit(r4, r5);
	ret = JKRAramArchive::open(r4) & 0xFF;
	if (ret == 0) { //error
		return 0;
	}
	//does some C++ object stuff here
	JSUPtrList::prepend(*JKRFileLoader::sVolumeList);
	return 1;
}

JKRAramArchive::mountFixed(char const *, JKRArchive::EMountDirection) {
	
}

JKRAramArchive::unmountFixed(void) {
	
}

JKRAramArchive::open(long) {
	
}

JKRAramArchive::fetchResource(JKRArchive::SDIFileEntry *, unsigned long *) {
	
}

JKRAramArchive::fetchResource(void *, unsigned long, JKRArchive::SDIFileEntry *, unsigned long *, JKRExpandSwitch) {
	
}

JKRAramArchive::getAramAddress_Entry(JKRArchive::SDIFileEntry *) {
	
}

JKRAramArchive::getAramAddress(unsigned long, char const *) {
	
}

JKRAramArchive::fetchResource_subroutine(unsigned long, unsigned long, unsigned char *, unsigned long, int) {
	
}

JKRAramArchive::fetchResource_subroutine(unsigned long, unsigned long, JKRHeap *, int, unsigned char **) {
	OSPanic("JKRAramArchive.cpp", 0x25D, ":::??? bad sequence\n");
}
