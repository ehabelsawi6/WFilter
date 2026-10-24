#ifndef CGOBJPC_VTABLE_H
#define CGOBJPC_VTABLE_H
#include "pch.h"
#include "IGObj.h"

#pragma pack(push, 4)
class CGObjPC_VTable
{
public:
	IGObj_VTable IGObj;

	//More here
};

#pragma pack(pop)

#endif