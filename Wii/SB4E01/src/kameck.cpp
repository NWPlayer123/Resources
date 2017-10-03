sub_801A4990(r3 *table, r4 **allocation) { //??? @ r4
	sub_8000C1E0(table, allocation, "Kameck", 0); //???
	sub_80010070(&table + 0xA4, &table + 0xB4, &table); //some other setup func
	sub_801A4B50(table, allocation);
	sub_801A4B00(table);
	ret = sub_8000F020(someinitval, float(r2 - 0x4234), float(r2 - 0x4234), float(r2 - 0x4234));
	sub_8005C0D0(table, ret, float(r2 - 0x4234));
	ret2 = sub_80501850(0x1C);
	if (ret2 != 0) {
		sub_801501D0(ret2, 0);
	}
	sub_80150260(); //??
	ret3 = sub_80006EB0(someinitval2, float(r2 - 0x4234));
	sub_8041A8E0(table, 0, ret3);
	sub_80034D20(table);
	ret4 = sub_8002C9B0(allocation);
	if (ret4 != 0) {
		sub_80052230(table);
		sub_80051F30(table);
	}
	sub_80237C00(table, r13 - 0x4B48, 1);
	ret5 = sub_80501850(0x1C);
	if (ret5 != 0) {
		sub_8014FD90(ret5, table, ret2);
	}
	sub_80019ED0(table, ret5, r13 - 0x4B24, "SupportFreeze");
	sub_801A4C30(table, allocation); //cleanup ??
	sub_801A5820(table);
	sub_8001AA10(table, allocation);
	//return???
}