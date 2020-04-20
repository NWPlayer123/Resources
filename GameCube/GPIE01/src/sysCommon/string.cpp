#include "pch.h"
#include "sysNew.cpp"

class String {
	char * str; // *(this + 1)

	String(void) {
		String::init(this, 64);
	}

	String(int a1) {
		String::init(this, a1);
	}

	String(String * instance, char *a1, int a2) {
		String::init(instance, a1, a2);
	}

	void init(String *instance, int strLength) {
		void *v2;
		String *v3;

		v3 = instance;
		if (strLength) // if non zero value then:
			v2 = allocateBytesOnHeap(strLength + 1); // + 1 for 
		else
			v2 = 0;

		*v3->str = (int)v2;
		*v3 = strLength;
	}

	void init(String *instance, char *strLength, int a3) {
		this->str = strLength;
		*this = a3;
	}

	bool isWhiteSpace(char a1)
	{
		return a1 == 32 || a1 == 9 || a1 == 13 || a1 == 10 || a1 < 32;
	}

	int calcHash(char *a1) {
		char v2; // [esp+4Ch] [ebp-8h]

		String::String((String *)&v2, a1, 0);
		return String::calcHash((String *)&v2);
	}

	int calcHash(String *instance) {
		void *v2; // [esp+4Ch] [ebp-10h]
		unsigned int v3; // [esp+50h] [ebp-Ch]
		int v4; // [esp+54h] [ebp-8h]
		int v5; // [esp+54h] [ebp-8h]

		v4 = 0;
		v2 = (void *)instance->str;
		while (v2)
		{
			v5 = (*(char*)v2 = (char)v2 + 1) + 16 * v4;
			v3 = v5 & 0xF0000000;
			if (v5 & 0xF0000000)
				v5 ^= v3 >> 24;
			v4 = ~v3 & v5;
		}
		return v4;
	}

	int getLength(char *a1)
	{
		char v2; // [esp+4Ch] [ebp-8h]

		String::String((String *)&v2, a1, 0);
		return String::getLength((String *)&v2);
	}

	int getLength(String *instance)
	{
		int v1; // eax
		int i; // [esp+4Ch] [ebp-Ch]
		char *v4; // [esp+50h] [ebp-8h]

		v4 = instance->str;
		for (i = 0; ; ++i)
		{
			v1 = *v4++;
			if (!v1)
				break;
		}
		return i;
	}

	void concat(char *a1, char *a2)
	{
		int v2; // ecx
		int v3; // edx
		char *v4; // [esp+54h] [ebp+8h]

		do
			v2 = *a1++;
		while (v2);
		v4 = a1 - 1;
		do
		{
			*v4 = *a2;
			v3 = *v4++;
			++a2;
		} while (v3);
	}

	bool contains(char *a2)
	{
		return String::contains((char*)this, a2);
	}

	char contains(char *a1, char *a2)
	{
		int v2; // eax
		int v3; // edx
		char *v5; // [esp+4Ch] [ebp-4h]

		v5 = a2;
		while (*a1 && *a2)
		{
			v2 = *a1;
			v3 = *a2++;
			++a1;
			if (v2 == v3)
			{
				if (!*a2)
					return 1;
			}
			else
			{
				a2 = v5;
			}
		}
		return 0;
	}

	char contains(char *a1, char a2)
	{
		char v3; // [esp+4Ch] [ebp-4h]
		char v4; // [esp+4Dh] [ebp-3h]

		v3 = a2;
		v4 = 0;
		return String::contains(a1, &v3);
	}

	char *copy(char *a1, char *a2)
	{
		int v2; // ecx

		do
		{
			*a1 = *a2;
			v2 = *a1++;
			++a2;
		} while (v2);
		return a1;
	}

	bool copyUntil(char *a1, char *a2, char a3, char **a4)
	{
		while (*a2 != a3 && *a2)
			*a1++ = *a2++;
		*a1 = 0;
		if (a4)
			*a4 = a2;
		return *a2 == a3;
	}

	char * dup(char *a1)
	{
		int v1; // eax
		char *v2; // ST58_4

		v1 = String::getLength(a1);
		v2 = (char*)allocateBytesOnHeap(v1 + 1);
		String::copy(v2, a1);
		return v2;
	}

	bool isSame(String *instance, struct String *a2)
	{
		return String::isSame(instance, a2->str);
	}

	bool isSame(String *instance, char *a2)
	{
		int v2; // ecx
		int v3; // eax
		BOOL v5; // [esp+4Ch] [ebp-Ch]
		void *v6; // [esp+50h] [ebp-8h]

		v6 = (void*)instance->str;
		while (v6 && *a2)
		{
			v2 = (char)v6;
			v3 = *a2++;
			(*(int *)v6 = *(int *)v6 + 1);
			if (v2 != v3)
				return 0;
		}
		v5 = v6 || *a2;
		return v5 == 0;
	}

	int toInt(char *a1)
	{
		char v2; // [esp+4Ch] [ebp-8h]

		String::String((String *)&v2, a1, 0);
		return String::toInt((String *)&v2);
	}

	int toInt(String *instance)
	{
		int result; // eax
		int v2; // [esp+4Ch] [ebp-1Ch]
		signed int v3; // [esp+50h] [ebp-18h]
		int v4; // [esp+54h] [ebp-14h]
		int v5; // [esp+54h] [ebp-14h]
		int v6; // [esp+58h] [ebp-10h]
		char *v7; // [esp+5Ch] [ebp-Ch]
		char *v8; // [esp+5Ch] [ebp-Ch]
		char v9; // [esp+60h] [ebp-8h]
		char v10; // [esp+60h] [ebp-8h]

		v7 = instance->str;
		v4 = 0;
		v3 = 0;
		if (*v7 != 48 || v7[1] != 120)
		{
			while (1)
			{
				while (1)
				{
					v10 = *v7++;
					if ((v10 < 48 || v10 > 57) && v10 != 45)
						return 0;
					if (v10 != 45)
						break;
					v3 = 1;
				}
				v5 = (unsigned __int8)(v10 - 48) + v4;
				if (!*v7 || *v7 == 46 || *v7 < 48 || *v7 > 57)
					break;
				v4 = 10 * v5;
			}
			if (v3)
				v5 = -v5;
			result = v5;
		}
		else
		{
			v6 = 0;
			v8 = v7 + 2;
			while (1)
			{
				v9 = *v8++;
				if (!v9)
					break;
				if (v9 < 48 || v9 > 57)
				{
					if (v9 < 97 || v9 > 102)
					{
						if (v9 < 65 || v9 > 70)
							return 0;
						v2 = v9 - 55;
					}
					else
					{
						v2 = v9 - 87;
					}
				}
				else
				{
					v2 = v9 - 48;
				}
				v6 += v2;
				if (*v8)
					v6 *= 16;
			}
			result = v6;
		}
		return result;
	}
};