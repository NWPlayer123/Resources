#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef CMDSTREAM_H
#define CMDSTREAM_H

#include "Stream.h"

class SYSCORE_API CmdStream {
private:
	Stream* strm;
	char* buffer; //this + 4
	char currentToken[256];
	int pending;
	int currentChar;
	int unkVar2;
	int unkVar3;
public:
	static char* statbuff;

	CmdStream() {}
	CmdStream(Stream* strm);

	void init(Stream*);
	void fillBuffer(bool canFill);
	void copyToToken(int);

	char nextChar();
	bool isToken(char* Str);
	char* getToken(bool hasComments);
	char* skipLine();

	bool LineIsComment();
	bool whiteSpace(char toCheck);
	bool endOfCmds();
	bool endOfSection();
};

#endif

char* CmdStream::statbuff;

CmdStream::CmdStream(Stream* strm)
{
	this->init(strm);
}

void CmdStream::init(Stream* stream)
{
	this->buffer = 0;
	if (!CmdStream::statbuff)
	{
		CmdStream::statbuff = (char*)malloc(sizeof(char) * 0x8000); //or = new char[0x8000]
	}
	memset(CmdStream::statbuff, 0, 0x8000);
	this->strm = stream;
	this->pending = this->strm->getPending();
	this->currentChar = 0;
	this->unkVar2 = 0;
	this->unkVar3 = 0;
	this->buffer = CmdStream::statbuff;
	this->fillBuffer(1);
}

void CmdStream::fillBuffer(bool canFill)
{
	if (canFill || this->currentChar - this->unkVar3 >= 0x4000)
	{
		if (this->unkVar2)
		{
			memcpy(this->buffer + this->unkVar3, this->buffer + this->unkVar3 + 0x4000, 0x4000);
			this->buffer -= 0x4000;
			this->unkVar3 += 0x4000;
		}

		int result = this->unkVar2 != 0 ? 0x4000 : 0x8000;

		if (this->pending - this->unkVar2 < result)
			result = this->pending - this->unkVar2;

		this->strm->read(this->buffer + this->unkVar2, result);
		this->unkVar2 += result;
	}
}

bool CmdStream::LineIsComment()
{
	return  *(this->buffer + this->currentChar) == '#'
		|| *(this->buffer + this->currentChar) == '/'
		&& *(this->buffer + this->currentChar + 1) == '/';
}

void CmdStream::copyToToken(int length)
{
	int i = 0;
	while(i < length) {
		char currentChar = *(this->buffer + i + this->currentChar);

		if (currentChar == '\t')
			currentChar = ' ';
		this->currentToken[i] = currentChar;
		i++;
	}
	this->currentToken[i] = 0;
}

bool CmdStream::endOfCmds()
{
	this->fillBuffer(0);
	while (this->currentChar < this->pending && this->whiteSpace(*(this->buffer + this->currentChar))) {
		this->currentChar++;
	}

	if (this->currentChar < this->pending)
		return *(this->buffer + this->currentChar) == -1;

	else
		return 1;

}

bool CmdStream::whiteSpace(char toCheck)
{
	return !toCheck
		|| toCheck == '\n'
		|| toCheck == '\r'
		|| toCheck == '\t'
		|| toCheck == ' '
		|| toCheck == ',';
}

bool CmdStream::endOfSection()
{
	this->fillBuffer(0);
	return *(this->buffer + this->currentChar) == '}';
}

char* CmdStream::getToken(bool hasComments)
{
	this->fillBuffer(0);

	if (hasComments)
	{
		while (this->LineIsComment())
			this->skipLine();
	}

	int currChar = this->currentChar;
	char tempIdentifier = 0;

	if (*(this->buffer + currChar) == '"' || *(this->buffer + currChar) == '\'')
	{
		tempIdentifier = 1;
		++currChar;
		++this->currentChar;
	}

	while (1)
	{
		int shouldBreak;
		if (tempIdentifier)
		{
			shouldBreak = *(this->buffer + currChar) == '"' || *(this->buffer + currChar) == '\'' ? 0 : 1;;
		}

		else
		{
			shouldBreak = this->whiteSpace(*(this->buffer + currChar)) == 0;
		}

		if (!shouldBreak)
			break;

		++currChar;

	}

	this->copyToToken(currChar - this->currentChar);

	if (tempIdentifier)
		this->currentToken[currChar++ - this->currentChar] = 0;

	while (currChar < this->pending && this->whiteSpace(*(this->buffer + currChar)))
		++currChar;

	this->currentChar = currChar;
	return this->currentToken;
}

char* CmdStream::skipLine()
{
	this->fillBuffer(0);
	int i = this->currentChar;
	while(i < this->pending && *(this->buffer + i) != '\n' && *(this->buffer + i) != '\r') {
		i++;
	}

	this->copyToToken(i - this->currentChar);

	while (*(this->buffer + i) == '\n' || *(this->buffer + i) == '\r')
		++i;

	this->currentChar = i;

	return this->currentToken;
}

char CmdStream::nextChar()
{
	return *(this->buffer + this->currentChar);
}

bool CmdStream::isToken(char* Str)
{
	if (!strlen(this->currentToken))
		return false;

	if (strlen(this->currentToken) != strlen(Str))
		return false;

	for (int i = 0; i < strlen(this->currentToken); ++i)
	{
		if (Str[i] != this->currentToken[i])
			return false;
	}

	return true;
}