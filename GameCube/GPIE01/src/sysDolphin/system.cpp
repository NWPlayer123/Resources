openFile__6SystemFPcbb
initSoftReset__6SystemFv
beginRender__6SystemFv
doneRender__6SystemFv
waitRetrace__6SystemFv

void System::run(BaseApp *app) { //r3 context, r4 BaseApp
	GXInvalidateTexAll();
	while (true) {
		Jac_Gsync()
		CARDProbe(0);
		CARDProbe(1);
		ControllerMgr::update(); //passes context
		System::updateSysClock(); //passes context
		OSCheckActiveThreads();
		app->idle();
	}
}

System::getTime(void) {
	
}
updateSysClock__6SystemFv
parseArchiveDirectory__6SystemFPcPc
read__9DVDStreamFPvi
getPending__9DVDStreamFv
ParseMapFile__Fv
hardReset__6SystemFv
__ct__6SystemFv
initBigFont__Fv
showDvdError__6SystemFR8Graphics
Initialise__6SystemFv
sndPlaySe__6SystemFUl
__dt__6SystemFv
loadFunc__FPv
draw__9LoadIdlerFR8Graphics
init__9LoadIdlerFv
startLoading__6SystemFP9LoadIdlerbUl
nudgeLoading__6SystemFv
endLoading__6SystemFv
doneDMA__FUl
copyWaitUntilDone__6SystemFv
copyRamToCache__6SystemFUlUlUl
copyCacheToRam__6SystemFUlUlUl
freeBuffer__FUl
copyCacheToTexture__6SystemFP12CacheTexture
dvdFunc__FPv
nudgeDvdThread__6SystemFv
startDvdThread__6SystemFv
flush__9LogStreamFv
write__9LogStreamFPvi
close__9DVDStreamFv
invoke__29Delegate1<6System,R8Graphics>FR8Graphics
__sinit_system_cpp
getPending__10AramStreamFv
read__10AramStreamFPvi