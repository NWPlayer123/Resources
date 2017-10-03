void __cdecl main(int argc, const char **argv, const char **envp) {
	System::Initialise(); //passes gsys
	alloc = System::alloc(0x18);
	if (alloc != 0) //successfully made
		nodeMgr = NodeMgr::NodeMgr(alloc);
	app = System::alloc(0x54);
	if (app != 0) //successfully made
		PlugPikiApp::PlugPikiApp(app);
	System::run(app);
	OSPanic("sysBootup.cpp", 29, "End of demo"); //this shouldn't happen
}