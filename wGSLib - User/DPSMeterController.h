#ifndef GS_DPS_METER_HOOK
#define GS_DPS_METER_HOOK
#include "stdafx.h"
#include "GObjPC.h"
GS_NS_START

class AURefObjCommon
{
public:
	char pad_0000[4]; // vftable
	char pad_0008[4]; // unk

	int ItemID;

	char pad_000C[4]; // unk
	char pad_0010[4]; // str pad for vc17

	std::string CodeName128;

	char pad_002C[84];

	unsigned short TypeID;
	unsigned short unk;

	DWORD unknown1;
	char unknown2;
	unsigned char Rarity;
};
class CInstanceCOS
{
private:
	char _pad_to_dbdata[24];//0x18
	AURefObjCommon* pRefObjCommon;
	char _pad_to_objiddata[12];//0x18
public:
	uint32_t RefObjID;
	uint32_t UniqueID;
	AURefObjCommon* GetObjCommon()
	{
		return this->pRefObjCommon;
	}
};
class CGObjMob
{
private:
	char pad_0000[8]; //0x0000
	uint32_t UniqueID; //0x0008
	char pad_000C[40]; //0x000C
public:
	CInstanceCOS* CInstance; //0x0034
	char pad_0038[7276]; //0x0038
	std::map<int, int> m_AggroMap; //0x1CA4
	uint32_t GetUniqueID()
	{
		return this->UniqueID;
	}
};

class CDpsMeterController
{
public:
	static void Initialize();
	void OnMonsterDeath(CGObjPC* player, CGObjMob* monster);
private:
};
GS_NS_END
#endif