	OSReport("モジュール(%s)の読み込み中\n", name); //Loading Module (/foresta.rel.szs)
	uint32_t handle = JC__JKRDvdToMainRam_byName(name, 0, 1);
JKRDvdRipper::loadToMainRAM("/foresta.rel.szs", 0, 1, 0, 0, 1, 0, 0);

loadToMainRAM(const char *name, unsigned char *, JKRExpandSwitch, unsigned long, JKRHeap *, JKRDvdRipper::EAllocDirection, unsigned long, int *) {
	DvdFile = JKRDvdFile::JKRDvdFile();
	ret = DvdFile.open(name); //keeps it open in the object, returns code, not handle
	if (ret & 0xFF != 0) {
		delete DvdFile;
		return 0;
	}
	ret = loadToMainRAM_3(DvdFile, restofarguments);
	delete DvdFile;
	return ret;
	//this is done, minus syntax errors
}


loadToMainRAM_2(long, unsigned char *, JKRExpandSwitch, unsigned long, JKRHeap *, JKRDvdRipper::EAllocDirection, unsigned long, int *) {
	
}
loadToMainRAM_3(JKRDvdFile *, unsigned char *, JKRExpandSwitch, unsigned long, JKRHeap *, JKRDvdRipper::EAllocDirection, unsigned long, int *) {
	
	
	
	OSPanic("JKRDvdRipper.cpp", 0x129, "Sorry, not prepared for SZP resource\n");
	
	OSPanic("JKRDvdRipper.cpp", 0x132, ":::Not support SZP with offset read");
	
	
}
JKRDecompressFromDVD(JKRDvdFile *, void *, unsigned long, unsigned long, unsigned long, unsigned long)
decompSZS_subroutine(unsigned char *, unsigned char *)
firstSrcData(void)
nextSrcData(unsigned char *)
JKRDvdRipper::isErrorRetry((void))
__sinit_JKRDvdRipper_cpp
__dt__23JSUList_12JKRDMCommand_Fv