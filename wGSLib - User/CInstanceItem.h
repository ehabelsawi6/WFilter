#ifndef CINSTANCEITEM_H
#define CINSTANCEITEM_H
#include "pch.h"
#include "CRefObjItem.h"

class CInstanceItem
{
public:
	char pad_0000[16]; //0x0000
	class CDBTable* DBTable; //0x0010
	char pad_0014[4]; //0x0014
	CRefObjItem* pCRefObjItem; //0x0018
	char pad_001C[4]; //0x001C
	uintptr_t ItemId; //0x0020
	char pad_0024[4]; //0x0024
	uintptr_t RefItemId; //0x0028
	char pad_002C[24]; //0x002C
}; //Size: 0x0044


#endif