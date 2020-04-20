#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef STREAM_H
#define STREAM_H

#ifndef STRING_H
#define STRING_H

class SYSCORE_API String {
public:
	int m_stringLen;
	char* m_string;

	String();
	String(int stringLength);
	String(char* string, int stringLength);

	double toFloat() { return 0.0; }
	int toInt();

	void init(int stringLength);
	void init(char* string, int stringLength);

	int calcHash();
	unsigned __int32 calcHash(char*);

	static int getLength(char*);
	int getLength();

	static char* dup(char*);
	char* dup();

	static void concat(char*, char*);
	static char* copy(char*, char*);
	static bool isSame(char*, char*);
	bool isSame(char*);
	bool isSame(String*);
	static bool isWhiteSpace(char);
	static bool copyUntil(char*, char*, char, char**);
	static bool equals(char*, char*);
	static bool contains(char*, char*);
	static bool contains(char*, char);
	bool contains(char*);
};

#endif


String::String() {
	this->init(64);
}

String::String(int stringLength) {
	this->init(stringLength);
}

String::String(char* string, int stringLength) {
	this->init(string, stringLength);
}

void String::init(int _stringLength) {
	char * _tempStr;

	if (_stringLength)
		_tempStr = new char[_stringLength + 1]; // v2 = allocateBytesOnHeap(a2 + 1);
	else
		_tempStr = 0;
	this->m_string = _tempStr;
	this->m_stringLen = _stringLength;
}

void String::init(char* _string, int _stringLength) {
	this->m_string = _string;
	this->m_stringLen = _stringLength;
}

int String::calcHash() {
	int hash = 0;
	char* string = this->m_string;

	while (*string)
	{
		int unkPurpose = 16 * hash + *string++;

		unsigned int unkPurpose2 = unkPurpose & 0xF0000000;
		if (unkPurpose2)
			unkPurpose ^= unkPurpose2 >> 24;
		hash = ~unkPurpose2 & unkPurpose;
	}

	return hash;
}

unsigned __int32 String::calcHash(char* _string) {
	String toCalcHash(_string, 0);

	return toCalcHash.calcHash();
}

bool String::contains(char* arg) {
	return this->contains(this->m_string, arg);
}

bool String::contains(char* str1, char* str2) {
	char* tempChar = str2;
	while (*str1 && *str2)
	{
		if (*str1++ == *str2++) {
			if (!*str2) {
				return 1;
			}
		}
		else
		{
			str2 = tempChar;
		}
	}
	return 0;
}

bool String::contains(char* a1, char a2) {
	char temp = a2;

	return String::contains(a1, &temp);
}

bool String::isSame(String* toCompare) {
	return this->isSame(toCompare->m_string);
}

bool String::isSame(char* a1) {
	char* str = this->m_string;
	while (*str && *a1)
	{
		if (*str++ != *a1++)
			return 0;
	}

	int retVal = *str || *a1;
	return retVal == 0;
}

bool String::isSame(char* s1, char* s2) {
	String tempStr(s1, 0);
	return tempStr.isSame(s2);
}

bool String::equals(char* str1, char* str2) {
	return String::isSame(str1, str2);
}

char* String::dup() {
	return String::dup(this->m_string);
}

char* String::dup(char* a1) {
	char* newStr = new char[String::getLength(a1) + 1];
	String::copy(newStr, a1);
	return newStr;
}

int String::getLength(char* string) {
	String tempStr(string, 0);
	return tempStr.getLength();
}

int String::getLength() {
	int i = 0;
	char* tempString = this->m_string;
	for (i = 0; ; ++i)
	{
		if (!(*tempString++))
			break;
	}
	return i;
}

char* String::copy(char* arg1, char* arg2) {
	int loop = 0;
	while (loop)
	{
		*arg1 = *arg2;
		loop = *arg1++;
		++arg2;
	}
	return arg1;
}

void String::concat(char* arg1, char* arg2) {
	int arg1Iter;
	do
		arg1Iter = *arg1++;
	while (arg1Iter);

	char* tempChar = arg1 - 1;
	int temp;
	do
	{
		*tempChar = *arg2;
		temp = *arg1++;
		++arg2;
	} while (temp);
}

bool String::isWhiteSpace(char toCheck) {
	return toCheck == ' ' || toCheck == '\t' || toCheck == '\r'
		|| toCheck == '\n' || toCheck < ' ';
}

bool String::copyUntil(char* a1, char* a2, char a3, char** a4) {
	while (*a2 != a3 && *a2)
		* a1++ = *a2++;

	*a1 = 0;
	if (a4)
		* a4 = a2;
	return *a2 == a3;
}

int String::toInt() {
	char* string = this->m_string;
	int unk1 = 0;
	bool unk2 = false;
	char nextChar;

	if (*string != '0' || string[1] != 'x')
	{
		int unk3;
		while (!*string || *string == '.' || *string < '0' || *string > '9')
		{
			while (nextChar != '-')
			{
				nextChar = *string++;
				if ((nextChar < '0' || nextChar > '9') && nextChar != '-')
					return 0;
				unk2 = true;
			}
			unk3 = (nextChar - '0') + unk1;
			unk1 = 10 * unk3;		
		}
		if (unk2)
			unk3 = -unk3;
		return unk3;
	}
	  else
  {
    int unk3 = 0;
    char* unk4 = string + 2;
	int unk5;
    while ( 1 )
    {
      nextChar = *unk4++;
      if ( !nextChar )
        break;
      if ( nextChar < '0' || nextChar > '9' )
      {
        if ( nextChar < 'a' || nextChar > 'f' )
        {
          if ( nextChar < 'A' || nextChar > 'F' )
            return 0;
          unk5 = nextChar - '7';
        }
        else
        {
          unk5 = nextChar - 'W';
        }
      }
      else
      {
        unk5 = nextChar - '0';
      }
      unk3 += unk5;
      if ( *unk4 )
        unk3 *= 16;
    }
    return unk3;
  }
}

#include <cstdarg>
#include <algorithm>

class SYSCORE_API Stream {
public:
	// 0h - vtable
	char* currentWorkingDir; // 4h

	Stream();

	// Reading functions
	virtual int readInt();
	virtual char readByte();
	virtual short readShort();
	virtual float readFloat();
	virtual char* readString();
	virtual void readString(String&);
	virtual void readString(char*, int);

	//Writing functions
	virtual void writeInt(int);
	virtual void writeByte(unsigned __int8);
	virtual void writeShort(short);
	virtual void writeFloat(float);
	virtual void writeString(char*);
	virtual void writeString(String&);

	// Core read/write functions
	virtual void read(void*, int) {}
	virtual void write(void*, int) {}

	// 'Getter' functions
	virtual int getPending() { return 0; }
	virtual int getAvailable() { return 0; }

	// Misc. functions (gets overloaded)
	virtual void close() {}
	virtual bool getClosing() { return 0; }
	virtual void flush() {}

	// Printing functions
	void print(char*, ...);
	void vPrintf(char*, char*);
};

#endif

Stream::Stream()
{
}

void Stream::print(char* Format, ...)
{
	char Dest[256]; // [esp+50h] [ebp-400h]
	va_list va; // [esp+460h] [ebp+10h]

	va_start(va, Format);
	vsprintf(Dest, Format, va);
	if (strlen(Dest))
	{
		this->write(Dest, strlen(Dest));
	}
}

void Stream::vPrintf(char* Format, char* Args)
{
	char resultantString[256];

	vsprintf(resultantString, Format, Args);


	if (strlen(resultantString))
	{
		this->write(resultantString, strlen(resultantString));
	}
}

int Stream::readInt()
{
	int c;
	this->read(&c, sizeof(int));
	return ((c & 0xFF000000) >> 24) | ((c & 0xFF0000) >> 8) | ((c & 0xFF00) << 8) | (c << 24);
}

char Stream::readByte()
{
	char c;
	this->read(&c, sizeof(unsigned char));
	return c;
}

short Stream::readShort()
{
	short c;
	this->read(&c, sizeof(short));
	return ((c & 0xFF00) >> 8) | (c << 8);
}

float Stream::readFloat()
{
	int c;
	this->read(&c, sizeof(float));
	c = (c << 24) | ((c & 0xFF00) << 8) | ((c & 0xFF0000) >> 8) | ((c & 0xFF000000) >> 24);
	return static_cast<float>(c);
}

char* Stream::readString()
{
	int stringLength = this->readInt();
	char* returnValue = new char[stringLength + 1];

	this->read(returnValue, stringLength);

	returnValue[stringLength] = 0;
	return returnValue;
}

void Stream::readString(String & str)
{
	int stringLength = this->readInt();

	if (str.m_stringLen < stringLength)
		str.init(stringLength);

	this->read(str.m_string, stringLength);

	str.m_string[stringLength] = 0; // null terminate string
}

void Stream::readString(char* string, int stringLength)
{
	String tempVar(string, stringLength);
	this->readString(tempVar);
}

void Stream::writeInt(int toW)
{
	unsigned int wr = ((toW & 0xFF000000) >> 24) | ((toW & 0xFF0000) >> 8) | ((toW & 0xFF00) << 8) | (toW << 24);
	this->write(&wr, sizeof(wr));
}

void Stream::writeByte(unsigned __int8 toW)
{
	this->write(&toW, sizeof(toW));
}

void Stream::writeShort(short toW)
{
	short wr = ((toW & 0xFF00) >> 8) | (toW << 8);
	this->write(&wr, sizeof(wr));
}

void Stream::writeFloat(float toW)
{
	unsigned int temp = *reinterpret_cast<unsigned int*>(&toW);
	temp = (temp << 24) | ((temp & 0xFF00) << 8) | ((temp & 0xFF0000) >> 8) | ((temp & 0xFF000000) >> 24);
	this->write(&temp, sizeof(float));
}

void Stream::writeString(String & str)
{
	int strleng = (str.getLength() + 3) & ~3;
	this->writeInt(strleng);
	this->write(str.m_string, str.getLength());

	char tempBuf = 0;
	for (int i = 0; ; ++i)
	{
		if (i >= strleng - str.getLength())
			break;
		this->write(&tempBuf, 1);
	}
}

void Stream::writeString(char* toW)
{
	String tempStr(toW, 0);
	this->writeString(tempStr);
}

#ifndef RAS_H
#define RAS_H

class SYSCORE_API RandomAccessStream : public Stream {
public:
	// 0h - vtable
	// (Stream: 4h)

	// (Stream VTable 0 - 76)
	RandomAccessStream();
	virtual int getPending();// 80
	virtual int getPosition() { return 0; }//92
	virtual void setPosition(int) { }//88
	virtual int getLength() { return this->getAvailable(); } //84

	void padFile(unsigned __int32 toPad);
	void padFileTo(unsigned __int32 a1, unsigned __int32 a2);
	void readFrom(int arg1, void* buffer, int length);
	int readIntFrom(int position);
	void skipPadding(unsigned __int32 paddingAmount);
};

#endif


RandomAccessStream::RandomAccessStream() { }

int RandomAccessStream::getPending()
{
	return this->getPosition() - this->getLength();
}

void RandomAccessStream::padFile(unsigned __int32 toPad)
{
	int length = this->getLength();
	int amount = ((length + toPad - 1) & ~(toPad - 1)) - length;
	for (int i = 0; i < amount; ++i)
		this->writeByte(0);
}

void RandomAccessStream::padFileTo(unsigned __int32 a1, unsigned __int32 a2)
{
	int length = this->getLength();
	int amount = a1 - length - a2;
	for (int i = 0; i < amount; ++i)
		this->writeByte(0);
}

void RandomAccessStream::readFrom(int arg1, void* buffer, int length)
{
	this->setPosition(arg1);
	this->read(buffer, length);
}

int RandomAccessStream::readIntFrom(int position)
{
	this->setPosition(position);
	return this->readInt();
}

void RandomAccessStream::skipPadding(unsigned __int32 paddingAmount)
{
	int length = this->getLength();
	int resultAmount = (~(paddingAmount - 1) & (length + paddingAmount - 1)) - length;
	for (int i = 0; i < resultAmount; ++i)
		char temp = this->readByte();
}
