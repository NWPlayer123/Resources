IsCard
CARDProbeEx
DoMount
__CARDMountCallback

int CARDMountAsync(int card_id, r4, r5, *callback) { //should be finished
	if (card_id != 0 && card_id != 1)
		return -128; //invalid card_id
	if (!*(uint8_t)(0x800030E3) &= 0x80)
		return -3;
	handle = OSDisableInterrupts();
	__CARDBlockBase = __CARDBlock + (card_id * 0x110);
	if (*(__CARDBlockBase + 4) == -1) {
		OSRestoreInterrupts(handle);
		return -1;
	}
	if (*__CARDBlockBase == 0) {
		state = EXIGetState(card_id);
		if (!state &= 8) {
			OSRestoreInterrupts(handle);
			return -2;
		}
	}
	*(__CARDBlockBase + 4) = -1;
	*(__CARDBlockBase + 0x80) = r4;
	*(__CARDBlockBase + 0xC4) = r5;
	if (callback == 0)
		callback = __CARDDefaultApiCallback;
	*(__CARDBlockBase + 0xD0) = callback;
	*(__CARDBlockBase + 0xCC) = 0;
	if (*__CARDBlockBase == 0) {
		if (EXIAttach(card_id, __CARDExtHandler) == 0) {
			*(__CARDBlockBase + 4) = -3; //LAST_ERROR ?
			OSRestoreInterrupts(handle);
			return -3;
		} //else fallthrough
	}
	*(__CARDBlockBase + 0x24) = callback;
	*__CARDBlockBase = 0;
	EXISetExiCallback(card_id, 0);
	OSCancelAlarm(&__CARDBlockBase + 0xE0);
	*(__CARDBlockBase + 0x84) = callback;
	*(__CARDBlockBase + 0x88) = callback;
	OSRestoreInterrupts(handle);
	*(__CARDBlockBase + 0xDC) = __CARDMountCallback;
	if (EXILock(card_id, 0, __CARDUnlockedHandler) != 0) {
		*(__CARDBlockBase + 0xDC) = callback;
		return DoMount(card_id);
	}
	return 0;
}

int CARDMount(card_id, r4, r5) { //mini-function
	ret = CARDMountAsync(card_id, r4, r5, __CARDSyncCallback);
	if (ret > 0)
		return __CARDSync(card_id);
	else
		return ret;
}


DoUnmount
CARDUnmount