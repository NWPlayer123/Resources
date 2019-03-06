#include "pch.h"
#include "stream.cpp"

// stream class could probably be replace by an ifstream i think... /shrug lol

class CmdStream { 
public:
	void* statbuff;
	void* allocatedBytes;
	int fileLine; // *(this + 69)
	int endOfFilePosition; // *(this + 66)
	char currentChar; // *(this + 1) 
	char * currentWord; // (this + 8)

	CmdStream CmdStreamConstructor(Stream &a2) {
		CmdStream *v2;

		v2 = this;

		v2->statbuff = 0;
		v2->allocatedBytes = 0;
		v2->fileLine = 0;
		v2->endOfFilePosition = 0;
		v2->currentChar = 0;

		//CmdStream::init(a2);
		return *v2;
	}

	void init(Stream &a2) {
		CmdStream *v2;

		v2 = this;
		if (!statbuff) {
			statbuff = malloc(0x8000u);
		}
		memset(statbuff, 0, 0x8000u);
		//*v2 = a2;  *v4 = a2 where v4 is cmdstream and a2 is argument 2 aka stream struct
		allocatedBytes = statbuff;
		CmdStream::fillBuffer(*v2, 1);

	}

	void fillBuffer(CmdStream& a1, bool a2) {
//		int v2; // [esp+4Ch] [ebp-8h]
		//CmdStream *v3; // [esp+50h] [ebp-4h]

		//v3 = &a1;

		// what the fuck does this even mean
		/*
		  int v2; // [esp+4Ch] [ebp-8h]
		  CmdStream *v3; // [esp+50h] [ebp-4h]

		  v3 = this;
		  if ( a2 || *(v3 + 69) - *(v3 + 68) >= 0x4000 )
		  {
			if ( *(v3 + 67) )
			{
			  memcpy((*(v3 + 68) + *(v3 + 1)), (*(v3 + 1) + *(v3 + 68) + 0x4000), 0x4000u);
			  *(v3 + 1) -= 0x4000;
			  *(v3 + 68) += 0x4000;
			}
			v2 = *(v3 + 67) != 0 ? 0x4000 : 0x8000;
			if ( *(v3 + 66) - *(v3 + 67) < v2 )
			  v2 = *(v3 + 66) - *(v3 + 67);
			(*(**v3 + 52))(*v3, *(v3 + 67) + *(v3 + 1), v2);
			*(v3 + 67) += v2;
		  }
		*/
	}

	void copyToToken(CmdStream *instance, int a2) {
		char v2; // [esp+4Ch] [ebp-Ch]
		int i; // [esp+50h] [ebp-8h]

		for (i = 0; i < a2; ++i)
		{
			v2 = instance->currentChar + i + instance->fileLine;
			if (v2 == 9) // what
				v2 = 32;
			instance->currentWord = &v2;
		}
	}

	char skipLine(CmdStream *instance) {
		int i; // [esp+4Ch] [ebp-8h]

		for (i = instance->fileLine; i < instance->endOfFilePosition && instance->currentChar + i != 10 && instance->currentChar + i != 13; ++i);

		CmdStream::copyToToken(instance, i - instance->fileLine);

		while (instance->currentChar + i == 10 || instance->currentChar + i == 13)
			++i;
		instance->fileLine = i;
		return *instance->currentWord;
	}

	void getToken(CmdStream *instance, bool hasComments)
	{
		bool v3; // [esp+4Ch] [ebp-14h]
		signed int v4; // [esp+50h] [ebp-10h]
		int v5; // [esp+54h] [ebp-Ch]
		int v6; // [esp+58h] [ebp-8h]

		if (hasComments)
		{
			while (CmdStream::LineIsComment(instance))      // if its a comment (starts with //) 
				CmdStream::skipLine(instance);                  // skip the line in the file
		}
		v6 = instance->fileLine;
		v5 = 0;
		if ((instance->currentChar) == 34 || (instance->currentChar) == 39) // 34 = " and 39  = '
		{
			v5 = 1; // has tokens
			++v6; //go to next line
			++instance->fileLine; // go to next line
		}
		while (1) // loop indefinetly
		{
			if (v5) // if has "" or ''
			{                                           // if its not an empty line or group of empty spaces
				v4 = (instance->currentChar + v6) == 34 || (instance->currentChar + v6) == 39 ? 0 : 1; // v4 = 0 if current char is ' or "
				v3 = (bool)v4; // bool v3 = 1 or 0
			}
			else
			{ // if it doesnt
				v3 = CmdStream::whiteSpace(instance->currentChar + v6) == 0;// then its whitespace aka empty line or group of empty spaces
			}
			if (!v3)                                  // if v3 is 0 
				break;                                    // break
			++v6;                                       // increment loop
		}

		CmdStream::copyToToken(instance, v6 - instance->fileLine);  // copy values or something idfk what the fuck that is <----

		while (v6 < instance->endOfFilePosition && CmdStream::whiteSpace(instance->currentChar + v6))
			++v6;
		instance->fileLine = v6;
	}

	bool endOfCmds(CmdStream *instance)
	{
		bool result; // al
		CmdStream *v2; // [esp+4Ch] [ebp-4h]

		v2 = this;
		CmdStream::fillBuffer(*v2, 0); // what is fill buffer? whats the purpose?

		while (v2->fileLine < v2->endOfFilePosition && CmdStream::whiteSpace(v2->currentChar + v2->fileLine)) // what in fuck is v2+66???
			++v2->fileLine; // advance position

		if (v2->fileLine >= v2->endOfFilePosition) // is v2+66 the line number that the file ends?
			result = 1; // if fileposition is less than or equal to v2+66
		else
			result = v2->currentChar + v2->fileLine == -1; // result = if current char and fileposition == -1 which should be false 
		return result;
	}

	bool whiteSpace(char toCheck)
	{
		return !toCheck || toCheck == 10 || toCheck == 13 || toCheck == 9 || toCheck == 32 || toCheck == 44;
		// 10 = "line feed" 
        // 13 = "carriage return" aka -\n-
        // 9 = "horizontal tab" aka -	-
        // 32 = "space" aka - -
        // 44 = "comma" aka -,-
	}

	bool LineIsComment(CmdStream *instance) {
		return (instance->fileLine + instance->currentChar) == 35    // if whatever variable 1 and 2 == ascii code 35 aka #, or
			|| (instance->fileLine + instance->currentChar) == 47 && ((instance->fileLine + 1) + (instance->currentChar + 1)) == 47;// if variable 1 and 2  == ascii code 47 aka / and the next one = 47 so
	}

	bool isToken(CmdStream *instance, const char *Str) {
		//return strcmp(instance->currentWord, Str) == 0; 
		size_t wordLength;
		signed int i;
		CmdStream *currCmdStream;

		currCmdStream = instance; // make local variable = bigger instance of class

		if (!strlen(currCmdStream->currentWord))  // if current word is zero then
			return 0; // return bebir

		wordLength = strlen(currCmdStream->currentWord); // size_t v2 = length of current word

		if (wordLength != strlen(Str))  // if length of current word isnt equal to length of input string
			return 0; // return babeee
		
		for (i = 0; i < strlen(currCmdStream->currentWord); ++i) // iterate once for every num of the length
		{
			if (Str[i] != currCmdStream->currentWord[i]) // if the specific char [i] of the input string isnt equal to the specific char [i] of current word;
				return 0;  // return babee
		}

		return 1; // if we dont return, we do now and its true!!! yeeeeeAAAAAT*/
	}

}; 