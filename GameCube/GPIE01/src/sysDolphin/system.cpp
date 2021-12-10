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

// This is from a DLL found on 'any' pikmin disc
// hardReset__6SystemFv
StdSystem System::hardReset(StdSystem *this)
{
  StdSystem *v1; // ST60_4
  struct Texture *v2; // eax
  StdSystem *result; // eax

  v1 = this;
  *(this + 5) = j_allocateBytesOnHeap(0x10u);
  v2 = StdSystem::loadTexture(v1, "consFont.bti", 1);
  Font::setTexture(*(v1 + 5), v2, 16, 8);
  StdSystem::set2DRoot(gsys, "screen/otona_blo/", "screen/otona_tex/");
  result = v1;
  *(v1 + 282) = 0;
  return result;
}

__ct__6SystemFv
__dt__6SystemFv
__sinit_system_cpp
beginRender__6SystemFv
close__9DVDStreamFv
copyCacheToRam__6SystemFUlUlUl
copyCacheToTexture__6SystemFP12CacheTexture
copyRamToCache__6SystemFUlUlUl
copyWaitUntilDone__6SystemFv
doneDMA__FUl
doneRender__6SystemFv
draw__9LoadIdlerFR8Graphics
dvdFunc__FPv
endLoading__6SystemFv
flush__9LogStreamFv
freeBuffer__FUl
getPending__10AramStreamFv
getPending__9DVDStreamFv
initBigFont__Fv
initSoftReset__6SystemFv
init__9LoadIdlerFv
initialise__6SystemFv
invoke__29Delegate1<6System,R8Graphics>FR8Graphics
loadFunc__FPv
nudgeDvdThread__6SystemFv
nudgeLoading__6SystemFv
openFile__6SystemFPcbb
parseArchiveDirectory__6SystemFPcPc
parseMapFile__Fv
read__10AramStreamFPvi
read__9DVDStreamFPvi
showDvdError__6SystemFR8Graphics
sndPlaySe__6SystemFUl
startDvdThread__6SystemFv
startLoading__6SystemFP9LoadIdlerbUl
updateSysClock__6SystemFv
waitRetrace__6SystemFv
write__9LogStreamFPvi