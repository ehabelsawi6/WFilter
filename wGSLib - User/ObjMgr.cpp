#include "pch.h"
#include "ObjMgr.h"
#include "GObjPC.h"
#include "RefDataManager.h"

std::list<CGObjPC*> CObjMgr::s_lstPlayers;
CAutoCriticalSection* CObjMgr::s_playerListACS;

typedef CGObjPC* (__stdcall* fnGetPC)();
typedef void(__stdcall* fnReleasePC)(CGObjPC** ppPC);

fnGetPC pfnGetPC;
fnReleasePC pfnReturnPC;

CGObjPC* __stdcall OnGetPC();
void __stdcall OnReturnPC(CGObjPC** ppPC);


bool CObjMgr::Initialize()
{
	s_playerListACS = new CAutoCriticalSection();

	pfnGetPC = reinterpret_cast<fnGetPC>(0x004DE260);
	pfnReturnPC = reinterpret_cast<fnReleasePC>(0x004DE2A0);

	CGObjPC::SetupFunctionPointers();

	DetourTransactionBegin();
	DetourAttach(&(PVOID&)pfnGetPC, OnGetPC);
	DetourAttach(&(PVOID&)pfnReturnPC, OnReturnPC);
	DetourTransactionCommit();
	return true;
}

__OBJ_MGR_PLAYER_LST& CObjMgr::GetPlayers() { return s_lstPlayers; }
CAutoCriticalSection* CObjMgr::GetPlayerListACS() { return s_playerListACS; }


CGObjPC* CObjMgr::GetPlayerByDBID(int nID)
{
	CGObjPC* pResult = NULL;

	s_playerListACS->Enter();

	__OBJ_MGR_PLAYER_LST_IT itCur = s_lstPlayers.begin();
	__OBJ_MGR_PLAYER_LST_IT itEnd = s_lstPlayers.end();

	for (; itCur != itEnd; itCur++)
	{
		CGObjPC* pPC = *itCur;
		if (pPC->GetInstance() == NULL)
			continue;

		if (pPC->GetDBID() == nID)
		{
			pResult = pPC;
			break;
		}
	}

	s_playerListACS->Leave();

	return pResult;
}

CGObjPC* __stdcall OnGetPC()
{
	CAutoCriticalSection* pACS = CObjMgr::GetPlayerListACS();
	__OBJ_MGR_PLAYER_LST& lst = CObjMgr::GetPlayers();

	pACS->Enter();
	CGObjPC* pPC = pfnGetPC();
	lst.push_back(pPC);
	pACS->Leave();

	return pPC;
}

void __stdcall OnReturnPC(CGObjPC** ppPC)
{
	CAutoCriticalSection* pACS = CObjMgr::GetPlayerListACS();
	__OBJ_MGR_PLAYER_LST& lst = CObjMgr::GetPlayers();

	pACS->Enter();
	lst.remove(*ppPC);
	pACS->Leave();

	pfnReturnPC(ppPC);
}


void CObjMgr::SpawnMonster(SPosInfoForMobSpawn* pPosInfo, BYTE btType, float fltRange, DWORD dwRefObjID, SWorldID worldID)
{
	const DWORD dwGameWorldMgr = 0x00D0B380;
	const DWORD dwFuncCallAddr = 0x005F6EB0;

	CRefObj* pRefObj = CRefDataManager::GetRefObjByID(dwRefObjID);

	const float fltArgZero = 0.0f;

	__asm push 1;								//can be 1, OK
	__asm push fltArgZero;						//can be 0.0flt, OK
	__asm push 0;								//can be 0, OK
	__asm push 0;								//can be 0, OK
	__asm push btType;							//mob type (general unique etc etc), OK
	__asm push fltRange;						//prolly range
	__asm push fltArgZero;
	__asm push 0;
	__asm push 0;
	__asm push pRefObj;							//ref obj ptr, OK
	__asm push 0;
	__asm push worldID;
	__asm push dwGameWorldMgr;					//CGameWorldMgr, OK
	__asm mov eax, pPosInfo;				//ref to nav cell, OK?
	__asm call dwFuncCallAddr;
}

void CObjMgr::SpawnMonsterNearPlayer(CGObjPC* pPC, BYTE btType, float fltRange, DWORD dwRefObjID)
{
	SWorldID sWorldID;
	pPC->GetWorldID(sWorldID);

	SPosInfoForMobSpawn* pPcPosInfo = reinterpret_cast<SPosInfoForMobSpawn*>(
		(DWORD)(pPC)+0x7C
		);

	//SPosInfoForMobSpawn* pos = new SPosInfoForMobSpawn(24744, 993.000f, -8.497, 1396.000);

	SpawnMonster(pPcPosInfo, btType, fltRange, dwRefObjID, sWorldID);
	//---
}

void CObjMgr::EngageBuffSkill(CGObjPC* pPC,  const char* szSkillCodeName128)
{
	const DWORD dwCGObjPC_EngageBuffSkill_Addr = 0x004F1800;
	const double dblUnk1 = 1.00;
	const int nUnk2 = 1;

	__asm push nUnk2;
	__asm push szSkillCodeName128;
	__asm fld dblUnk1;
	__asm mov ecx, pPC;
	__asm call dwCGObjPC_EngageBuffSkill_Addr;
}

void CObjMgr::EngageBuffSkill1(CGObjPC* pPC, int SilkID, int Time)
{
	__asm
	{
		mov eax, 0x49A390
		mov esi, pPC
		push 0
		push 0
		push 0
		push 0
		push 0
		push 0
		push 0
		push 0
		push Time
		push[SilkID]
		push 0
		call eax
	}
}