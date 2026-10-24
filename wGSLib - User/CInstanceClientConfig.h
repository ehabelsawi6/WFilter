#ifndef CINSTANCECLIENTCONFIG_H
#define CINSTANCECLIENTCONFIG_H
#include "pch.h"
#include "CDBTable.h"
class CInstanceClientConfig
{
public:
	char pad_0000[16]; //0x0000
	CDBTable* iCDBTable; //0x0010
	char pad_0014[4]; //0x0014
	uintptr_t CharID; //0x0018
	char pad_001C[4]; //0x001C
	uintptr_t N00007C86; //0x0020
	char pad_0024[4]; //0x0024
}; //Size: 0x0028

#endif