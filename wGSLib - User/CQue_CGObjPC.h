#ifndef CQUE_CGOBJPC_H
#define CQUE_CGOBJPC_H
#include "pch.h"

//Que containing a list of CGObjPCs... should I use template shit later?
class CQue_CGObjPC
{
public:
	char pad_0000[8]; //0x0000
	uintptr_t Unk1; //0x0008
	void* HeapPointer; //0x000C
	char pad_0010[4]; //0x0010
	uintptr_t UsageCount; //0x0014
	uintptr_t AvailableCount; //0x0018
	uintptr_t N0000131E; //0x001C
	char pad_0020[4]; //0x0020
	uintptr_t N00001320; //0x0024
	char pad_0028[4]; //0x0028
	uintptr_t ObjCount; //0x002C
	uintptr_t SizePossibly; //0x0030
	char pad_0034[4]; //0x0034
	char N00004647[4]; //0x0038
	char N00004648[4]; //0x003C
	char N00004334[4]; //0x0040
	char N00004335[4]; //0x0044
	uintptr_t ClassNameLength; //0x0048
	uintptr_t ClassNameLengthMaxPossibly; //0x004C
	char pad_0050[12]; //0x0050
	uintptr_t SizePossibly2; //0x005C
}; //Size: 0x0060

#endif