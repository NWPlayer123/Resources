osDestroyThread(*thread) {
	if (thread == 0) {
		OSCancelThread(OSGetCurrentThread);
	} else {
		OSCancelThread(thread);
	}
}