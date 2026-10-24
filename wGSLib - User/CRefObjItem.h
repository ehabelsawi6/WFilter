#ifndef CREFOBJITEM_H
#define CREFOBJITEM_H
#include "pch.h"


class CRefObjItem
{
public:
	char pad_0004[4]; //0x0004
	uintptr_t RefObjID; //0x0008
	char pad_000C[92]; //0x000C
	char* DescriptionText; //0x0068
	char pad_006C[140]; //0x006C
	char* BsrFileName; //0x00F8
	char pad_00FC[24]; //0x00FC
	char* BsrDropFileName; //0x0114
	char pad_0118[24]; //0x0118
	char* DdjFilePath; //0x0130
	char pad_0134[1808]; //0x0134

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0844


#endif