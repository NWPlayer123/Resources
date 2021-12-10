#include "pch.h"
#pragma once

class AyuStack {
public:
	int size; // *(this + 1);
	int used; // *(this + 2);
	int * fixedBuffer;// *(this + 3)
	int topOfStack; // *(this + 4)
	int unk1;// *(this + 5)
	int bottomOfStack;// *(this + 6)

	char *type[3]; // *(this + 8)
	bool unk2; // (_BYTE *)this + 28 where | | | | | byte * = void *
	bool activated; // *(this + 29)

	void create(char *a2, int a3, void *a4, int a5, bool a6)
	{
		//std::printf("creating stack... \n");
		AyuStack *v6; // ST50_4

		v6 = this;
		//*this = a3;
		this->activated = 1;

		*this->type = a2;

		this->fixedBuffer = (int *)a4;

		v6->topOfStack = a5 + v6->bottomOfStack;

		v6->size = v6->topOfStack - *v6->fixedBuffer;

		this->unk2 = a6;
		if (this->unk2)
			*this->fixedBuffer = 0x12345678;
		//std::printf("resetting stack... \n");
		AyuStack::reset(this);
	}

	void reset(AyuStack *instance)
	{
		instance->unk1 = *instance->fixedBuffer;
		instance->bottomOfStack = instance->topOfStack;
		instance->used = 0;
		//std::printf("reset successfully!\n");
	}

	void * push(int a2)
	{
		void *result; // eax
		int v3; // ST54_4
		int v4; // [esp+4Ch] [ebp-Ch]
		void *v5; // [esp+50h] [ebp-8h]
		int v6; // [esp+60h] [ebp+8h]

		if (!a2)                                    // if a2 = 0 make sure a2 = 1
			a2 = 1;


		if (a2 & 7)
			a2 = (a2 + 7) & 0xFFFFFFF8;                 // make sure a2 is always 8
		v6 = a2 + 8;
		if ((int)this == 2)
		{
			if ((v6 + this->unk1) <= this->bottomOfStack)
			{
				v3 = this->unk1;
				if (this->unk1 == *this->fixedBuffer)
				{
					v4 = 0;
					v5 = (void *)this->unk1;
				}
				else
				{
					v4 = (this->unk1 - 8);
					v5 = (void *)(this->unk1 - 8);
				}
				this->used += v6;
				this->unk1 += v6;
				*(&this->unk1 - 8) = v4 + v6;
				AyuStack::checkStack(this);
				result = v5;
			}
			else
			{
				result = 0;
			}
		}
		else if ((this->bottomOfStack - v6) >= this->unk1)
		{
			this->used += v6;
			this->bottomOfStack -= v6;
			*&this->bottomOfStack = v6;
			result = (void *)(this->bottomOfStack + 8);
		}
		else
		{
			result = 0;
		}
		return result;
	}

	void checkStack(AyuStack *instance)
	{
		if ((int)instance & 2)
		{
			if (instance->unk1 - (instance->unk1 - 8) != *instance->fixedBuffer)
				assert("trashed memory stack\n");
		}
	}

	void pop(AyuStack *instance)
	{
		int v1; // ST54_4
		int v2; // ST50_4

		if ((int)instance == 2)
		{
			v1 = (instance->unk1 - 8);
			instance->used -= v1;
			instance->unk1 -= v1;
		}
		else
		{
			v2 = *&instance->bottomOfStack;
			instance->used -= v2;
			instance->bottomOfStack += v2;
		}
	}

	bool checkOverflow(AyuStack *instance)
	{
		bool result; // al

		if (instance->unk2) // unk2 is true
			result = *instance->fixedBuffer != 0x12345678; // if fixedbuffer isnt equal to 0x12345678 return false
		else
			result = 0;
		return result;
	}

	int getMaxFree(AyuStack *instance)
	{
		int v2; // [esp+4Ch] [ebp-8h]

		if (instance->size - instance->used - 8 <= 0)
			v2 = 0;
		else
			v2 = instance->size - instance->used - 8;
		return v2;
	}

	int getFree(AyuStack *instance)
	{
		return instance->size - instance->used;
	}

	int getTopUsed(AyuStack *instance) // get top used aka top used frames?
	{
		return instance->topOfStack - instance->bottomOfStack; // bottom of stack minus top of the stack = amount used?
	}

	int getSize(AyuStack *instance)
	{
		return instance->size;
	}

	void * operator=(const void *a2)
	{
		memcpy(this, a2, 0x24u);
		return this;
	}
};