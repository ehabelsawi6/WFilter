#ifndef WMGR_H
#define WMGR_H
#include "pch.h"
class WMGR
{
public:
	char pad_0000[16]; //0x0000
	USHORT CharId;
	class CGObjPC* CGObjPC; //0x0014
}; //Size: 0x0018

#endif