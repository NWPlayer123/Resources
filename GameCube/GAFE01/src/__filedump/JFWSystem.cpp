void firstInit(void) {
	OSInit();
	DVDInit();
	root = JKRExpHeap::createRoot(MaxStdHeap, false);
	JKRExpHeap::create(SysHeapSize, root, false);
}