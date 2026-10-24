#ifndef CINSTANCEPC_H
#define CINSTANCEPC_H
#include "pch.h"
#include "RefObjChar.h"
#include "CDBTable.h"

class CInstancePC
{
public:
	char pad_0000[16]; //0x0000
	class CDBTable* iDbTable; //0x0010
	char pad_0014[4]; //0x0014
	class RefObjChar* iRefObjChar; //0x0018
	char pad_001C[4]; //0x001C
	uintptr_t CharID; //0x0020
	char pad_0024[4]; //0x0024
	uintptr_t ModelID; //0x0028
	char pad_002C[4]; //0x002C
	char CharName16[16]; //0x30
	char pad_0040[4]; //0x0040
	uintptr_t Unk; //0x0044
	char pad_0048[24]; //0x0048
	uintptr_t Unk1; //0x0060
	char pad_0064[4]; //0x0064
	uintptr_t ExpOffset; //0x0068
	char pad_006C[8]; //0x006C
	USHORT Strength; //0x0074
	USHORT Intelect; //0x0076
	USHORT Gold; //0x0078
	uintptr_t RemainSkillPoint; //0x0080
	uintptr_t RemainStatPoint; //0x0084
	char pad_0088[4]; //0x0088
	uintptr_t CurHealth; //0x008C
	uintptr_t CurMana; //0x0090
	uintptr_t RegionID; //0x0094
	float PosX; //0x0098
	float PosY; //0x009C
	float PosZ; //0x00A0
	char pad_00A4[40]; //0x00A4
	uintptr_t UnkRegionID1; //0x00CC
	float UnkPosX1; //0x00D0
	float UnkPosY1; //0x00D4
	float UnkPosZ1; //0x00D8
	uintptr_t DeathRegionId; //0x00DC
	float DeathRegionPosX; //0x00E0
	float DeathRegionPosY; //0x00E4
	float DeathRegionPosZ; //0x00E8
	char pad_00EC[12]; //0x00EC
}; //Size: 0x00F8


#endif