__osInitialize_common() {
	osShutdown = 0;
	__osFinalrom = 1;
	__osShutdownDisable = 0;
	__osShutdown = 0;
	__osResetKeyStep = 0;
	__osResetSwitchPressed = 0;
	if (__osInitialized == 0) {
		__osTimerServicesInit();
		__osContinitialized = 0;
		__osInitialized = 1;
	}
}