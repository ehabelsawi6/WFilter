#include "pch.h"
#include "StaticPatches.h"

#include "ConfigMgr.h"
#include "DbMgr.h"
#include "MemoryUtility.h"
#include "IGObj.h"

class CGObj;
class CInstance;

const char* szUnknown = "Unknown";

//Cap
#define CHAR_MAX_LEVEL_OFFSET											0x004E52C9
#define PET_MAX_LEVEL_OFFSET											0x004D641E
#define CH_MASTERY_MAX_LEVEL_OFFSET										0x0059C5E7
#define EU_MASTERY_MAX_LEVEL_OFFSET										0x00B46130

//Rates
#define RATE_LIMIT_BYPASS_INDIVIDUAL_OFFSET								0x0042714E
#define RATE_LIMIT_BYPASS_PARTY_OFFSET									0x004271F7
#define RATE_LIMIT_BYPASS_DROP_ITEM_RATIO_OFFSET						0x004272A2
#define RATE_LIMIT_BYPASS_DROP_GOLD_RATIO_OFFSET						0x0042734B

//Null instance fix
#define GOBJ_GET_CHAR_NAME_FUNC_OFFSET									0x004A66D0
#define GOBJ_GET_NICK_NAME_FUNC_OFFSET									0x004DDC50

//Green book
#define GREEN_BOOK_NOP_OFFSET_1											0x004142E2
#define GREEN_BOOK_NOP_OFFSET_2											0x0041474D

//Quest
#define QUEST_RAISE_EVENT_DISABLE_MSG_OFFSET							0x005805C8

//Flag world
#define FLAG_WORLD_KILL_REWARD_CODENAME_OFFSET							0x005F19AA
#define FLAG_WORLD_KILL_REWARD_COUNT_OFFSET								0x005F1998
#define FLAG_WORLD_WIN_REWARD_CODENAME_OFFSET							0x00646D43
#define FLAG_WORLD_WIN_REWARD_COUNT_OFFSET								0x00646D41

//Arena
#define BATTLE_ARENA_REWARD_CODENAME_OFFSET								0x006691C7
#define BATTLE_ARENA_GUILD_AND_JOB_WIN_REWARD_COUNT_OFFSET				0x0066915C
#define BATTLE_ARENA_GUILD_AND_JOB_LOSE_REWARD_COUNT_OFFSET				0x00669177
#define BATTLE_ARENA_PARTY_AND_RANDOM_WIN_REWARD_COUNT_OFFSET			0x00669163
#define BATTLE_ARENA_PARTY_AND_RANDOM_LOSE_REWARD_COUNT_OFFSET			0x0066917E

//PK
#define PK_MIN_LEVEL_OFFSET												0x005295DB
#define PK_MIN_LEVEL_FOR_ITEM_DROP_OFFSET								0x004E6A34


//Job
#define JOB_MAX_LEVEL_OFFSET											0x0060DE6C
#define JOB_DISABLE_JOB_NPC_SPAWN_OFFSET								0x0060C4AB
#define JOB_TEMPLE_ENTRY_BUTTON_LEVEL_OFFSET							0x0051AE72
#define JOB_TEMPLE_AP_LEVEL_OFFSET										0x0051ABE9

//Guild
#define GUILD_UNION_MAX_CHAT_PLAYERS_OFFSET								0x005C4B46
#define GUILD_LEVEL_REQ_FOR_MERCENARY_SPAWN_OFFSET						0x004FD02B
#define GUILD_ALLOW_NON_GM_SPAWN_MERCENARIES_OFFSET						0x004FD045
#define GUILD_DISABLE_GRANT_NAME_RESTRICTION_OFFSET_1					0x00517C20
#define GUILD_DISABLE_GRANT_NAME_RESTRICTION_OFFSET_2					0x005C75AB

//Alchemy
#define ALCHEMY_MIN_ITEM_LEVEL_FOR_ASTRAL_TAKING_EFFECT_OFFSET			0x00506D94
#define ALCHEMY_ITEM_LEVEL_FOR_ASTRAL_RECOVERY_OFFSET					0x00506DD3
#define ALCHEMY_DROP_ITEM_MAX_PLUS_CHECK_OFFSET						    0x004AA74C

//Academy
#define ACADEMY_CREATION_LEVEL_REQUIREMENT_OFFSET						0x004E46C5
#define ACADEMY_CREATION_GOLD_REQUIREMENT_OFFSET						0x004E46E2
#define ACADEMY_MAX_SUB_MENTOR_COUNT_OFFSET								0x005E4457
#define ACADEMY_MAX_APPRENTICES_COUNT_OFFSET							0x005E44D7
#define ACADEMY_SUB_MENTOR_LEVEL_REQUIREMENT_OFFSET_1					0x005192CF			
#define ACADEMY_APPRENTICE_LEVEL_REQUIREMENT_OFFSET_1					0x00519304
#define ACADEMY_SUB_MENTOR_LEVEL_REQUIREMENT_OFFSET_2					0x005196CE
#define ACADEMY_APPRENTICE_LEVEL_REQUIREMENT_OFFSET_2					0x00519713
#define ACADEMY_SUB_MENTOR_LEVEL_REQUIREMENT_OFFSET_3					0x00519885
#define ACADEMY_APPRENTICE_LEVEL_REQUIREMENT_OFFSET_3					0x00519895
#define ACADEMY_DISBAND_PENALTY_OFFSET									0x005DD36B

//Monster
#define MONSTER_GIANT_SPAWN_DISABLE_PATCH_OFFSET_1						0x0056093C
#define MONSTER_GIANT_SPAWN_DISABLE_PATCH_OFFSET_2						0x0056093F

//NPC
#define NPC_SET_AVAILABLE_INTERACTIONS_FUNC_OFFSET						0x004C6350
#define NPC_ADD_AVAILABLE_INTERACTION_FUNC_OFFSET						0x004C3F50
#define NPC_MAX_LEVEL_TO_TELEPORT_AT_DEATH_POS__OR_RECALL_POINT_OFFSET	0x004F36F4

//Misc, Client side for ressurect at same pos offset = 0x00797E21
#define MISC_MAX_LEVEL_FOR_RESSURECT_AT_SAME_POS_OFFSET					0x00510180

//Other
#define MSG_WRITE_OUT_FUNC_OFFSET										0x00936640

//Pet
#define GRAB_PET_INVENTORY_SIZE_OFFSET									0x004D6F9F
#define GRAB_PET_PAGE_FIX_OFFSET										0x004FBD8A

//Inline hooks, kinda mess to use dwords here but ok for now
const DWORD ORIG_UNIQUE_ENTERED_MSG_CALL_ADDR = 0x00936640;
const DWORD ORIG_UNIQUE_KILLED_MSG_CALL_ADDR = 0x00936640;
const DWORD UNIQUE_ENTERED_MSG_HOOK_JUMPBACK = 0x00414DB5;
const DWORD UNIQUE_KILLED_MSG_HOOK_JUMPBACK = 0x00414BAE;
const DWORD UNIQUE_ENTERED_MSG_HOOK_ADDR = 0x00414DB0;
const DWORD UNIQUE_KILLED_MSG_HOOK_ADDR = 0x00414BA9;


typedef int (WINAPI* fnMessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
typedef int (WINAPI* fnMessageBoxW)(HWND hWnd, LPCSTR lpText, LPCWSTR lpCaption, UINT uType);
typedef const char* (__thiscall* fnGetCharName)(CGObj* pObj);
typedef const char* (__thiscall* fnGetNickName)(CGObj* pObj);
typedef bool(__thiscall* fnCGObjNPCNPC_SetAvailableInteractions)(IGObj*, int a2, int a3, int a4, int a5, int a6);
typedef void* (__thiscall* fnCGObjNPCNPC_AddAvailableInteraction)(IGObj*, int nInteractionID);

void __stdcall LogUniqueMonsterEntered(char* szUniqueName);
void __stdcall LogUniqueMonsterKilled(char* szUniqueName, char* szKillerName);

//__declspec(naked) void
void MyOnUniqueEnteredMsg();
void MyOnUniqueKilledMsg();

//Need to obtain addrs by GetProcAddress for those.
fnMessageBoxA pfnOrigMessageBoxA = NULL;
fnMessageBoxW pfnOrigMessageBoxW = NULL;
fnGetCharName pfnOrigGetCharName = NULL;
fnGetNickName pfnOrigGetNickName = NULL;

//This are static.
fnCGObjNPCNPC_SetAvailableInteractions pfnOrigCGObjNPCNPC_SetAvailableInteractions =
reinterpret_cast<fnCGObjNPCNPC_SetAvailableInteractions>(NPC_SET_AVAILABLE_INTERACTIONS_FUNC_OFFSET);

fnCGObjNPCNPC_AddAvailableInteraction pfnOrigCGObjNPCNPC_AddAvailableInteraction =
reinterpret_cast<fnCGObjNPCNPC_AddAvailableInteraction>(NPC_ADD_AVAILABLE_INTERACTION_FUNC_OFFSET);

CInstance* GetGObjInstance(CGObj* pObj)
{
	return MEMUTIL_READ_BY_PTR_OFFSET(pObj, 0x34, CInstance*);
}


int WINAPI MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	//printf("MessageBoxA %s, [Text] %s\n", lpCaption, lpText);
	//printf("MessageBoxA [Text] %s\n", lpText);
	return 1;
}

int WINAPI MyMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	//wprintf(L"MessageBoxW %s, [Text] %s\n", lpCaption, lpText);
	//wprintf(L"MessageBoxW [Text] %s\n", lpText);
	return 1;
}

const char* __fastcall MyGetCharName(CGObj* pObj, LPVOID /* dummy edx */)
{
	if (pObj == NULL)
		return szUnknown;

	if (GetGObjInstance(pObj) == NULL)
		return szUnknown;

	return pfnOrigGetCharName(pObj);
}

const char* __fastcall MyGetNickName(CGObj* pObj, LPVOID /* dummy edx */)
{
	if (pObj == NULL)
		return szUnknown;

	if (GetGObjInstance(pObj) == NULL)
		return szUnknown;

	return pfnOrigGetNickName(pObj);
}
//
//bool __fastcall MyCGObjNPCNPC_SetAvailableInteractions(IGObj* pObj, void* /* dummy edx */, int a2, int a3, int a4, int a5, int a6)
//{
//	bool bOrigResult = pfnOrigCGObjNPCNPC_SetAvailableInteractions(pObj, a2, a3, a4, a5, a6);
//
//	const char* szCodeName128 = pObj->GetCodeName();
//	//printf("[%s] NPC CodeName128 = [%s], a2 [%d] a3 [%d] a4 [%d] a5 [%d] a6 [%d]\n", __FUNCTION__, szCodeName128, a2, a3, a4, a5, a6);
//
//	__DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST lst = CConfigMgr::GetCustomNpcInteractions();
//
//	__DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST_IT it = lst.begin();
//	__DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST_IT end = lst.end();
//
//	for (; it != end; it++)
//	{
//		SCustomNpcInteractionDbRecord record = (SCustomNpcInteractionDbRecord)(*it);
//		if (strcmp(record.szCodeName128, szCodeName128) == 0)
//		{
//			//DWORD res = reinterpret_cast<int(__thiscall*)(IGObj*, int)>(0x4C3F50)(pObj, record.nInteractionID);
//			void* res = pfnOrigCGObjNPCNPC_AddAvailableInteraction(pObj, record.nInteractionID);
//			printf("[%s] Added custom interaction mode for npc [%s] interaction id [%d] result 0x%x.\n", __FUNCTION__,
//				szCodeName128, record.nInteractionID, res
//			);
//		}
//	}
//
//	return bOrigResult;
//}

void __stdcall LogUniqueMonsterEntered(char* szUniqueName)
{
	//printf("entered unique name = %s\n", szUniqueName);
	CDbMgr::GetMiscDbSet()->CallUniqueEnteredSP(szUniqueName);
}

void __stdcall LogUniqueMonsterKilled(char* szUniqueName, char* szKillerName)
{
	//printf("unique monster killed, unique = %s, killer = %s\n", szUniqueName, szKillerName);
	CDbMgr::GetMiscDbSet()->CallUniqueKilledSP(szUniqueName, szKillerName);
}

__declspec(naked) void MyOnUniqueEnteredMsg()
{
	__asm push eax;
	__asm call LogUniqueMonsterEntered;
	__asm call ORIG_UNIQUE_ENTERED_MSG_CALL_ADDR;
	__asm jmp UNIQUE_ENTERED_MSG_HOOK_JUMPBACK;
}

__declspec(naked) void MyOnUniqueKilledMsg()
{
	__asm push ecx;
	__asm push eax;
	__asm call LogUniqueMonsterKilled;
	__asm call ORIG_UNIQUE_KILLED_MSG_CALL_ADDR;
	__asm jmp UNIQUE_KILLED_MSG_HOOK_JUMPBACK;
}

bool CStaticPatches::Apply()
{
	SGameServerConfig* pstGameServerConfig = CConfigMgr::GetGameServerConfig();
	SFlagWorldCustomConfig* pstFlagWorldConfig = CConfigMgr::GetFlagWorldConfig();
	SBattleArenaCustomConfig* pstBattleArenaConfig = CConfigMgr::GetBattleArenaConfig();
	SPKCustomConfig* pstPKConfig = CConfigMgr::GetPKConfig();
	SJobCustomConfig* pstJobConfig = CConfigMgr::GetJobConfig();
	//SGuildCustomConfig* pstGuildConfig = CConfigMgr::GetGuildConfig();
	//SAcademyCustomConfig* pstAcademyConfig = CConfigMgr::GetAcademyConfig();
	//SMonsterCustomConfig* pstMonsterConfig = CConfigMgr::GetMonsterConfig();
	//SNPCConfig* pstNpcConfig = CConfigMgr::GetNpcConfig();
	//SMiscConfig* pstMiscConfig = CConfigMgr::GetMiscConfig();
	SAlchemyCustomConfig* pstAlchemyConfig = CConfigMgr::GetAlchemyConfig();
	SPetConfig* pstPetConfig = CConfigMgr::GetPetConfig();

	LPCSTR lpszCodename = NULL;

	//==============================================================================================================================

	//Basic gameserver cfg
	MEMUTIL_WRITE_VALUE(BYTE, CHAR_MAX_LEVEL_OFFSET, pstGameServerConfig->btMaxCharLevel);
	MEMUTIL_WRITE_VALUE(BYTE, PET_MAX_LEVEL_OFFSET, pstGameServerConfig->btMaxPetLevel);
	MEMUTIL_WRITE_VALUE(DWORD, CH_MASTERY_MAX_LEVEL_OFFSET, pstGameServerConfig->dwMaxChinaMasteryLevel);

	LDOUBLE dblTmpMaxEuroMastery = static_cast<LDOUBLE>(pstGameServerConfig->dwMaxEuropeMasteryLevel);
	MEMUTIL_WRITE_VALUE(LDOUBLE, EU_MASTERY_MAX_LEVEL_OFFSET, dblTmpMaxEuroMastery);

	if (pstGameServerConfig->bBypassRatesLimit)
	{
		BYTE btPayload = 0x42;
		MEMUTIL_WRITE_VALUE(BYTE, RATE_LIMIT_BYPASS_INDIVIDUAL_OFFSET, btPayload);
		MEMUTIL_WRITE_VALUE(BYTE, RATE_LIMIT_BYPASS_PARTY_OFFSET, btPayload);
		MEMUTIL_WRITE_VALUE(BYTE, RATE_LIMIT_BYPASS_DROP_ITEM_RATIO_OFFSET, btPayload);
		MEMUTIL_WRITE_VALUE(BYTE, RATE_LIMIT_BYPASS_DROP_GOLD_RATIO_OFFSET, btPayload);
	}

	if (pstGameServerConfig->bEnableNullInstanceFix)
	{
		pfnOrigGetCharName = reinterpret_cast<fnGetCharName>(GOBJ_GET_CHAR_NAME_FUNC_OFFSET);
		pfnOrigGetNickName = reinterpret_cast<fnGetNickName>(GOBJ_GET_NICK_NAME_FUNC_OFFSET);

		DetourTransactionBegin();
		DetourAttach(&(PVOID&)pfnOrigGetCharName, MyGetCharName);
		DetourAttach(&(PVOID&)pfnOrigGetNickName, MyGetNickName);
		DetourTransactionCommit();
	}

	if (pstGameServerConfig->bDisableGreenBook)
	{
		MEMUTIL_NOP(GREEN_BOOK_NOP_OFFSET_1, 8);
		MEMUTIL_NOP(GREEN_BOOK_NOP_OFFSET_2, 5);
	}

	if (pstGameServerConfig->bRedirectMsgBoxes)
	{
		HMODULE hUser32 = GetModuleHandleA("User32.dll");
		pfnOrigMessageBoxA = reinterpret_cast<fnMessageBoxA>(GetProcAddress(hUser32, "MessageBoxA"));
		pfnOrigMessageBoxW = reinterpret_cast<fnMessageBoxW>(GetProcAddress(hUser32, "MessageBoxW"));

		DetourTransactionBegin();
		DetourAttach(&(PVOID&)pfnOrigMessageBoxA, MyMessageBoxA);
		DetourAttach(&(PVOID&)pfnOrigMessageBoxW, MyMessageBoxW);
		DetourTransactionCommit();
	}

	if (pstGameServerConfig->bDisableQuestRaiseEventMsg)
	{
		MEMUTIL_NOP(QUEST_RAISE_EVENT_DISABLE_MSG_OFFSET, 19);
	}


	//==============================================================================================================================

	//CTF - Kill reward
	lpszCodename = static_cast<LPCSTR>(pstFlagWorldConfig->strFlagWorldKillRewardCodename.c_str());
	MEMUTIL_WRITE_VALUE(LPCSTR, FLAG_WORLD_KILL_REWARD_CODENAME_OFFSET, lpszCodename);
	MEMUTIL_WRITE_VALUE(BYTE, FLAG_WORLD_KILL_REWARD_COUNT_OFFSET, pstFlagWorldConfig->btFlagWorldKillRewardCount);


	//CTF - Win reward
	lpszCodename = static_cast<LPCSTR>(pstFlagWorldConfig->strFlagWorldWinRewardCodename.c_str());
	MEMUTIL_WRITE_VALUE(LPCSTR, FLAG_WORLD_WIN_REWARD_CODENAME_OFFSET, lpszCodename);
	MEMUTIL_WRITE_VALUE(BYTE, FLAG_WORLD_WIN_REWARD_COUNT_OFFSET, pstFlagWorldConfig->btFlagWorldWinRewardCount);

	//==============================================================================================================================

	//BattleArena - reward codename
	lpszCodename = static_cast<LPCSTR>(pstBattleArenaConfig->strBattleArenaRewardCodename.c_str());
	MEMUTIL_WRITE_VALUE(LPCSTR, BATTLE_ARENA_REWARD_CODENAME_OFFSET, lpszCodename);

	//BattleArena - Guild and job win reward count
	MEMUTIL_WRITE_VALUE(BYTE, BATTLE_ARENA_GUILD_AND_JOB_WIN_REWARD_COUNT_OFFSET, pstBattleArenaConfig->btBattleArenaGuildAndJobWinRewardCount);

	//BattleArena - Guild and job lose reward count
	MEMUTIL_WRITE_VALUE(BYTE, BATTLE_ARENA_GUILD_AND_JOB_LOSE_REWARD_COUNT_OFFSET, pstBattleArenaConfig->btBattleArenaGuildAndJobLoseRewardCount);

	//BattleArena - Party and random win reward count
	MEMUTIL_WRITE_VALUE(BYTE, BATTLE_ARENA_PARTY_AND_RANDOM_WIN_REWARD_COUNT_OFFSET, pstBattleArenaConfig->btBattleArenaPartyAndRandomWinRewardCount);

	//BattleArena - Party and random lose reward count
	MEMUTIL_WRITE_VALUE(BYTE, BATTLE_ARENA_PARTY_AND_RANDOM_LOSE_REWARD_COUNT_OFFSET, pstBattleArenaConfig->btBattleArenaPartyAndRandomLoseRewardCount);

	//==============================================================================================================================
	//anoha

	/*BYTE lvlPk = 140;
	MEMUTIL_WRITE_VALUE(BYTE, PK_MIN_LEVEL_OFFSET, lvlPk);*/
	//PK
	MEMUTIL_WRITE_VALUE(BYTE, PK_MIN_LEVEL_OFFSET, pstPKConfig->btMinLevel);
//	MEMUTIL_WRITE_VALUE(BYTE, PK_MIN_LEVEL_FOR_ITEM_DROP_OFFSET, pstPKConfig->btMinLevelForItemDrop);

	//==============================================================================================================================

	//Job
//	MEMUTIL_WRITE_VALUE(BYTE, JOB_MAX_LEVEL_OFFSET, pstJobConfig->btMaxLevel);

	//Job - temple access
//	MEMUTIL_WRITE_VALUE(BYTE, JOB_TEMPLE_ENTRY_BUTTON_LEVEL_OFFSET, pstJobConfig->btJobCaveApLevel);
//	MEMUTIL_WRITE_VALUE(BYTE, JOB_TEMPLE_AP_LEVEL_OFFSET, pstJobConfig->btJobCaveApLevel);

	if (pstJobConfig->bDisableJobNpcSpawn)
	{
		//xor eax, eax
		char payload[2] = { 0x33, 0xC0 };
		MEMUTIL_WRITE_POINTER(JOB_DISABLE_JOB_NPC_SPAWN_OFFSET, &payload, sizeof(payload));
	}

	//==============================================================================================================================

	//Guild
//	MEMUTIL_WRITE_VALUE(BYTE, GUILD_UNION_MAX_CHAT_PLAYERS_OFFSET, pstGuildConfig->btMaxUnionChatPlayers);
//	MEMUTIL_WRITE_VALUE(BYTE, GUILD_LEVEL_REQ_FOR_MERCENARY_SPAWN_OFFSET, pstGuildConfig->btMinGuildLevelForMercenarySpawn);

	//if (pstGuildConfig->bAllowNonGmMercenarySpawn)
	//{
	//	//short jmp, skip check if summoner is guild master
	//	BYTE btInstruction = 0xEB;
	//	MEMUTIL_WRITE_VALUE(BYTE, GUILD_ALLOW_NON_GM_SPAWN_MERCENARIES_OFFSET, btInstruction);
	//}

	//if (pstGuildConfig->bDisableGrantNameRestriction)
	//{
	//	//Short jmp, skip check if guild level is >= 4 and the player is guild master
	//	BYTE btInstruction = 0xEB;
	//	MEMUTIL_WRITE_VALUE(BYTE, GUILD_DISABLE_GRANT_NAME_RESTRICTION_OFFSET_1, btInstruction);
	//	MEMUTIL_WRITE_VALUE(BYTE, GUILD_DISABLE_GRANT_NAME_RESTRICTION_OFFSET_2, btInstruction);
	//}


	//==============================================================================================================================

	//Alchemy
	MEMUTIL_WRITE_VALUE(BYTE, ALCHEMY_MIN_ITEM_LEVEL_FOR_ASTRAL_TAKING_EFFECT_OFFSET, pstAlchemyConfig->btMinItemLevelForAstralToTakeEffect);
	MEMUTIL_WRITE_VALUE(BYTE, ALCHEMY_ITEM_LEVEL_FOR_ASTRAL_RECOVERY_OFFSET, pstAlchemyConfig->btItemLevelForAstralRecovery);

	//if (pstAlchemyConfig->btMaxItemPlusDropCheck)
	//{
	//	void* addr = reinterpret_cast<void*>(ALCHEMY_DROP_ITEM_MAX_PLUS_CHECK_OFFSET);
	//	CMemoryUtility::UnProtect(addr, 1);
	//	*(BYTE*)(ALCHEMY_DROP_ITEM_MAX_PLUS_CHECK_OFFSET) = MEMUTIL_ASM_OPCODE_SHORT_JUMP;
	//	CMemoryUtility::ReProtect();
	//}
	//==============================================================================================================================

	//Academy
	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_CREATION_LEVEL_REQUIREMENT_OFFSET, pstAcademyConfig->btCreationLevelRequirement);
	//MEMUTIL_WRITE_VALUE(DWORD, ACADEMY_CREATION_GOLD_REQUIREMENT_OFFSET, pstAcademyConfig->dwCreationGoldRequirement);
	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_MAX_SUB_MENTOR_COUNT_OFFSET, pstAcademyConfig->btMaxSubMentors);
	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_MAX_APPRENTICES_COUNT_OFFSET, pstAcademyConfig->btMaxApprentices);

	//Two first level values need to be decreased by 1, this is how it is at GS (see IDA).
	//BYTE btTmpLevel;

	//btTmpLevel = pstAcademyConfig->btSubMentorLevelRequirement - 1;
	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_SUB_MENTOR_LEVEL_REQUIREMENT_OFFSET_1, btTmpLevel);
	//btTmpLevel = pstAcademyConfig->btApprenticeLevelRequirement - 1;
	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_APPRENTICE_LEVEL_REQUIREMENT_OFFSET_1, btTmpLevel);

	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_SUB_MENTOR_LEVEL_REQUIREMENT_OFFSET_2, pstAcademyConfig->btSubMentorLevelRequirement);
	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_APPRENTICE_LEVEL_REQUIREMENT_OFFSET_2, pstAcademyConfig->btApprenticeLevelRequirement);
	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_SUB_MENTOR_LEVEL_REQUIREMENT_OFFSET_3, pstAcademyConfig->btSubMentorLevelRequirement);
	//MEMUTIL_WRITE_VALUE(BYTE, ACADEMY_APPRENTICE_LEVEL_REQUIREMENT_OFFSET_3, pstAcademyConfig->btApprenticeLevelRequirement);

	//MEMUTIL_WRITE_VALUE(DWORD, ACADEMY_DISBAND_PENALTY_OFFSET, pstAcademyConfig->dwDisbandPenaltySeconds);

	//==============================================================================================================================
	//Monster

	//if (pstMonsterConfig->bDisableGiantSpawn)
	//{
	//	//Monster type
	//	BYTE btPayload1 = 0xF0;
	//	BYTE btPayload2 = 0x00;

	//	MEMUTIL_WRITE_VALUE(BYTE, MONSTER_GIANT_SPAWN_DISABLE_PATCH_OFFSET_1, btPayload1);
	//	MEMUTIL_WRITE_VALUE(BYTE, MONSTER_GIANT_SPAWN_DISABLE_PATCH_OFFSET_2, btPayload2);
	//}

	//if (pstMonsterConfig->bEnableUniqueKillHook)
	//{
	//	MEMUTIL_SETUP_HOOK(E_MEMUTUL_HOOK_TYPE::LongJump, (uintptr_t)UNIQUE_ENTERED_MSG_HOOK_ADDR, (uintptr_t)&MyOnUniqueEnteredMsg);
	//	MEMUTIL_SETUP_HOOK(E_MEMUTUL_HOOK_TYPE::LongJump, (uintptr_t)UNIQUE_KILLED_MSG_HOOK_ADDR, (uintptr_t)&MyOnUniqueKilledMsg);
	//}

	//==============================================================================================================================

	//NPC
	//DetourTransactionBegin();
	//DetourAttach(&(PVOID&)pfnOrigCGObjNPCNPC_SetAvailableInteractions, MyCGObjNPCNPC_SetAvailableInteractions);
	//DetourTransactionCommit();

	//MEMUTIL_WRITE_VALUE(BYTE, NPC_MAX_LEVEL_TO_TELEPORT_AT_DEATH_POS__OR_RECALL_POINT_OFFSET, pstNpcConfig->btMaxLevelForTeleportAtDeathPosOrRecallPoint);

	////==============================================================================================================================
	////Misc

	//MEMUTIL_WRITE_VALUE(BYTE, MISC_MAX_LEVEL_FOR_RESSURECT_AT_SAME_POS_OFFSET, pstMiscConfig->btMaxLevelForRessurectAtSamePos);

	//==============================================================================================================================
	//Pet

	//Short relative jump, fix.
	BYTE btPayload = 0xEB;
	MEMUTIL_WRITE_VALUE(BYTE, GRAB_PET_PAGE_FIX_OFFSET, btPayload);

	////Jmx uses DWORD for inv size even tho it's actually byte iirc...
	DWORD dwGrabPetInvSize = (DWORD)pstPetConfig->btGrabPetInventorySize;
	MEMUTIL_WRITE_VALUE(DWORD, GRAB_PET_INVENTORY_SIZE_OFFSET, dwGrabPetInvSize);

	return true;
}
