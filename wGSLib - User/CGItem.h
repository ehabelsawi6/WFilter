#ifndef CGITEM_H
#define CGITEM_H
#include "CInstanceItem.h"
#include "pch.h"
class CGItem
{
public:
	char pad_0000[8]; //0x0000
	uintptr_t UniqueIdPossibly; //0x0008
	char pad_000C[40]; //0x000C
	CInstanceItem* pCInstanceItem; //0x0034
	char pad_0038[8]; //0x0038
}; //Size: 0x0040
#endif