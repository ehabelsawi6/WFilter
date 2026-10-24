#ifndef CINSTANCECHARTRIJOB_H
#define CINSTANCECHARTRIJOB_H
#include "pch.h"
class CInstanceCharTrijob
{
public:
	char pad_0000[16]; //0x0000
	class CDBTable* CDBTable; //0x0010
	char pad_0014[4]; //0x0014
	uintptr_t CharID; //0x0018
	char pad_001C[20]; //0x001C
}; //Size: 0x0030

#endif