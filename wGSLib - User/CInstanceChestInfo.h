#ifndef CINSTANCECHESTINFO_H
#define CINSTANCECHESTINFO_H
#include "pch.h"
#include "CDBTable.h"
class CCInstanceChestInfo
{
public:
	char pad_0000[16]; //0x0000
	CDBTable* CDBTable; //0x0010
	char pad_0014[3632]; //0x0014
}; //Size: 0x0E44

#endif