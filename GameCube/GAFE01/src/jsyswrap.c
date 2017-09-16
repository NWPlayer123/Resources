JW_GetAramAddress(int index) { //finished??
	if (24 >= index >= 0) {
		return JC_JKRAramArchive_getAramAddress_byName(&forest_arc_aram_p, "DATA", aram_resName[index << 2]);
	} else {
		if (76 >= index >= 24) {
			return JC_JKRAramArchive_getAramAddress_byName(&forest_arc_aram2_p, "DATA", aram_resName[index << 2]);
		}
	}
	return 0;
}