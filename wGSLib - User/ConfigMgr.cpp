#include "pch.h"
#include "ConfigMgr.h"

#include <VMProtectSDK.h>

#include "DbMgr.h"
#include "IniReader.h"
#include "SettingsDBSet.h"

#define GS_CONFIG_PATH									".\\wGSLib\\wGSLib.ini"
//#define GS_DB_TRIGGER_ACTIONS_CONFIG_PATH				".\\GSLib\\DbTriggerActions.ini"
//#define GS_FLAG_WORLD_CONFIG_PATH						".\\GSLib\\FlagWorld.ini"
//#define GS_BATTLE_ARENA_CONFIG_PATH						".\\GSLib\\BattleArena.ini"
//#define GS_PK_CONFIG_PATH								".\\GSLib\\PK.ini"
//#define GS_JOB_CONFIG_PATH								".\\GSLib\\Job.ini"
//#define GS_GUILD_CONFIG_PATH							".\\GSLib\\Guild.ini"
//#define GS_ALCHEMY_CONFIG_PATH							".\\GSLib\\Alchemy.ini"
//#define GS_ACADEMY_CONFIG_PATH							".\\GSLib\\Academy.ini"
//#define GS_REGION_RESTRICTION_CONFIG_PATH				".\\GSLib\\RegionRestriction.ini"
//#define GS_MONSTER_CONFIG_PATH							".\\GSLib\\Monster.ini"
//#define GS_DEBUG_CONFIG_PATH							".\\GSLib\\Debug.ini"
//#define GS_NPC_CONFIG_PATH								".\\GSLib\\NPC.ini"
//#define GS_MISC_CONFIG_PATH								".\\GSLib\\Misc.ini"
//#define GS_PET_CONFIG_PATH								".\\GSLib\\Pet.ini"

const std::string& strGsSection = "GameServer";
const std::string& strDbTriggerActionsSection = "DbTriggerActions";
const std::string& strFlagWorldSection = "FlagWorld";
const std::string& strBattleArenaSection = "BattleArena";
const std::string& strPKSection = "PK";
const std::string& strJobSection = "Job";
//const std::string& strGuildSection = "Guild";
const std::string& strAlchemySection = "Alchemy";
//const std::string& strAcademySection = "Academy";
const std::string& strRegionRestrictionSection = "RegionRestriction";
//const std::string& strMonsterSection = "Monster";
//const std::string& strDebugConfigSection = "Debug";
//const std::string& strNpcConfigSection = "NPC";
//const std::string& strMiscConfigSection = "Misc";
const std::string& strPetConfigSection = "Pet";


SGameServerConfig* CConfigMgr::s_pstGameServerConfig = NULL;
SDbTriggerActionsConfig* CConfigMgr::s_pstDbTriggerActionsConfig = NULL;
SFlagWorldCustomConfig* CConfigMgr::s_pstFlagWorldConfig = NULL;
SBattleArenaCustomConfig* CConfigMgr::s_pstBattleArenaConfig = NULL;
SPKCustomConfig* CConfigMgr::s_pstPKConfig = NULL;
SJobCustomConfig* CConfigMgr::s_pstJobConfig = NULL;
//SGuildCustomConfig* CConfigMgr::s_pstGuildConfig = NULL;
SAlchemyCustomConfig* CConfigMgr::s_pstAlchemyConfig = NULL;
//SAcademyCustomConfig* CConfigMgr::s_pstAcademyConfig = NULL;
SRegionRestrictionCustomConfig* CConfigMgr::s_pstRegionRestrictionConfig = NULL;
//SMonsterCustomConfig* CConfigMgr::s_pstMonsterConfig = NULL;
//SDebugConfig* CConfigMgr::s_pstDebugConfig = NULL;
//SNPCConfig* CConfigMgr::s_pstNpcConfig = NULL;
//SMiscConfig* CConfigMgr::s_pstMiscConfig = NULL;
SPetConfig* CConfigMgr::s_pstPetConfig = NULL;

//__DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST CConfigMgr::s_CustomNpcInteractions;

void CConfigMgr::Initialize()
{
	s_pstGameServerConfig = new SGameServerConfig;
	s_pstDbTriggerActionsConfig = new SDbTriggerActionsConfig;
	s_pstFlagWorldConfig = new SFlagWorldCustomConfig;
	s_pstBattleArenaConfig = new SBattleArenaCustomConfig;
	s_pstPKConfig = new SPKCustomConfig;
	s_pstJobConfig = new SJobCustomConfig;
//	s_pstGuildConfig = new SGuildCustomConfig;
	s_pstAlchemyConfig = new SAlchemyCustomConfig;
//	s_pstAcademyConfig = new SAcademyCustomConfig;
	s_pstRegionRestrictionConfig = new SRegionRestrictionCustomConfig;
//	s_pstMonsterConfig = new SMonsterCustomConfig;
//	s_pstDebugConfig = new SDebugConfig;
//	s_pstNpcConfig = new SNPCConfig;
//	s_pstMiscConfig = new SMiscConfig;
	s_pstPetConfig = new SPetConfig;
}
int CConfigMgr::GetServerID()
{
	HMODULE hExe = GetModuleHandle(NULL);
	char fullPath[MAX_PATH] = { 0 };
	char fname[MAX_PATH] = { 0 };
	char ext[MAX_PATH] = { 0 };
	char procName[MAX_PATH] = { 0 };
	GetModuleFileNameA(hExe, fullPath, MAX_PATH);
	_splitpath(fullPath, 0, 0, fname, ext);
	strcpy(procName, fname);
	strcat(procName, ext);
	//std::cout << procName << std::endl;
	if(std::string(procName) == VMProtectDecryptStringA("SR_GameServer2.exe") ||
		std::string(procName) == VMProtectDecryptStringA("wF_GameServer2.exe"))
	{
		SetConsoleTitleA("wFilter GameServer Lib (ServerID: 2)");
		return 2;
	}

		SetConsoleTitleA("wFilter GameServer Lib (ServerID: 1)");
		return 1;


}
bool CConfigMgr::LoadIniSettings()
{
	CIniReader* pReader = NULL;

	//==============================================================================================================================
	//GameServer common
	pReader = new CIniReader(GS_CONFIG_PATH);
	//printf("[%s] @ [%s]\n", strGsSection.c_str(), GS_CONFIG_PATH);

	printf("\n[%s] \n", strGsSection.c_str());


	printf("---------------------------\n");
	//s_pstGameServerConfig->strAddonDbConn = pReader->ReadStringA(strGsSection, "AddonDbConnStr", "[None]");
	s_pstGameServerConfig->strFilterContentDbConn = pReader->ReadStringA(strGsSection, "FilterDbConnStr", "Driver={SQL Server};SERVER=RAVIN;Trusted_Connection=true;DATABASE=SRO_VT_BFILTER;Timeout=5;");
	s_pstGameServerConfig->nServerID = GetServerID();/*pReader->ReadInt(strGsSection, "ServerID", 1);*/
	s_pstGameServerConfig->btMaxCharLevel = pReader->ReadInt(strGsSection, "MaxCharLevel", 110);
	s_pstGameServerConfig->btMaxPetLevel = pReader->ReadInt(strGsSection, "MaxPetLevel", 110);
	s_pstGameServerConfig->dwMaxChinaMasteryLevel = pReader->ReadInt(strGsSection, "MaxChinaMasteryLevel", 330);
	s_pstGameServerConfig->dwMaxEuropeMasteryLevel = pReader->ReadInt(strGsSection, "MaxEuropeMasteryLevel", 240);
	s_pstGameServerConfig->bBypassRatesLimit = pReader->ReadBool(strGsSection, "BypassRatesLimit", true);
	s_pstGameServerConfig->bEnableNullInstanceFix = pReader->ReadBool(strGsSection, "EnableNullInstanceFix", true);
	s_pstGameServerConfig->bDisableGreenBook = pReader->ReadBool(strGsSection, "DisableGreenBook", true);
	s_pstGameServerConfig->bRedirectMsgBoxes = pReader->ReadBool(strGsSection, "RedirectMessageBoxes", false);
	s_pstGameServerConfig->bDisableQuestRaiseEventMsg = pReader->ReadBool(strGsSection, "DisableQuestRaiseEventMsg", false);
	printf("---------------------------\n");


	//==============================================================================================================================
	//DB triggered actions
	//pReader = new CIniReader(GS_DB_TRIGGER_ACTIONS_CONFIG_PATH);

	//printf("\n[%s] @ [%s]\n", strDbTriggerActionsSection.c_str(), GS_DB_TRIGGER_ACTIONS_CONFIG_PATH);
	printf("\n[%s] \n", strDbTriggerActionsSection.c_str());


	printf("---------------------------\n");
	s_pstDbTriggerActionsConfig->nDbPollInterval = pReader->ReadInt(strDbTriggerActionsSection, "DbPollInterval", 1000);
	s_pstDbTriggerActionsConfig->bDeliverDamage = pReader->ReadBool(strDbTriggerActionsSection, "DeliverDamage", false);
	s_pstDbTriggerActionsConfig->bDeliverItems = pReader->ReadBool(strDbTriggerActionsSection, "DeliverItems", false);
	s_pstDbTriggerActionsConfig->bDeliverGold = pReader->ReadBool(strDbTriggerActionsSection, "DeliverGold", false);
	s_pstDbTriggerActionsConfig->bDeliverTeleports = pReader->ReadBool(strDbTriggerActionsSection, "DeliverTeleports", false);
	s_pstDbTriggerActionsConfig->bDeliverSkillPoints = pReader->ReadBool(strDbTriggerActionsSection, "DeliverSkillPoints", false);
	s_pstDbTriggerActionsConfig->bDeliverExperience = pReader->ReadBool(strDbTriggerActionsSection, "DeliverExperience", false);
	s_pstDbTriggerActionsConfig->bDeliverCharReload = pReader->ReadBool(strDbTriggerActionsSection, "DeliverInstantCharReload", false);
	s_pstDbTriggerActionsConfig->bDeliverPvpState = pReader->ReadBool(strDbTriggerActionsSection, "DeliverPvpState", false);
	s_pstDbTriggerActionsConfig->bDeliverStatPoints = pReader->ReadBool(strDbTriggerActionsSection, "DeliverStatPoint", false);
	s_pstDbTriggerActionsConfig->bDeliverHwanLevel = pReader->ReadBool(strDbTriggerActionsSection, "DeliverHwanLevel", false);
	s_pstDbTriggerActionsConfig->bDeliverMobSpawnNearPlayer = pReader->ReadBool(strDbTriggerActionsSection, "DeliverMobSpawnNearPlayer", false);
	s_pstDbTriggerActionsConfig->bDeliverMobSpawnAtPos = pReader->ReadBool(strDbTriggerActionsSection, "DeliverMobSpawnAtPos", false);
	s_pstDbTriggerActionsConfig->bDeliverBuffs = pReader->ReadBool(strDbTriggerActionsSection, "DeliverBuffs", false);
	s_pstDbTriggerActionsConfig->bDeliverBuffsByID = pReader->ReadBool(strDbTriggerActionsSection, "DeliverBuffsByIDAndTime", false);
	s_pstDbTriggerActionsConfig->bDeliverZerk = pReader->ReadBool(strDbTriggerActionsSection, "DeliverZerk", false);
	s_pstDbTriggerActionsConfig->bDeliverSilk = pReader->ReadBool(strDbTriggerActionsSection, "DeliverSilk", false);
	s_pstDbTriggerActionsConfig->bDeliverUpdateItem = pReader->ReadBool(strDbTriggerActionsSection, "DeliverUpdateItem", false);
	s_pstDbTriggerActionsConfig->bDeliverDropItem = pReader->ReadBool(strDbTriggerActionsSection, "DeliverDropItem", false);
	s_pstDbTriggerActionsConfig->bEnableDelayReportMsg = pReader->ReadBool(strDbTriggerActionsSection, "EnableDelayReportMsg", true);

	printf("---------------------------\n");

	//==============================================================================================================================
	//Flag world
	//pReader = new CIniReader(GS_FLAG_WORLD_CONFIG_PATH);

	//printf("\n[%s] @ [%s] \n", strFlagWorldSection.c_str(), GS_FLAG_WORLD_CONFIG_PATH);
	printf("\n[%s] \n", strFlagWorldSection.c_str());

	printf("---------------------------\n");
	s_pstFlagWorldConfig->strFlagWorldKillRewardCodename = pReader->ReadStringA(strFlagWorldSection, "KillRewardCodename", "ITEM_ETC_E080723_ICETROPHY");
	s_pstFlagWorldConfig->btFlagWorldKillRewardCount = pReader->ReadInt(strFlagWorldSection, "KillRewardCount", 1);
	s_pstFlagWorldConfig->strFlagWorldWinRewardCodename = pReader->ReadStringA(strFlagWorldSection, "WinRewardCodename", "ITEM_ETC_E080723_ICETROPHY");
	s_pstFlagWorldConfig->btFlagWorldWinRewardCount = pReader->ReadInt(strFlagWorldSection, "WinRewardCount", 1);
	printf("---------------------------\n");

	//==============================================================================================================================
	//Battle arena
	//pReader = new CIniReader(GS_BATTLE_ARENA_CONFIG_PATH);

	//printf("\n[%s] @ [%s] \n", strBattleArenaSection.c_str(), GS_BATTLE_ARENA_CONFIG_PATH);

	printf("\n[%s] \n", strBattleArenaSection.c_str());


	printf("---------------------------\n");
	s_pstBattleArenaConfig->strBattleArenaRewardCodename = pReader->ReadStringA(strBattleArenaSection, "RewardCodename", "ITEM_ETC_ARENA_COIN");
	s_pstBattleArenaConfig->btBattleArenaGuildAndJobWinRewardCount = pReader->ReadInt(strBattleArenaSection, "GuildAndJobWinRewardCount", 7);
	s_pstBattleArenaConfig->btBattleArenaGuildAndJobLoseRewardCount = pReader->ReadInt(strBattleArenaSection, "GuildAndJobLoseRewardCount", 2);
	s_pstBattleArenaConfig->btBattleArenaPartyAndRandomWinRewardCount = pReader->ReadInt(strBattleArenaSection, "PartyAndRandomWinRewardCount", 5);
	s_pstBattleArenaConfig->btBattleArenaPartyAndRandomLoseRewardCount = pReader->ReadInt(strBattleArenaSection, "PartyAndRandomLoseRewardCount", 1);
	printf("---------------------------\n");

	//==============================================================================================================================
	//PK
	//pReader = new CIniReader(GS_PK_CONFIG_PATH);

	//printf("\n[%s] @ [%s] \n", strPKSection.c_str(), GS_PK_CONFIG_PATH);
		printf("\n[%s] \n", strPKSection.c_str());

	printf("---------------------------\n");
	s_pstPKConfig->btMinLevel = pReader->ReadInt(strPKSection, "MinLevel", 20);
	//s_pstPKConfig->btMinLevelForItemDrop = pReader->ReadInt(strPKSection, "MinLevelForItemDrop", 10);
	printf("---------------------------\n");

	//==============================================================================================================================
	//Job
	//pReader = new CIniReader(GS_JOB_CONFIG_PATH);

	printf("\n[%s] \n", strJobSection.c_str());

	//printf("---------------------------\n");
	//s_pstJobConfig->btMaxLevel = pReader->ReadInt(strJobSection, "MaxLevel", 7);
	s_pstJobConfig->bDisableJobNpcSpawn = pReader->ReadBool(strJobSection, "DisableJobNpcSpawn", false);
	//s_pstJobConfig->btJobCaveApLevel = pReader->ReadInt(strJobSection, "JobCaveAPLevel", 105);
	//printf("---------------------------\n");

	//==============================================================================================================================
	//Guild
	/*pReader = new CIniReader(GS_GUILD_CONFIG_PATH);

	printf("\n[%s] @ [%s] \n", strGuildSection.c_str(), GS_GUILD_CONFIG_PATH);

	printf("---------------------------\n");
	s_pstGuildConfig->btMaxUnionChatPlayers = pReader->ReadInt(strGuildSection, "MaxUnionChatPlayers", 12);
	s_pstGuildConfig->btMinGuildLevelForMercenarySpawn = pReader->ReadInt(strGuildSection, "MinGuildLevelForMercenarySpawn", 3);
	s_pstGuildConfig->bAllowNonGmMercenarySpawn = pReader->ReadBool(strGuildSection, "AllowNonGmMercenarySpawn", false);
	s_pstGuildConfig->bDisableGrantNameRestriction = pReader->ReadBool(strGuildSection, "DisableGrantNameRestriction", false);
	printf("---------------------------\n");*/

	//==============================================================================================================================
	//Alchemy
	/*pReader = new CIniReader(GS_ALCHEMY_CONFIG_PATH);

	printf("\n[%s] @ [%s] \n", strAlchemySection.c_str(), GS_ALCHEMY_CONFIG_PATH);
	*/
	printf("\n[%s] \n", strAlchemySection.c_str());
	printf("---------------------------\n");
	s_pstAlchemyConfig->btMinItemLevelForAstralToTakeEffect = pReader->ReadInt(strAlchemySection, "MinItemLevelForAstralToTakeEffect", 4);
	s_pstAlchemyConfig->btItemLevelForAstralRecovery = pReader->ReadInt(strAlchemySection, "ItemLevelForAstralRecovery", 4);
	//s_pstAlchemyConfig->btMaxItemPlusDropCheck = pReader->ReadBool(strAlchemySection, "MaxItemPlusDropCheck", 0);
	printf("---------------------------\n");

	//==============================================================================================================================
	//Academy
	/*pReader = new CIniReader(GS_ACADEMY_CONFIG_PATH);

	printf("\n[%s] @ [%s] \n", strAcademySection.c_str(), GS_ACADEMY_CONFIG_PATH);

	printf("---------------------------\n");
	s_pstAcademyConfig->btCreationLevelRequirement = pReader->ReadInt(strAcademySection, "CreationLevelRequirement", 60);
	s_pstAcademyConfig->dwCreationGoldRequirement = pReader->ReadInt(strAcademySection, "CreationGoldRequirement", 100000);
	s_pstAcademyConfig->btMaxSubMentors = pReader->ReadInt(strAcademySection, "MaxSubMentors", 2);
	s_pstAcademyConfig->btMaxApprentices = pReader->ReadInt(strAcademySection, "MaxApprentices", 5);
	s_pstAcademyConfig->btSubMentorLevelRequirement = pReader->ReadInt(strAcademySection, "SubMentorLevelRequirement", 60);
	s_pstAcademyConfig->btApprenticeLevelRequirement = pReader->ReadInt(strAcademySection, "ApprenticeLevelRequirement", 40);
	s_pstAcademyConfig->dwDisbandPenaltySeconds = pReader->ReadInt(strAcademySection, "DisbandPenaltySeconds", 604800);
	printf("---------------------------\n");*/

	//==============================================================================================================================
	//Region restriction
	//pReader = new CIniReader(GS_REGION_RESTRICTION_CONFIG_PATH);

	printf("\n[%s] \n", strRegionRestrictionSection.c_str());

	printf("---------------------------\n");
	s_pstRegionRestrictionConfig->bEnableHideNameRegions = pReader->ReadBool(strRegionRestrictionSection, "EnableHideNameRegions", false);
	printf("---------------------------\n");

	////==============================================================================================================================
	//Monsters
	/*pReader = new CIniReader(GS_MONSTER_CONFIG_PATH);

	printf("\n[%s] @ [%s] \n", strMonsterSection.c_str(), GS_MONSTER_CONFIG_PATH);

	printf("---------------------------\n");
	s_pstMonsterConfig->bDisableGiantSpawn = pReader->ReadBool(strMonsterSection, "DisableGiantMonsterSpawn", false);
	s_pstMonsterConfig->bEnableUniqueKillHook = pReader->ReadBool(strMonsterSection, "EnableUniqueKillHook", false);
	printf("---------------------------\n");*/

	//==============================================================================================================================
	//Debug
	/*pReader = new CIniReader(GS_DEBUG_CONFIG_PATH);

	printf("\n[%s] @ [%s] \n", strDebugConfigSection.c_str(), GS_DEBUG_CONFIG_PATH);

	printf("---------------------------\n");
	s_pstDebugConfig->bDebugPrivilege = pReader->ReadBool(strDebugConfigSection, "EnableDebugPrivilege", false);
	s_pstDebugConfig->bDebuggerPresent = pReader->ReadBool(strDebugConfigSection, "EnableDebuggerPresent", false);
	s_pstDebugConfig->bTopLevelExceptionHook = pReader->ReadBool(strDebugConfigSection, "EnableTopLevelExceptionFilterHook", false);
	s_pstDebugConfig->bMinidumpOnTopLevelException = pReader->ReadBool(strDebugConfigSection, "EnableMinidumpOnTopLevelException", false);
	s_pstDebugConfig->bDisableEndlessLoopChecker = pReader->ReadBool(strDebugConfigSection, "DisableEndlessLoopChecker", false);
	s_pstDebugConfig->bLogLastNetMsgs = pReader->ReadBool(strDebugConfigSection, "EnableLogLastNetMsgs", false);
	printf("---------------------------\n");*/

	//==============================================================================================================================
	//NPC
	/*pReader = new CIniReader(GS_NPC_CONFIG_PATH);

	printf("\n[%s] @ [%s] \n", strNpcConfigSection.c_str(), GS_NPC_CONFIG_PATH);

	printf("---------------------------\n");
	s_pstNpcConfig->btMaxLevelForTeleportAtDeathPosOrRecallPoint = pReader->ReadInt(strNpcConfigSection, "MaxLevelForTeleportAtDeathPosOrRecallPoint", 20);
	printf("---------------------------\n");*/

	//==============================================================================================================================
	//Misc
	/*pReader = new CIniReader(GS_MISC_CONFIG_PATH);

	printf("\n[%s] @ [%s] \n", strMiscConfigSection.c_str(), GS_MISC_CONFIG_PATH);

	printf("---------------------------\n");
	s_pstMiscConfig->btMaxLevelForRessurectAtSamePos = pReader->ReadInt(strMiscConfigSection, "MaxLevelForRessurectAtSamePos", 10);
	printf("---------------------------\n");*/



	//Pet
	/*pReader = new CIniReader(GS_PET_CONFIG_PATH);

	printf("\n[%s] @ [%s] \n", strPetConfigSection.c_str(), GS_PET_CONFIG_PATH);
	*/
	printf("\n[%s] \n", strPetConfigSection.c_str());

	printf("---------------------------\n");
	s_pstPetConfig->btGrabPetInventorySize = pReader->ReadInt(strPetConfigSection, "GrabPetInventorySize", 28);
	printf("---------------------------\n");

	return true;
}

bool CConfigMgr::LoadDbSettings()
{
	CSettingsDBSet* pSettingsDbSet = CDbMgr::GetSettingsDbSet();
	//pSettingsDbSet->GetCustomNpcInteractionRecords(s_CustomNpcInteractions);

	return true;
}

SGameServerConfig* CConfigMgr::GetGameServerConfig()
{
	return s_pstGameServerConfig;
}

SDbTriggerActionsConfig* CConfigMgr::GetDbTriggerActionsConfig()
{
	return s_pstDbTriggerActionsConfig;
}

SFlagWorldCustomConfig* CConfigMgr::GetFlagWorldConfig()
{
	return s_pstFlagWorldConfig;
}

SBattleArenaCustomConfig* CConfigMgr::GetBattleArenaConfig()
{
	return s_pstBattleArenaConfig;
}

SPKCustomConfig* CConfigMgr::GetPKConfig()
{
	return s_pstPKConfig;
}

SJobCustomConfig* CConfigMgr::GetJobConfig()
{
	return s_pstJobConfig;
}

//SGuildCustomConfig* CConfigMgr::GetGuildConfig()
//{
//	return s_pstGuildConfig;
//}

SAlchemyCustomConfig* CConfigMgr::GetAlchemyConfig()
{
	return s_pstAlchemyConfig;
}
//
//SAcademyCustomConfig* CConfigMgr::GetAcademyConfig()
//{
//	return s_pstAcademyConfig;
//}
//
SRegionRestrictionCustomConfig* CConfigMgr::GetRegionRestrictionConfig()
{
	return s_pstRegionRestrictionConfig;
}
//
//SMonsterCustomConfig* CConfigMgr::GetMonsterConfig()
//{
//	return s_pstMonsterConfig;
//}
//
//SDebugConfig* CConfigMgr::GetDebugConfig()
//{
//	return s_pstDebugConfig;
//}
//
//SNPCConfig* CConfigMgr::GetNpcConfig()
//{
//	return s_pstNpcConfig;
//}
//
//SMiscConfig* CConfigMgr::GetMiscConfig()
//{
//	return s_pstMiscConfig;
//}
//
SPetConfig* CConfigMgr::GetPetConfig()
{
	return s_pstPetConfig;
}
//
//__DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST& CConfigMgr::GetCustomNpcInteractions()
//{
//	return s_CustomNpcInteractions;
//}