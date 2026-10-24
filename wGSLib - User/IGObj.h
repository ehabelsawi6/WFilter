#pragma once
#include "pch.h"
#include "RemodelUtility.h"
#include "Param.h"

struct SPartyInfo;

#pragma pack(push, 1)
struct SWorldID
{
	WORD wLayerID;
	WORD wWorldID;

	SWorldID(WORD wLayerID, WORD wWorldID) : wLayerID(wLayerID), wWorldID(wWorldID)
	{

	}

	SWorldID() : wLayerID(0), wWorldID(0)
	{

	}
};
#pragma pack(pop)

//STeleportPos is same except padding 4
#pragma pack(push, 1)
struct SPosInfo
{
	WORD wRegionID;
	float fltX;
	float fltY;
	float fltZ;

	SPosInfo(WORD wRegionID, float fltX, float fltY, float fltZ) :
		wRegionID(wRegionID), fltX(fltX), fltY(fltY), fltZ(fltZ)
	{

	}

	SPosInfo() : wRegionID(0), fltX(0.0f), fltY(0.0f), fltZ(0.0f)
	{

	}
};
#pragma pack(pop)

#pragma pack(push, 4)
struct STeleportPos
{
	WORD wRegionID;
	float fltX;
	float fltY;
	float fltZ;

	STeleportPos(WORD wRegionID, float fltX, float fltY, float fltZ) :
		wRegionID(wRegionID), fltX(fltX), fltY(fltY), fltZ(fltZ)
	{

	}

	STeleportPos() : wRegionID(0), fltX(0.0f), fltY(0.0f), fltZ(0.0f)
	{

	}

	STeleportPos(SPosInfo pos) : wRegionID(pos.wRegionID), fltX(pos.fltX), fltY(pos.fltY), fltZ(pos.fltZ)
	{

	}
};
#pragma pack(pop)


enum LIFESTATE : UINT8
{
	LIFESTATE_EMBRYO = 0,
	LIFESTATE_ALIVE = 1,
	LIFESTATE_DEAD = 2,
	LIFESTATE_GONE = 3,
};

enum MOTIONSTATE : UINT8
{
	MOTIONSTATE_STAND = 0,
	MOTIONSTATE_SKILL = 1,
	MOTIONSTATE_WALK = 2,
	MOTIONSTATE_RUN = 3,
	MOTIONSTATE_SIT = 4,
	MOTIONSTATE_JUMP = 5,
	MOTIONSTATE_SWIM = 6,
	MOTIONSTATE_RIDE = 7,
	MOTIONSTATE_KNOCKDOWN = 8,
	MOTIONSTATE_STUN = 9,
	MOTIONSTATE_FROZEN = 10,
	MOTIONSTATE_HIT = 11,
	MOTIONSTATE_REQ_HELP = 12,
	MOTIONSTATE_PAO = 13,
	MOTIONSTATE_COUNTERATTACK = 14,
	MOTIONSTATE_SKILL_ACTIONOFF = 15,
	MOTIONSTATE_SKILL_KNOCKBACK = 16,
	MOTIONSTATE_PROTECTIONWALL = 17,
	MOTIONSTATE_CHANGEMOTION = 18,
	MOTIONSTATE_SLEEP = 19,
	MOTIONSTATE_STONE = 20,
};

enum BODYMODE : UINT8
{
	BODYMODE_NORMAL = 0,
	BODYMODE_HWAN = 1,
	BODYMODE_INVICIBLE = 2,
	BODYMODE_INVISIBLE = 3,
	BODYMODE_BERSERKER = 4,
	BODYMODE_GM_INVISIBLE = 5,
	BODYMODE_STEALTH = 6,
	BODYMODE_SKILL_INVISIBLE = 7,
};

enum JOBSTATE : UINT8
{
	JOBSTATE_NONE = 0,
};

enum TELEPORTSTATE : UINT8
{
	TELEPORTSTATE_NONE = 0,
};

enum MONSTERCLASS : UINT8
{
	MONSTERCLASS_NONE = 0,
};

//.rdata:00AE78F4
class IGObj
{
public:
	REMODEL_DECLARE_VIRTUAL_NOIMPL_DCTOR(IGObj);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(DWORD, GetRefObjID() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(DWORD, GetJID() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(DWORD, GetGameID() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(DWORD, GetTypeID() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(SWorldID&, GetWorldID(SWorldID& dwResult) const, dwResult);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsChar() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsPC() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsNPC() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsNPCNPC() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsMonster() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsCOS() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsCart() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsVehicle() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsPet() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsMercenary() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsAttackableCOS() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsStruct() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsItem() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsExpendables() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsContainerItem() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsContainerSummon() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsSpecialty() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsPotion() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsScroll() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsBullet() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsArrow() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsBolt() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsHPPotion() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsMPPotion() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsElixir() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsGold() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsTownPortal() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsEquip() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsWeapon() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsShield() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsAccessory() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsTeleportGate() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsRobe() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsArmor() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsBow() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsCrossBow() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsSummonScroll() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsReinforceRecipe() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsReinforceProbUP() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsFreeBattleEquip() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsQuest_n_EventItem() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsCashItem() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, Unknown1() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanTrade() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanSell() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanBorrow() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanDrop() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanPick() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanRepair() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanRevive() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanUse() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, CanThrow() const, FALSE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(LPCSTR, GetCodeName() const, NULL);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(LPCSTR, GetCharName() const, NULL);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(LPCSTR, GetNickName() const, NULL);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(SPosInfo*, GetPosInfo(SPosInfo&) const, NULL);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(LIFESTATE, GetLifeState() const, LIFESTATE_EMBRYO);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(MOTIONSTATE, GetMotionState() const, MOTIONSTATE_STAND);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BODYMODE, GetBodyMode() const, BODYMODE_NORMAL);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(double, GetParam(GOBJ_PARAM wParamID) const, 0.0f); //max 61 dunno why coz there are assignments with 140 etc
	REMODEL_DECLARE_VIRTUAL_NOIMPL(DWORD, GetHealth() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(DWORD, GetMana() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(DWORD, GetMaxHealth() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(DWORD, GetMaxMana() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, IsTargeting() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(JOBSTATE, GetJobState() const, JOBSTATE_NONE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(TELEPORTSTATE, GetTeleportState() const, TELEPORTSTATE_NONE);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BYTE, GetLevel() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BYTE, GetMaxLevel() const, 0);
	REMODEL_DECLARE_VIRTUAL_NOIMPL(MONSTERCLASS, GetMonsterClass() const, MONSTERCLASS_NONE);
	//.rdata:00AEDEDC                 dd offset ?GetPartyInfo@OK_CGObj@@UAE@XZ ; OK_CGObj::GetPartyInfo(void)
	REMODEL_DECLARE_VIRTUAL_NOIMPL(BOOL, GetPartyInfo(SPartyInfo&) const, NULL);
};


//-------------------------------------------------------
typedef void* (__stdcall* fnIGObj_Ctor)(void* _ptr);

typedef BOOL(__thiscall* fnIsChar)(void* _ecx);
typedef BOOL(__thiscall* fnIsPC)(void* _ecx);
typedef BOOL(__thiscall* fnIsNPC)(void* _ecx);
typedef BOOL(__thiscall* fnIsNPCNPC)(void* _ecx);
typedef BOOL(__thiscall* fnIsMonster)(void* _ecx);
typedef BOOL(__thiscall* fnIsCOS)(void* _ecx);
typedef BOOL(__thiscall* fnIsCart)(void* _ecx);
typedef BOOL(__thiscall* fnIsVehicle)(void* _ecx);
typedef BOOL(__thiscall* fnIsPet)(void* _ecx);
typedef BOOL(__thiscall* fnIsMercenary)(void* _ecx);
typedef BOOL(__thiscall* fnIsAttackableCOS)(void* _ecx);
typedef BOOL(__thiscall* fnIsStruct)(void* _ecx);
typedef BOOL(__thiscall* fnIsItem)(void* _ecx);

typedef BOOL(__thiscall* fnIsExpendables)(void* _ecx);
typedef BOOL(__thiscall* fnIsContainerItem)(void* _ecx);
typedef BOOL(__thiscall* fnIsContainerSummonerItem)(void* _ecx);
typedef BOOL(__thiscall* fnIsSpecialty)(void* _ecx);
typedef BOOL(__thiscall* fnIsPotion)(void* _ecx);
typedef BOOL(__thiscall* fnIsScroll)(void* _ecx);
typedef BOOL(__thiscall* fnIsBullet)(void* _ecx);
typedef BOOL(__thiscall* fnIsArrow)(void* _ecx);
typedef BOOL(__thiscall* fnIsBolt)(void* _ecx);
typedef BOOL(__thiscall* fnIsHPPotion)(void* _ecx);
typedef BOOL(__thiscall* fnIsMPPotion)(void* _ecx);
typedef BOOL(__thiscall* fnIsElixir)(void* _ecx);
typedef BOOL(__thiscall* fnIsGold)(void* _ecx);
typedef BOOL(__thiscall* fnIsTownPortal)(void* _ecx);
typedef BOOL(__thiscall* fnIsEquip)(void* _ecx);
typedef BOOL(__thiscall* fnIsWeapon)(void* _ecx);
typedef BOOL(__thiscall* fnIsShield)(void* _ecx);
typedef BOOL(__thiscall* fnIsAccessory)(void* _ecx);
typedef BOOL(__thiscall* fnIsTeleportGate)(void* _ecx);
typedef BOOL(__thiscall* fnIsRobe)(void* _ecx);
typedef BOOL(__thiscall* fnIsArmor)(void* _ecx);
typedef BOOL(__thiscall* fnIsBow)(void* _ecx);
typedef BOOL(__thiscall* fnIsCrossBow)(void* _ecx);
typedef BOOL(__thiscall* fnIsSummonScroll)(void* _ecx);
typedef BOOL(__thiscall* fnIsReinforceRecipe)(void* _ecx);
typedef BOOL(__thiscall* fnIsReinforceProbUP)(void* _ecx);
typedef BOOL(__thiscall* fnIsFreeBattleEquip)(void* _ecx);
typedef BOOL(__thiscall* fnIsQuest_n_EventItem)(void* _ecx);
typedef BOOL(__thiscall* fnIsCashItem)(void* _ecx);
typedef BOOL(__thiscall* fnAlwaysZero_1)(void* _ecx);

typedef BOOL(__thiscall* fnCanTrade)(void* _ecx);
typedef BOOL(__thiscall* fnCanSell)(void* _ecx);
typedef BOOL(__thiscall* fnCanBorrow)(void* _ecx);
typedef BOOL(__thiscall* fnCanDrop)(void* _ecx);
typedef BOOL(__thiscall* fnCanPick)(void* _ecx);
typedef BOOL(__thiscall* fnCanRepair)(void* _ecx);
typedef BOOL(__thiscall* fnCanRevive)(void* _ecx);
typedef BOOL(__thiscall* fnCanUse)(void* _ecx);
typedef BOOL(__thiscall* fnCanThrow)(void* _ecx);

typedef LPCSTR(__thiscall* fnGetCodeName)(void* _ecx);

typedef LPVOID(__thiscall* fnGetPosInfo)(void* _ecx);
//Unk                           
typedef BYTE(__thiscall* fnGetLifeState)(void* _ecx);
//Unk                           
typedef BYTE(__thiscall* fnGetMotionState)(void* _ecx);

//Unk                           
typedef BYTE(__thiscall* fnGetBodyMode)(void* _ecx);
//Unk, mby different ret        
typedef LPVOID(__thiscall* fnGetParam)(void*, short paramId);

typedef BOOL(__thiscall* fnIsTargeting)(void* _ecx);

//Unk                           
typedef BYTE(__thiscall* fnGetJobState)(void* _ecx);
//Unk                           
typedef BYTE(__thiscall* fnGetTeleportState)(void* _ecx);

typedef BYTE(__thiscall* fnGetLevel)(void* _ecx);
typedef BYTE(__thiscall* fnGetMaxLevel)(void* _ecx);

typedef BYTE(__thiscall* fnGetMonsterClass)(void* _ecx);

//0x0057f380 Unk                
typedef LPVOID(__thiscall* fnGetPartyInfo)(void* _ecx, LPVOID arg1);

//Unk                           
typedef LPVOID(__thiscall* fnAttachCustomTeleportCapability)(void* _ecx, LPVOID ar1);

//Unk                           
typedef LPVOID(__thiscall* fnRegisterEventHandler)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//Unk                           
typedef LPVOID(__thiscall* fnUnregisterEventHandler)(void* _ecx, LPVOID lpEventHandler);

//Unk                           
typedef void(__thiscall* fnRaiseEvent1)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4);

//Unk                           
typedef void(__thiscall* fnRaiseEvent2)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk                           
typedef void(__thiscall* fnSetEventResult)(void* _ecx, LPVOID arg1);

//Unk                           
typedef void(__thiscall* fnRaiseEventSingle)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//Unk                           
typedef LPVOID(__thiscall* fnShowMenu)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5, LPVOID arg6, LPVOID arg7, LPVOID arg8);

typedef void(__thiscall* fnTerminateMenu)(void* _ecx);

//NOTE: prolly menu ptr         
typedef LPVOID(__thiscall* fnGetMenuContext)(void* _ecx);

//__cdecl !                     
typedef void(__thiscall* fnOutputChatMsg)(void* _ecx, LPVOID arg1);

//NOTE: Maybe struct, or std::string etc
typedef void(__thiscall* fnSetCharName)(void* _ecx, LPCSTR lpCharname);

//Unk
typedef void(__thiscall* fnAddAvailableInteraction)(void* _ecx, LPVOID arg1);

//NOTE:Can be return bool?
typedef	LPVOID(__thiscall* fnCompareGold)(void* _ecx, LPVOID arg1);

//Unk
typedef void(__thiscall* fnOffsetGold1)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5);

//Unk
typedef void(__thiscall* fnOffsetGold2)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5, LPVOID arg6);

//Unk
typedef void(__thiscall* fnOffsetExpPoint)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5, LPVOID arg6);

//Unk
typedef void(__thiscall* fnOffsetSkillPoint)(void* _ecx, LPVOID arg1, LPVOID arg2);

//NOTE: May be wrong
typedef void(__thiscall* fnGetGuildName)(LPCSTR& buffer);

//Unk
typedef LPVOID(__thiscall* fnGetQuestData)(void* _ecx, LPVOID arg1);

//Unk
typedef LPVOID(__thiscall* fnPrepareQuestData)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//Unk
typedef LPVOID(__thiscall* fnPrepareClosedQuestData)(void* _ecx, LPVOID arg1);

//NOTE: Arg may be quest ptr or id
typedef LPVOID(__thiscall* fnSaveClearQuestNow)(void* _ecx, LPVOID arg1);

//NOTE: Arg may be quest ptr or id
typedef BYTE(__thiscall* fnGetQuestStatus)(void* _ecx, LPVOID arg1);

//NOTE: May be wrong
typedef BYTE(__thiscall* fnGetQuestStatusByName)(void* _ecx, LPCSTR lpName);

//Unk
typedef void(__thiscall* fnUpdateQuestStatus)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4);

//NOTE: Arg may be quest ptr or id
typedef void(__thiscall* fnSaveQuestNow)(void* _ecx, LPVOID arg1);

//NOTE: Arg may be quest ptr or id
typedef LPVOID(__thiscall* fnGetQuestEndDate)(void* _ecx, LPVOID arg1, LPVOID arg2);


//NOTE: Arg may be quest ptr or id
typedef void(__thiscall* fnAddQuestArchievementCount)(void* _ecx, LPVOID arg1);

//NOTE: Arg may be quest ptr or id, second arg is most likely count
typedef void(__thiscall* fnSetQuestArchievementCount)(void* _ecx, LPVOID arg1, short count);

typedef BYTE(__thiscall* fnGetRecvQuestCount)(void* _ecx);

//00AE7AB0
typedef void(__thiscall* fnUpdateQuestContentsString)(void* _ecx,
	LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4,
	LPVOID arg5, LPVOID arg6, LPVOID arg7, LPVOID arg8, LPVOID arg9);

//NOTE: Arg may be quest ptr or id, second atrg is most likely count
typedef void(__thiscall* fnUpdateQuestStartDataAll)(void* _ecx, LPVOID arg1);

//Unk
typedef void(__thiscall* fnUpdateQuestTimeLimit)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4);

//NOTE: Arg may be quest ptr or id, second arg is most likely npc Id (unique, ref or what ?)
typedef void(__thiscall* fnUpdateQuestNpcID)(void* _ecx, LPVOID arg1, UINT npcId);

//Unk
typedef void(__thiscall* fnSendQuestEventMessage)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//NOTE: Arg may be quest ptr or id, second arg is most likely msg ptr LPCSTR or LPCWSTR ?
typedef void(__thiscall* fnSendQuestNpcChat)(void* _ecx, LPVOID arg1, LPCSTR msg);

//NOTE: Arg may be quest ptr or id, second arg is most likely progress in % ?
typedef void(__thiscall* fnSendQuestStartTimeBar)(void* _ecx, LPVOID arg1, UINT progress);

//NOTE: Arg may be quest ptr or id, second arg could be result code or smth
typedef void(__thiscall* fnSendQuestCatchMobResult)(void* _ecx, LPVOID arg1, LPVOID arg2);

//NOTE: Arg may be quest ptr or id
typedef BOOL(__thiscall* fnIsCatchMob)(void* _ecx, LPVOID arg1);

//NOTE: Arg may be quest ptr or id, second arg is possibly mob id or ptr
typedef LPVOID(__thiscall* fnDeleteMobForCatchQuest)(void* _ecx, LPVOID arg1, LPVOID mobPossibly);

//NOTE: Arg may be quest ptr or id, second arg is possibly cos instance
typedef LPVOID(__thiscall* fnSpawnCatchCOSForCatchQuest)(void* _ecx, LPVOID arg1, LPVOID cosObjPossibly);

//NOTE: Arg may be quest ptr or id
typedef LPVOID(__thiscall* fnSearchHaveCatchMob)(void* _ecx, LPVOID arg1);

//NOTE: Arg may be quest ptr or id
typedef void(__thiscall* fnDeleteCatchCOS)(void* _ecx, LPVOID arg1);

//NOTE: Kill possibly...
typedef void(__thiscall* fnSetLifeState)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//Active/Inactive ??
typedef void(__thiscall* fnSetChangeObjActiveState)(void* _ecx);

//Unk
typedef void(__thiscall* fnSetInsDungeonInfo)(void* _ecx, LPVOID arg1, LPVOID arg2);

//NOTE: Prolly returns dungeon info ptr
typedef LPVOID(__thiscall* fnGetInsDungeonInfo)(void* _ecx, LPVOID arg1);

//Unk
typedef void(__thiscall* fnSetEventResultInfo)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//Unk
typedef BYTE(__thiscall* fnGetEventResultInfo)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef LPVOID(__thiscall* fnZoe)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4);

//Unk
typedef LPVOID(__thiscall* fnGetVolatileQuestData)(void* _ecx, LPVOID arg1);

//Unk
typedef LPVOID(__thiscall* fnGetVolatileEventData)(void* _ecx, LPVOID arg1);

//Unk
typedef LPVOID(__thiscall* fnRegisterSpot_Object)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5);

//Unk
typedef LPVOID(__thiscall* fnRegisterSpot_Position)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5, LPVOID arg6, LPVOID arg7);

typedef void(__thiscall* fnUnregisterSpot)(void* _ecx, LPVOID arg1);
typedef void(__thiscall* fnUnregisterSpotByQuest)(void* _ecx, LPVOID arg1);

//Unk
typedef LPVOID(__thiscall* fnInquireSameItem)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5);

//Unk
typedef BYTE(__thiscall* fnFindEmptySlotNum)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef LPVOID(__thiscall* fnAddItem_EXT)(void* _ecx,
	LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4,
	LPVOID arg5, LPVOID arg6, LPVOID arg7, LPVOID arg8,
	LPVOID arg9, LPVOID	arg10, LPVOID arg11, LPVOID arg12);

//Unk
typedef LPVOID(__thiscall* fnDeleteItem_EXT)(void* _ecx,
	LPVOID arg1, LPVOID arg2, LPVOID arg3,
	LPVOID arg4, LPVOID arg5, LPVOID arg6);

//Unk
typedef LPVOID(__thiscall* fnMutateItemAt)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef LPVOID(__thiscall* fnCompareMyAndGuildMaster)(void* _ecx);

//Unk
typedef void(__thiscall* fnQB_ForceBlockOperation)(void* _ecx, LPVOID arg1);

//Unk
typedef void(__thiscall* fnQB_ReleaseBlockedJob)(void* _ecx, LPVOID arg1);

//Unk
typedef BOOL(__thiscall* fnQB_IsBlocked)(void* _ecx, LPVOID arg1);

//Unk enum
typedef BYTE(__thiscall* fnGetCurrentArmorType)(void* _ecx, LPVOID arg1);

//Unk enum
typedef BYTE(__thiscall* fnGetGender)(void* _ecx);

//NOTE: __cdecl !
typedef void(__thiscall* fnAddDisplayEffect)(void* _ecx, LPVOID arg1);


//Unk
typedef LPVOID(__thiscall* fnForceDropItem)(void* _ecx,
	LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4,
	LPVOID arg5, LPVOID arg6, LPVOID arg7, LPVOID arg8);

//Unk
typedef LPVOID(__thiscall* fnGetWorldLayerData)(void* _ecx, LPVOID arg1);

//Unk
typedef void(__thiscall* fnSetWorldLayerData)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Prolly ptr to CGObjPC, or other ... mby CQue<T>
typedef LPVOID(__thiscall* fnGetInstanceWorldUsers)(void* _ecx);

typedef void(__thiscall* fnSetCurPosAsLastTelPosition)(void* _ecx);

//NOTE: One of them is out buffer (uint8_t possibly for wep type)... I asume #2
typedef void(__thiscall* fnGetEquipedWeaponType)(void* _ecx, LPVOID arg1, LPVOID arg2);

typedef void(__thiscall* fnRefreshEventGuideData)(void* _ecx);

typedef void(__thiscall* fnSetAvailableInterationPerGObj)(void* _ecx, LPVOID arg1);

//Save ?
typedef void(__thiscall* fnBackupData)(void* _ecx, LPVOID arg1, LPVOID arg2);

typedef LPVOID(__thiscall* fnAllocMsgForPeer)(void* _ecx, LPVOID arg1);

//NOTE: arg could bee target peer or msg struct or both
typedef void(__thiscall* fnSendMsgToPeer)(void* _ecx, LPVOID arg1);

//May be string or wchar_t*
typedef void(__thiscall* fnSetTalkMenuTitle)(void* _ecx, LPCSTR lpStr);

//Unk
typedef void(__thiscall* fnRegisterTalkMenuItem)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//Unk
typedef BOOL(__thiscall* fnIsFirstTalkMenuEnable)(void* _ecx);

//Unk
typedef void(__thiscall* fnShowFirstTalkMenu)(void* _ecx);

//Unk
typedef void(__thiscall* fnEnableTalkMenuItem)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef void(__thiscall* fnResetQuestBlock)(void* _ecx);

//Unk
typedef LPVOID(__thiscall* fnRegisterNPCInteractionBlock)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef LPVOID(__thiscall* fnUnregisterNPCInteractionBlock)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef BOOL(__thiscall* fnIsInteractionAble)(void* _ecx, LPVOID arg1);

//Unk
typedef void(__thiscall* fnChattingByProxy)(void* _ecx, LPVOID arg1);

//Unk
typedef void(__thiscall* fnChattingByProxyArg)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef void(__thiscall* fnSetCharacterState)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef LPVOID(__thiscall* fnEnterWorld)(void* _ecx,
	LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5,
	LPVOID arg6, LPVOID arg7, LPVOID arg8, LPVOID arg9, LPVOID arg10,
	LPVOID arg11, LPVOID arg12, LPVOID arg13, LPVOID arg14, LPVOID arg15);

//Unk
typedef BOOL(__thiscall* fnIsUsingBonusTimeOfGoldTimeItem)(void* _ecx);

//Unk
typedef BOOL(__thiscall* fnIsPremiumItemPlayState)(void* _ecx);

//Unk
typedef BOOL(__thiscall* fnIsQuestByCompositeItem)(void* _ecx, LPVOID arg1);

//Unk
typedef LPVOID(__thiscall* fnUseQuestByCompositeItem)(void* _ecx, LPVOID arg1);

//Unk
typedef BYTE(__thiscall* fnGetRemainCountOfQuestByCompositeItem)(void* _ecx, LPVOID arg1);

//Unk
typedef BYTE(__thiscall* fnGetMaxCountOfQuestByCompositeItem)(void* _ecx, LPVOID arg1);

typedef LPVOID(__thiscall* fnGetEventHandlers)(void* _ecx);

//Unk
typedef LPVOID(__thiscall* fnGetWorldLayerEventHandlers1)(void* _ecx);

//Unk
typedef void(__thiscall* fnLeaveWorldReq)(void* _ecx);

//Unk
typedef LPVOID(__thiscall* fnREH_OnTrapped)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//Unk
typedef LPVOID(__thiscall* fnGetCurSelectedObj)(void* _ecx);

//Unk
typedef BOOL(__thiscall* fnIHaveTradeItem)(void* _ecx);

//Unk
typedef BOOL(__thiscall* fnIHaveCart)(void* _ecx);

//Unk
typedef LPVOID(__thiscall* fnGetWorldLayerEventHandlers2)(void* _ecx);

//Unk
typedef BOOL(__thiscall* fnIHaveMercenary)(void* _ecx);

//Unk
typedef void(__thiscall* fnBanToDefaultWorld)(void* _ecx, LPVOID arg1);

//Unk
typedef void(__thiscall* fnActivateAI)(void* _ecx, LPVOID arg1);

//Unk
typedef BYTE(__thiscall* fnGetMonsterType)(void* _ecx);

//Unk
typedef BOOL(__thiscall* fnIsPartySupportMonster)(void* _ecx);

//Unk
typedef void(__thiscall* fnConsumeHpMp)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3);

//Unk
typedef BOOL(__thiscall* fnIsChinsTombMonster)(void* _ecx);

//Unk
typedef LPVOID(__thiscall* fnEnterScriptMode)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef void(__thiscall* fnUpdateHwanLevel)(void* _ecx, BYTE level);

//Unk
typedef void(__thiscall* fnSetBodyMode)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4);

//Unk
typedef LPVOID(__thiscall* fnCountEmptyInventory)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4);

//Unk
typedef void(__thiscall* fnEngageBuffSkill)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef LPVOID(__thiscall* fnPostTempleReputationSetReq)(void* _ecx,
	LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4,
	LPVOID arg5, LPVOID arg6, LPVOID arg7, LPVOID arg8);

//Unk
typedef LPVOID(__thiscall* fnPostTempleReputationCheckReq)(void* _ecx,
	LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4,
	LPVOID arg5, LPVOID arg6, LPVOID arg7);

//AP notify?
typedef void(__thiscall* fnNotifyClientAPIconStatus)(void* _ecx);

//NOTe: Arg could be buff id or ptr
typedef BOOL(__thiscall* fnIsActiveBuff)(void* _ecx, LPVOID arg1);

//Unk
typedef LPVOID(__thiscall* fnShowRewardWindow)(void* _ecx, LPVOID arg1, LPVOID arg2, LPVOID arg3, LPVOID arg4, LPVOID arg5);

//Unk
typedef BOOL(__thiscall* fnIsAccomplishedCollectionBook_Theme_DWORD)(void* _ecx, LPVOID arg1);

//Unk
typedef BOOL(__thiscall* fnIsAccomplishedCollectionBook_Theme_LPCTSTR)(void* _ecx, LPVOID arg1);

//Unk
typedef BOOL(__thiscall* fnIsRegisteredCollectionBook_Item_DWORD)(void* _ecx, LPVOID arg1, LPVOID arg2);

//Unk
typedef BOOL(__thiscall* fnIsRegisteredCollectionBook_Item_LPCTSTR)(void* _ecx, LPVOID arg1);

class IGObj_VTable
{
public:
	fnIGObj_Ctor				Constructor;
	fnIsChar					IsChar;
	fnIsPC						IsPC;
	fnIsNPC						isNPC;
	fnIsNPCNPC					IsNPCNPC;
	fnIsMonster					IsMonster;
	fnIsCOS						IsCOS;
	fnIsCart					IsCart;
	fnIsVehicle					IsVehicle;
	fnIsPet						IsPet;
	fnIsMercenary				IsMercenary;
	fnIsAttackableCOS			IsAttackableCOS;
	fnIsStruct					IsStruct;
	fnIsItem					IsItem;

	fnIsExpendables				IsExpendables;
	fnIsContainerItem			IsContainerItem;
	fnIsContainerSummonerItem	IsContainerSummonerItem;
	fnIsSpecialty				IsSpecialty;
	fnIsPotion					IsPotion;
	fnIsScroll					IsScroll;
	fnIsBullet					IsBullet;
	fnIsArrow					IsArrow;
	fnIsBolt					IsBolt;
	fnIsHPPotion				IsHPPotion;
	fnIsMPPotion				IsMPPotion;
	fnIsElixir					IsElixir;
	fnIsGold					IsGold;
	fnIsTownPortal				IsTownPortal;
	fnIsEquip					IsEquip;
	fnIsWeapon					IsWeapon;
	fnIsShield					IsShield;
	fnIsAccessory				IsAccessory;
	fnIsTeleportGate			IsTeleportGate;
	fnIsRobe					IsRobe;
	fnIsArmor					IsArmor;
	fnIsBow						IsBow;
	fnIsCrossBow				IsCrossBow;
	fnIsSummonScroll			IsSummonScroll;
	fnIsReinforceRecipe			IsReinforceRecipe;
	fnIsReinforceProbUP			IsReinforceProbUP;
	fnIsFreeBattleEquip			IsFreeBattleEquip;
	fnIsQuest_n_EventItem		IsQuest_n_EventItem;
	fnIsCashItem				IsCashItem;
	fnAlwaysZero_1				AlwaysZero1;

	fnCanTrade					CanTrade;
	fnCanSell					CanSell;
	fnCanBorrow					CanBorrow;
	fnCanDrop					CanDrop;
	fnCanPick					CanPick;
	fnCanRepair					CanRepair;
	fnCanRevive					CanRevive;
	fnCanUse					CanUse;
	fnCanThrow					CanThrow;

	fnGetCodeName				GetCodeName;

	fnGetPosInfo				GetPosInfo;
	fnGetLifeState				GetLifeState;
	fnGetMotionState			GetMotionState;
	fnGetBodyMode				GetBodyMode;
	fnGetParam					GetParam;

	fnIsTargeting				IsTargeting;
	fnGetJobState				GetJobState;
	fnGetTeleportState			GetTeleportState;
	fnGetLevel					GetLevel;
	fnGetMaxLevel				GetMaxLevel;
	fnGetMonsterClass			GetMonsterClass;
	fnGetPartyInfo				GetPartyInfo;
	fnAttachCustomTeleportCapability AttachCustomTeleportCapability;
	fnRegisterEventHandler		RegisterEventHandler;
	fnUnregisterEventHandler	UnregisterEventHandler;
	fnRaiseEvent1				RaiseEvent1;
	fnRaiseEvent2				RaiseEvent2;
	fnSetEventResult			SetEventResult;
	fnRaiseEventSingle			RaiseEventSingle;

	fnShowMenu					ShowMenu;
	fnTerminateMenu				TerminateMenu;
	fnGetMenuContext			GetMenuContext;
	fnOutputChatMsg				OutputChatMsg;

	fnSetCharName				SetCharNAme;
	fnAddAvailableInteraction	AddAvailableInteraction;
	fnCompareGold				CompareGold;
	fnOffsetGold1				OffsetGold1;
	fnOffsetGold2				OffsetGold2;
	fnOffsetExpPoint			OffsetExpPoint;
	fnOffsetSkillPoint			OffsetSkillPoint;
	fnGetGuildName				GetGuildName;

	fnGetQuestData				GetQuestData;
	fnPrepareQuestData			PrepareQuestData;
	fnPrepareClosedQuestData	PrepareClosedQuestData;
	fnSaveClearQuestNow			SaveClearQuestNow;
	fnGetQuestStatus			GetQuestStatus;
	fnGetQuestStatusByName		GetQuestStatusByName;
	fnUpdateQuestStatus			UpdateQuestStatus;
	fnSaveQuestNow				SaveQuestNow;
	fnAddQuestArchievementCount	AddQuestArchievementCount;
	fnSetQuestArchievementCount	SetQuestArchievementCount;
	fnGetRecvQuestCount			GetRecvQuestCount;

	fnUpdateQuestStartDataAll	UpdateQuestStartDataAll;
	fnUpdateQuestTimeLimit		UpdateQuestTimeLimit;
	fnUpdateQuestNpcID			UpdateQuestNpcID;
	fnSendQuestEventMessage		SendQuestEventMessage;
	fnSendQuestNpcChat			SendQuestNpcChat;
	fnSendQuestStartTimeBar		SendQuestStartTimeBar;
	fnSendQuestCatchMobResult	SendQuestCatchMobResult;
	fnIsCatchMob				IsCatchMob;
	fnDeleteMobForCatchQuest	DeleteMobForCatchQuest;
	fnSpawnCatchCOSForCatchQuest	SpawnCatchCOSForCatchQuest;
	fnSearchHaveCatchMob		SearchHaveCatchMob;
	fnDeleteCatchCOS			DeleteCatchCOS;
	fnSetLifeState				SetLifeState;
	fnSetChangeObjActiveState	SetChangeObjActiveState;

	fnSetInsDungeonInfo			SetInsDungeonInfo;
	fnGetInsDungeonInfo			GetInsDungeonInfo;
	fnSetEventResultInfo		SetEventResultInfo;
	fnGetEventResultInfo		GetEventResultInfo;

	fnZoe						Zoe;
	fnGetVolatileQuestData		GetVolatileQuestData;
	fnGetVolatileEventData		GetVolatileEventData;
	fnRegisterSpot_Object		RegisterSpot_Object;
	fnRegisterSpot_Position		RegisterSpot_Position;
	fnUnregisterSpot			UnregisterSpot;
	fnUnregisterSpotByQuest		UnregisterSpotByQuest;

	fnInquireSameItem			InquireSameItem;
	fnFindEmptySlotNum			FindEmptySlotNum;
	fnAddItem_EXT				AddItem_EXT;
	fnDeleteItem_EXT			DeleteItem_EXT;

	fnMutateItemAt				MutateItemAt;
	fnCompareMyAndGuildMaster	CompareMyAndGuildMaster;
	fnQB_ForceBlockOperation	QB_ForceBlockOperation;
	fnQB_ReleaseBlockedJob		QB_ReleaseBlockedJob;
	fnQB_IsBlocked				QB_IsBlocked;
	fnGetCurrentArmorType		GetCurrentArmorType;
	fnGetGender					GetGender;
	fnAddDisplayEffect			AddDisplayEffect;

	fnForceDropItem				ForceDropItem;

	fnGetWorldLayerData			GetWorldLayerData;
	fnSetWorldLayerData			SetWorldLayerData;
	fnGetInstanceWorldUsers		GetInstanceWorldUsers;
	fnSetCurPosAsLastTelPosition SetCurPosAsLastTelPosition;
	fnGetEquipedWeaponType		GetEquipedWeaponType;
	fnRefreshEventGuideData		RefreshEventGuideData;
	fnSetAvailableInterationPerGObj	SetAvailableInteractionPerGObj;

	fnBackupData				BackupData;
	fnAllocMsgForPeer			AllocMsgForPeer;
	fnSendMsgToPeer				SendMsgToPeer;
	fnSetTalkMenuTitle			SetTalkMenuTitle;
	fnRegisterTalkMenuItem		RegisterTalkMenuItem;
	fnIsFirstTalkMenuEnable		IsFirstTalkMenuEnable;
	fnShowFirstTalkMenu			ShowFirstTalkMenu;
	fnEnableTalkMenuItem		EnableTalkMenuItem;
	fnResetQuestBlock			ResetQuestBlock;
	fnRegisterNPCInteractionBlock RegisterNPCInteractionBlock;
	fnUnregisterNPCInteractionBlock UnregisterNPCInteractionBlock;
	fnIsInteractionAble			IsInteractionAble;
	fnChattingByProxy			ChattingByProxy;
	fnChattingByProxyArg		ChattingByProxyArg;
	fnSetCharacterState			SetCharacterState;
	fnEnterWorld				EnterWorld;

	fnIsUsingBonusTimeOfGoldTimeItem	IsUsingBonusTimeOfGoldTimeItem;
	fnIsPremiumItemPlayState	IsPremiumItemPlayState;
	fnIsQuestByCompositeItem	IsQuestByCompositeItem;
	fnUseQuestByCompositeItem	UseQuestByCompositeItem;
	fnGetRemainCountOfQuestByCompositeItem GetRemainCountOfQuestByCompositeItem;
	fnGetMaxCountOfQuestByCompositeItem GetMaxCountOfQuestByCompositeItem;
	fnGetEventHandlers			GetEventHandlers;
	fnGetWorldLayerEventHandlers1	GetworldLayerEventHandlers1;
	fnLeaveWorldReq				LeaveWorldReq;
	fnREH_OnTrapped				REH_OnTrapped;
	fnGetCurSelectedObj			GetCurSelectedObj;
	fnIHaveTradeItem			IHaveTradeItem;
	fnIHaveCart					IHaveCart;
	fnGetWorldLayerEventHandlers2 GetWorldLayerEventHandlers2;
	fnIHaveMercenary			IHavemercenary;
	fnBanToDefaultWorld			BanToDefaultWorld;
	fnActivateAI				ActivateAI;
	fnGetMonsterType			GetMonsterType;
	fnIsPartySupportMonster		IsPartySupportMonster;
	fnConsumeHpMp				ConsumeHpMp;
	fnIsChinsTombMonster		IsChinsTombMonster;
	fnEnterScriptMode			EnterScriptMode;
	fnUpdateHwanLevel			UpdateHwanLevel;
	fnSetBodyMode				SetBodyMode;
	fnCountEmptyInventory		CountEmptyInventory;

	fnEngageBuffSkill			EngageBuffSkill;
	fnPostTempleReputationSetReq	PostTempleReputationSetReq;
	fnPostTempleReputationCheckReq	PostTempleReputationCheckReq;

	fnNotifyClientAPIconStatus	NotifyClientAPIconStatus;
	fnIsActiveBuff				IsActiveBuff;
	fnShowRewardWindow			ShowRewardWindow;
	fnIsAccomplishedCollectionBook_Theme_DWORD IsAccomplishedCollectionBook_Theme_DWORD;
	fnIsAccomplishedCollectionBook_Theme_LPCTSTR IsAccomplishedCollectionBook_Theme_LPCTSTR;
	fnIsRegisteredCollectionBook_Item_DWORD IsRegisteredCollectionBook_Item_DWORD;
	fnIsRegisteredCollectionBook_Item_LPCTSTR IsRegisteredCollectionBook_Item_LPCTSTR;

private:
}; //*g_IGObj_VTable = reinterpret_cast<decltype(g_IGObj_VTable)>(0x00AE78F8);
