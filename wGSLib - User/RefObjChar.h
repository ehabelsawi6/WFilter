#ifndef REFOBJCHAR_H
#define REFOBJCHAR_H
#include "pch.h"
class RefObjChar
{
public:
	char pad_0000[8]; //0x0000
	uintptr_t RefObjID; //0x0008
	char pad_000C[8]; //0x000C
	char* CodeName128; //0x0014
	char pad_0018[224]; //0x0018
	char* BsrFileName; //0x00F8
	char pad_00FC[592]; //0x00FC
}; //Size: 0x034C


#endif