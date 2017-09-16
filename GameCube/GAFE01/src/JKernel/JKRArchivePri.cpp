__ct__10JKRArchiveFv
__ct__10JKRArchiveFlQ210JKRArchive10EMountMode
__dt__10JKRArchiveFv

JKRArchive::isSameName(JKRArchive::CArcName &r4, unsigned long r5, unsigned short r6) {
	
}

findResType__10JKRArchiveCFUl
findDirectory__10JKRArchiveCFPCcUl
JKRArchive::findTypeResource(unsigned long resourceType, const char *name) { //unfinished
	if (resourceType != 0) {
		stored = JKRArchive::CArcName::store(name);
		ret = JKRArchive::findResType(resourceType);
		if (ret != 0) {
			JKRArchive::isSameName(stored, );
		}
	}
	return 0;
}

findFsResource__10JKRArchiveCFPCcUl
findIdxResource__10JKRArchiveCFUl
findNameResource__10JKRArchiveCFPCc
findPtrResource__10JKRArchiveCFPCv
store__Q210JKRArchive8CArcNameFPCc
store__Q210JKRArchive8CArcNameFPCcc