#pragma once
#include "pch.h"

struct SGameServerConfig
{
	//std::string strAddonDbConn;
	std::string strFilterContentDbConn;
	int nServerID;

	BYTE btMaxCharLevel;
	BYTE btMaxPetLevel;
	DWORD dwMaxChinaMasteryLevel;
	DWORD dwMaxEuropeMasteryLevel;

	bool bBypassRatesLimit;
	bool bEnableNullInstanceFix;
	bool bDisableGreenBook;
	bool bRedirectMsgBoxes;
	bool bDisableQuestRaiseEventMsg;
};

struct SDbTriggerActionsConfig
{
	int nDbPollInterval;
	bool bDeliverDamage;
	bool bDeliverItems;
	bool bDeliverGold;
	bool bDeliverTeleports;
	bool bDeliverSkillPoints;
	bool bDeliverExperience;
	bool bDeliverCharReload;
	bool bDeliverPvpState;
	bool bDeliverStatPoints;
	bool bDeliverHwanLevel;
	bool bDeliverMobSpawnNearPlayer;
	bool bDeliverMobSpawnAtPos;
	bool bDeliverBuffs;
	bool bDeliverBuffsByID;
	bool bDeliverZerk;
	bool bDeliverSilk;
	bool bDeliverUpdateItem;
	bool bDeliverDropItem;
	bool bEnableDelayReportMsg;
};

struct SFlagWorldCustomConfig
{
	std::string strFlagWorldKillRewardCodename;
	BYTE btFlagWorldKillRewardCount;

	std::string strFlagWorldWinRewardCodename;
	BYTE btFlagWorldWinRewardCount;
};

struct SBattleArenaCustomConfig
{
	std::string strBattleArenaRewardCodename;

	//Guild & job - win
	BYTE btBattleArenaGuildAndJobWinRewardCount;
	//Guild & job - lose
	BYTE btBattleArenaGuildAndJobLoseRewardCount;
	//Party & random - win
	BYTE btBattleArenaPartyAndRandomWinRewardCount;
	//Party & random - lose
	BYTE btBattleArenaPartyAndRandomLoseRewardCount;
};

struct SPKCustomConfig
{
	BYTE btMinLevel;
	BYTE btMinLevelForItemDrop;
};

struct SJobCustomConfig
{
	BYTE btMaxLevel;
	bool bDisableJobNpcSpawn;
	BYTE btJobCaveApLevel;
};

struct SGuildCustomConfig
{
	BYTE btMaxUnionChatPlayers;
	BYTE btMinGuildLevelForMercenarySpawn;
	bool bAllowNonGmMercenarySpawn;
	bool bDisableGrantNameRestriction;
};

struct SAlchemyCustomConfig
{
	BYTE btMinItemLevelForAstralToTakeEffect;
	BYTE btItemLevelForAstralRecovery;
	bool btMaxItemPlusDropCheck;
};

struct SAcademyCustomConfig
{
	BYTE btCreationLevelRequirement;
	DWORD dwCreationGoldRequirement;
	BYTE btMaxSubMentors;
	BYTE btMaxApprentices;
	BYTE btSubMentorLevelRequirement;
	BYTE btApprenticeLevelRequirement;
	DWORD dwDisbandPenaltySeconds;
};

struct SRegionRestrictionCustomConfig
{
	bool bEnableHideNameRegions;
};

struct SMonsterCustomConfig
{
	bool bDisableGiantSpawn;
	bool bEnableUniqueKillHook;
};

struct SDebugConfig
{
	bool bDebugPrivilege;
	bool bDebuggerPresent;
	bool bTopLevelExceptionHook;
	bool bMinidumpOnTopLevelException;
	bool bDisableEndlessLoopChecker;
	bool bLogLastNetMsgs;
};

struct SNPCConfig
{
	BYTE btMaxLevelForTeleportAtDeathPosOrRecallPoint;
};

struct SMiscConfig
{
	BYTE btMaxLevelForRessurectAtSamePos;
};

struct SPetConfig
{
	BYTE btGrabPetInventorySize;
};

class CConfigMgr
{
private:
	CConfigMgr();

	static SGameServerConfig* s_pstGameServerConfig;
	static SDbTriggerActionsConfig* s_pstDbTriggerActionsConfig;
	static SFlagWorldCustomConfig* s_pstFlagWorldConfig;
	static SBattleArenaCustomConfig* s_pstBattleArenaConfig;
	static SPKCustomConfig* s_pstPKConfig;
	static SJobCustomConfig* s_pstJobConfig;
//	static SGuildCustomConfig* s_pstGuildConfig;
	static SAlchemyCustomConfig* s_pstAlchemyConfig;
//	static SAcademyCustomConfig* s_pstAcademyConfig;
	static SRegionRestrictionCustomConfig* s_pstRegionRestrictionConfig;
//	static SMonsterCustomConfig* s_pstMonsterConfig;
//	static SDebugConfig* s_pstDebugConfig;
//	static SNPCConfig* s_pstNpcConfig;
//	static SMiscConfig* s_pstMiscConfig;
	static SPetConfig* s_pstPetConfig;

//	static __DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST s_CustomNpcInteractions;

public:
	static void Initialize();
	static bool LoadIniSettings();
	static bool LoadDbSettings();
	static int GetServerID();

	static SGameServerConfig* GetGameServerConfig();
	static SDbTriggerActionsConfig* GetDbTriggerActionsConfig();
	static SFlagWorldCustomConfig* GetFlagWorldConfig();
	static SBattleArenaCustomConfig* GetBattleArenaConfig();
	static SPKCustomConfig* GetPKConfig();
	static SJobCustomConfig* GetJobConfig();
//	static SGuildCustomConfig* GetGuildConfig();
	static SAlchemyCustomConfig* GetAlchemyConfig();
//	static SAcademyCustomConfig* GetAcademyConfig();
	static SRegionRestrictionCustomConfig* GetRegionRestrictionConfig();
//	static SMonsterCustomConfig* GetMonsterConfig();
//	static SDebugConfig* GetDebugConfig();
//	static SNPCConfig* GetNpcConfig();
//	static SMiscConfig* GetMiscConfig();
	static SPetConfig* GetPetConfig();

	//static __DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST& GetCustomNpcInteractions();
};