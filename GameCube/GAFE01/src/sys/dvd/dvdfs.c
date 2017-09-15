__DVDFSInit
DVDConvertPathToEntrynum(const char *path) { //unfinished but kms
	if (path[0] == 0) {
		return currentDirectory;
	}
	while (path[0] == "/") //bleh, complicating loops
		*path++;
	
	OSPanic("dvdfs.c", 0x178,
			"DVDConvertEntrynumToPath(possibly DVDOpen or DVDChangeDir or DVDOpenDir): "
			"specified directory or file (%s) doesn't match standard 8.3 format. "
			"This is a temporary restriction and will be removed soon\n", path);
	
}
DVDFastOpen
DVDOpen
DVDClose
entryToPath
DVDGetCurrentDir
DVDReadAsyncPrio
cbForReadAsync
DVDReadPrio
cbForReadSync
DVDPrepareStreamAsync
cbForPrepareStreamAsync
