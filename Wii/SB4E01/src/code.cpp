sub_8000CFB0(r3) {
	valid = false;
	if (&r3 != 0) {
		value = r3[4];
		if (value >= 0) {
			valid = true;
		}
	}
	if (valid == false) {
		return 0;
	} else {
		r3 = r3[4];
		if (&&r3 != 0) {
			r0 = &&r3;
		} else {
			r0 = 0;
		}
	}
	if (r3 < r0) {
		return 1;
	} else {
		return 0;
	}
}

sub_8022D980() {
	ret = sub_8045A970();
	ret = sub_80459A00(ret, 0x39);
	ret[0x20] = ret[0x18];
}

sub_80456490() {
	sub_8022D980()
}

sub_80459A00(r3, r4) {
	return r3[r4 << 2]; //some table
}

sub_8045A970() {
	r3 = &807D0DA4;
	r3 = r3[0x24];
	return sub_804BA7F0(r3);
}

sub_804BA7F0() {
	r3 = r3[0x12C];
	r3 = r3[0x10];
	return r3;
}