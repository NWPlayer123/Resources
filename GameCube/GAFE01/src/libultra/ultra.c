bcopy(void *src, const void *dst, uint32_t size) { //src and dst are backwards? sigh
	memmove(dst, src, size);
}

bcmp(const void *ptr1, const void *ptr2, uint32_t size) {
	memcmp(ptr1, ptr2, size);
}

bzero(void *data, uint32_t size) {
	memset(data, 0, size);
}

osSyncPrintf {
	
}

void osWritebackDCache(void *addr, uint32_t size) {
	DCStoreRange(addr, size);
}

osGetCount(void) {
	return OSGetTick();
}