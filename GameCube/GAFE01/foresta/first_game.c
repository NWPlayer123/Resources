exit_game() {
	famicom_setCallback_getSaveChan(mCD_GetThisLandSlotNo_code);
	mBGM_ct();
	mVibctl_ct();
	common_data_init();
}
first_game_cleanup
first_game_init(int something) {
	
}