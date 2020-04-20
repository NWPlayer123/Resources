#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include <cstdarg>
#include <algorithm>
#include <Windows.h>
#include "stream.cpp"

#ifndef FRAS
#define FRAS

class FileRandomAccessStream : public RandomAccessStream {
public:
	// 0h - vtable
	//(Stream: 4h)
	FILE* fStream; // 8h
	int dwordC; // Ch
	int fileSize; // 10h 

	FileRandomAccessStream(FILE* fpointer, char* cwd);
	virtual int getPosition();
};

#endif

#ifndef STDSYSTEM_H
#define STDSYSTEM_H

class CacheTexture;
class LoadIdler;
class AnimData;
class GfxobjInfo;
class Texture;
class Graphics;
class AyuHeap;
class LFInfo;
class Shape;
class LFlareGroup;

class SYSCORE_API StdSystem {
public:
	bool pending;	//4h
	double fade;	//8h this + 8

	char* baseDir;	//50h

	char* bloRoot;  //48h this + 72
	char* texRoot;  //4Ch this + 76

	char* dataRoot;	//54h this + 84
	int unkShutdownCode; //1C8h this + 456

	StdSystem();

	virtual void					initSoftReset();
	virtual RandomAccessStream* openFile(char*, bool, bool);
	virtual void					copyRamToCache(unsigned int, unsigned int, unsigned int);
	virtual void					copyCacheToRam(unsigned int, unsigned int, unsigned int);
	virtual void					copyWaitUntilDone();
	virtual void					copyCacheToTexture(CacheTexture*);
	virtual void					Activate(bool);
	virtual void					parseArchiveDirectory(char*, char*);
	virtual void					sndPlaySe(unsigned int) = 0;
	virtual void					startLoading(LoadIdler*, bool, unsigned int);
	virtual void					endLoading();

	bool							isShutdown();
	bool							isActive() { return (this->unkShutdownCode & 0x200000) == 0x200000; }
	void							setActive(bool set) { }
	double							getHalfRand(float a);
	double							getRand(float a);
	bool							resetPending();
	void							set2DRoot(char* _bloroot, char* _texroot);
	
	/*
		void		 Shutdown();
		void		 addAnimation(AnimData*, char*);
		void		 addGfxObject(GfxobjInfo*);
		void		 addTexture(Texture*, char*);
		void		 ageAnyAnimations();
		void		 attachObjs();
		void		 detachObjs();
		AnimData*	 findAnimation(char*);
		AnimData*	 findAnyAnimation(char*);
		GfxobjInfo*	 findAnyGfxObject(char*, unsigned int);
		int			 findAnyIndex(char*, char*);
		GfxobjInfo*	 findGfxObject(char*, unsigned int);
		AnimData*	 findIndexAnimation(char*, int);
		GfxobjInfo*	 findTexture(Texture*);
		void		 flushLFlares(Graphics*);
		void		 genAge(AgeServer*);
		void		 getAppMemory(char*);
		float		 getFade();
		float		 getHalfRand(float);
		AyuHeap*	 getHeap(int);
		int			 getHeapNum();
		LFInfo*		 getLFlareInfo();
		double		 getRand(float);
		Shape*		 getShape(char*, char*, char*, bool);
		void		 initLFlares(int);
		void		 invalidateObjs(unsigned int, unsigned int);
		bool		 isActive();
		AnimData*	 loadAnimation(Shape*, char*, bool);
		void		 loadBundle(char*, bool);
		Shape*		 loadShape(char*, bool);
		Texture*	 loadTexture(char*, bool);
		void		 onceInit();
		void		 parseArchiveDirectory(char*, char*);
		LFlareGroup* registerLFlare(Texture*);
		void		 resetHeap(int, int);
		void		 resetLFlares();
		void		 resetPending();
		void		 set2DRoot(char*, char*);
		void		 setActive(bool);
		void		 setDataRoot(char*);
		void		 setFade(float, float);
		void		 setFrameClamp(int);
		void		 setHeap(int);
		void		 setTextureBase(char*, char*);
		void		 softReset();*/
		static char* stringDup(char*);

		//StdSystem operator=(const StdSystem&);
};

#endif

//////////////////////////////////////////////////////////////////////
// FileRandomAccessStream class functions
//////////////////////////////////////////////////////////////////////

FileRandomAccessStream::FileRandomAccessStream(FILE* fpointer, char* cwd) : RandomAccessStream() {
	this->fStream = fpointer;
	this->currentWorkingDir = cwd;
	this->dwordC = 0;

	int offset = this->getPosition();
	fseek(this->fStream, 0, SEEK_END);
	this->fileSize = ftell(this->fStream);
	fseek(this->fStream, offset, SEEK_SET);
}

int FileRandomAccessStream::getPosition() {
	return ftell(this->fStream);
}

//////////////////////////////////////////////////////////////////////
// StdSystem class functions
//////////////////////////////////////////////////////////////////////

StdSystem::StdSystem()
{

}

void StdSystem::initSoftReset() {

}

RandomAccessStream* StdSystem::openFile(char*, bool, bool) {
	return new FileRandomAccessStream(0, 0);
}

void StdSystem::copyRamToCache(unsigned int, unsigned int, unsigned int) {

}

void StdSystem::copyCacheToRam(unsigned int, unsigned int, unsigned int) {

}

void StdSystem::copyWaitUntilDone() {

}

void StdSystem::copyCacheToTexture(CacheTexture*) {

}

void StdSystem::Activate(bool) {

}

void StdSystem::parseArchiveDirectory(char*, char*) {

}

void StdSystem::startLoading(LoadIdler*, bool, unsigned int) {

}

void StdSystem::endLoading() {

}

bool StdSystem::isShutdown() {
	return (this->unkShutdownCode) == 0x80000000;
}
/*
void StdSystem::Shutdown() {}
void StdSystem::addAnimation(AnimData*, char*) {}
void StdSystem::addGfxObject(GfxobjInfo*) {}
void StdSystem::addTexture(Texture*, char*) {}
void StdSystem::ageAnyAnimations() {}
void StdSystem::attachObjs() {}
void StdSystem::detachObjs() {}
AnimData* StdSystem::findAnimation(char*) {}
AnimData* StdSystem::findAnyAnimation(char*) {}
GfxobjInfo* StdSystem::findAnyGfxObject(char*, unsigned int) {}
int StdSystem::findAnyIndex(char*, char*) {}
GfxobjInfo* StdSystem::findGfxObject(char*, unsigned int) {}
AnimData* StdSystem::findIndexAnimation(char*, int) {}
GfxobjInfo* StdSystem::findTexture(Texture*) {}
void StdSystem::flushLFlares(Graphics*) {}
void StdSystem::genAge(AgeServer*) {}
void StdSystem::getAppMemory(char*) {}
float StdSystem::getHalfRand(float) {}
AyuHeap* StdSystem::getHeap(int) {}
int StdSystem::getHeapNum() {}
LFInfo* StdSystem::getLFlareInfo() {}
Shape* StdSystem::getShape(char*, char*, char*, bool) {}
void StdSystem::initLFlares(int) {}
void StdSystem::invalidateObjs(unsigned int, unsigned int) {}
bool StdSystem::isActive() {}
bool StdSystem::isShutdown() {}
AnimData* StdSystem::loadAnimation(Shape*, char*, bool) {}
void StdSystem::loadBundle(char*, bool) {}
Shape* StdSystem::loadShape(char*, bool) {}
Texture* StdSystem::loadTexture(char*, bool) {}
void StdSystem::onceInit() {}
void StdSystem::parseArchiveDirectory(char*, char*) {}
LFlareGroup* StdSystem::registerLFlare(Texture*) {}
void StdSystem::resetHeap(int, int) {}
void StdSystem::resetLFlares() {}
void StdSystem::resetPending() {}
void StdSystem::set2DRoot(char*, char*) {}
void StdSystem::setActive(bool) {}
void StdSystem::setDataRoot(char*) {}
void StdSystem::setFade(float, float) {}
void StdSystem::setFrameClamp(int) {}
void StdSystem::setHeap(int) {}
void StdSystem::setTextureBase(char*, char*) {}
void StdSystem::softReset() {}*/

char* allocateBytesOnHeap(size_t size) {
	return 0;
}

char* StdSystem::stringDup(char* str) {
	size_t size = strlen(str) + 1;
	char* dst = allocateBytesOnHeap(size);
	memcpy(dst, str, size);
	return dst;
}

double StdSystem::getHalfRand(float a) {
	return (rand() / 32767.0 - 0.5) * a;
}

double StdSystem::getRand(float a) {
	return rand() / 32767.0 * a;
}

bool StdSystem::resetPending() {
	return this->pending;
}

void StdSystem::set2DRoot(char* _bloroot, char* _texroot) {
	this->bloRoot = _bloroot;
	this->texRoot = _texroot;
}
