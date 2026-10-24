#pragma once
#include "pch.h"
#include "AutoCriticalSection.h"
#include "GObjPC.h"

#define __OBJ_MGR_PLAYER_LST	std::list<CGObjPC*>
#define __OBJ_MGR_PLAYER_LST_IT std::list<CGObjPC*>::iterator

class CRTNavCellQuad;
class CRefObj;

#pragma pack(push, 1)
struct SPosInfoForMobSpawn
{
	void* ptr;
	DWORD dwUnk1; //0
	DWORD dwRegionID;
	float fltPosX;
	float fltPosY;
	float fltPosZ;

	SPosInfoForMobSpawn(DWORD dwRegionID, float fltPosX, float fltPosY, float fltPosZ)
	{
		this->ptr = 0;
		this->dwUnk1 = 0;
		this->dwRegionID = dwRegionID;
		this->fltPosX = fltPosX;
		this->fltPosY = fltPosY;
		this->fltPosZ = fltPosZ;
	}
};
#pragma pack(pop)

class CObjMgr
{
public:
	static bool Initialize();
	static __OBJ_MGR_PLAYER_LST& GetPlayers();

	static CAutoCriticalSection* GetPlayerListACS();
	static CGObjPC* GetPlayerByDBID(int nID);

	static void SpawnMonster(SPosInfoForMobSpawn* pPosInfo, BYTE btType, float fltRange, DWORD dwRefObjID, SWorldID worldID);
	static void SpawnMonsterNearPlayer(CGObjPC* pPC, BYTE btType, float fltRange, DWORD dwRefObjID);
	static void EngageBuffSkill(CGObjPC* pPC, const char* szSkillCodeName128);
	static void EngageBuffSkill1(CGObjPC* pPC, int SilkID, int Time = 180);
private:
	static __OBJ_MGR_PLAYER_LST s_lstPlayers;
	static CAutoCriticalSection* s_playerListACS;
};