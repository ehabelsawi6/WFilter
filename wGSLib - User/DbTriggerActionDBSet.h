#pragma once
#include "pch.h"
#include "DbConnection.h"
#include "AutoCriticalSection.h"

struct E_INSTANT_DELIVERY_RECORD_TYPE
{
	enum Enum
	{
		Damage,
		Item,
		Gold,
		Teleport,
		SkillPoint,
		Experience,
		CharReload,
		PvpState,
		StatPoint,
		HwanLevel,
		MobSpawnNearPlayer,
		MobSpawnAtPos,
		Buffs,
		Buffs1,
		Berserker,
		Silk,
		UpdateItem,
		DropItem
	};
};

struct SInstantDmgDbRecord
{
	int nID;
	int nCharID;
	int nReasonMask;
	int nAmount;
};

struct SInstantChangeItemDbRecord
{
	int nID;
	int nCharID;
	int nSlot;
	char szCodename[128];
};

struct SInstantDropItemDbRecord
{
	int nID;
	int nCharID;
	int nPlus;
	int nCount;
	char szCodename[128];
};

struct SInstantItemDbRecord
{
	int nID;
	int nCharID;
	BYTE btStorageType;
	char szCodename[128];
	int nItemCount;
	BYTE btPlusValue;
};

struct SInstantGoldDbRecord
{
	int nID;
	int nCharID;
	int nAmount;
	bool bShowDeliveryMsg;
};

struct SInstantTeleportDbRecord
{
	int nID;
	int nCharID;
	WORD wWorldLayerID;
	WORD wWorldID;
	WORD wRegionID;
	float fltPosX;
	float fltPosY;
	float fltPosZ;
};

struct SInstantSkillPointDbRecord
{
	int nID;
	int nCharID;
	int nAmount;
};

struct SInstantExperienceDbRecord
{
	int nID;
	int nCharID;
	DWORD64 qwLevelExperience;
	DWORD64 qwSkillExperience;
};

struct SInstantCharReloadDbRecord
{
	int nID;
	int nCharID;
};

struct SInstantPvpStateDbRecord
{
	int nID;
	int nCharID;
	BYTE btState;
};

struct SInstantStatPointDbRecord
{
	int nID;
	int nCharID;
	WORD wFreeStatPoints;
	WORD wStr;
	WORD wInt;
};

struct SInstantHwanLevelDbRecord
{
	int nID;
	int nCharID;
	BYTE btLevel;
};

struct SInstantMobSpawnNearPlayerDbRecord
{
	int nID;
	int nCharID;
	BYTE btType;
	float fltRange;
	DWORD dwRefObjID;
};

struct SInstantMobSpawnAtPosDbRecord
{
	int nID;
	int nServerID;

	WORD wWorldLayerID;
	WORD wWorldID;

	WORD wRegionID;
	float fltPosX;
	float fltPosY;
	float fltPosZ;

	BYTE btMobType;
	float fltRange;
	DWORD dwRefObjID;
};

struct SInstantBuffsDbRecord
{
	int nID;
	int nCharID;
	char szCodeName128[128];
};

struct SInstantBuffs1DbRecord
{
	int nID;
	int nCharID;
	int nSkillID;
	int nTime;
};

struct SInstantZerkDbRecord
{
	int nID;
	int nCharID;
	int nPoints;
};

struct SInstantSilkDbRecord
{
	int nID;
	int nCharID;
	int nSilk;
	int nSilkGift;
	int nSilkPoint;
	bool bSendPacket;
};

#define __DBSET_INSTANT_DMG_DB_RECORD_LST						std::list<SInstantDmgDbRecord>
#define __DBSET_INSTANT_DMG_DB_RECORD_LST_IT					__DBSET_INSTANT_DMG_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_UPDATE_ITEM_DB_RECORD_LST				std::list<SInstantChangeItemDbRecord>
#define __DBSET_INSTANT_UPDATE_ITEM_DB_RECORD_LST_IT			__DBSET_INSTANT_UPDATE_ITEM_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_DROP_ITEM_DB_RECORD_LST				std::list<SInstantDropItemDbRecord>
#define __DBSET_INSTANT_DROP_ITEM_DB_RECORD_LST_IT			__DBSET_INSTANT_DROP_ITEM_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_ITEM_DB_RECORD_LST						std::list<SInstantItemDbRecord>
#define __DBSET_INSTANT_ITEM_DB_RECORD_LST_IT					__DBSET_INSTANT_ITEM_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_GOLD_DB_RECORD_LST						std::list<SInstantGoldDbRecord>
#define __DBSET_INSTANT_GOLD_DB_RECORD_LST_IT					__DBSET_INSTANT_GOLD_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_TELEPORT_DB_RECORD_LST					std::list<SInstantTeleportDbRecord>
#define __DBSET_INSTANT_TELEPORT_DB_RECORD_LST_IT				__DBSET_INSTANT_TELEPORT_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_SKILL_POINT_DB_RECORD_LST				std::list<SInstantSkillPointDbRecord>
#define __DBSET_INSTANT_SKILL_POINT_DB_RECORD_LST_IT			__DBSET_INSTANT_SKILL_POINT_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_EXPERIENCE_DB_RECORD_LST				std::list<SInstantExperienceDbRecord>
#define __DBSET_INSTANT_EXPERIENCE_DB_RECORD_LST_IT				__DBSET_INSTANT_EXPERIENCE_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_CHAR_RELOAD_DB_RECORD_LST				std::list<SInstantCharReloadDbRecord>
#define __DBSET_INSTANT_CHAR_RELOAD_DB_RECORD_LST_IT			__DBSET_INSTANT_CHAR_RELOAD_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_PVP_STATE_DB_RECORD_LST					std::list<SInstantPvpStateDbRecord>
#define __DBSET_INSTANT_PVP_STATE_DB_RECORD_LST_IT				__DBSET_INSTANT_PVP_STATE_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_STAT_POINT_DB_RECORD_LST				std::list<SInstantStatPointDbRecord>
#define __DBSET_INSTANT_STAT_POINT_DB_RECORD_LST_IT				__DBSET_INSTANT_STAT_POINT_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_HWAN_LEVEL_DB_RECORD_LST				std::list<SInstantHwanLevelDbRecord>
#define __DBSET_INSTANT_HWAN_LEVEL_DB_RECORD_LST_IT				__DBSET_INSTANT_HWAN_LEVEL_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_MOB_SPAWN_NEAR_PLAYER_DB_RECORD_LST		std::list<SInstantMobSpawnNearPlayerDbRecord>
#define __DBSET_INSTANT_MOB_SPAWN_NEAR_PLAYER_DB_RECORD_LST_IT	__DBSET_INSTANT_MOB_SPAWN_NEAR_PLAYER_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_MOB_SPAWN_AT_POS_DB_RECORD_LST			std::list<SInstantMobSpawnAtPosDbRecord>
#define __DBSET_INSTANT_MOB_SPAWN_AT_POS_DB_RECORD_LST_IT		__DBSET_INSTANT_MOB_SPAWN_AT_POS_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_BUFFS_DB_RECORD_LST						std::list<SInstantBuffsDbRecord>
#define __DBSET_INSTANT_BUFFS_DB_RECORD_LST_IT					__DBSET_INSTANT_BUFFS_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_BUFFS1_DB_RECORD_LST						std::list<SInstantBuffs1DbRecord>
#define __DBSET_INSTANT_BUFFS1_DB_RECORD_LST_IT					__DBSET_INSTANT_BUFFS1_DB_RECORD_LST::iterator


#define __DBSET_INSTANT_ZERK_DB_RECORD_LST						std::list<SInstantZerkDbRecord>
#define __DBSET_INSTANT_ZERK_DB_RECORD_LST_IT					__DBSET_INSTANT_ZERK_DB_RECORD_LST::iterator

#define __DBSET_INSTANT_SILK_DB_RECORD_LST						std::list<SInstantSilkDbRecord>
#define __DBSET_INSTANT_SILK_DB_RECORD_LST_IT					__DBSET_INSTANT_SILK_DB_RECORD_LST::iterator

class CDbTriggerActionDBSet
{
private:
	CDbConnection* m_pDbConnection;
	CAutoCriticalSection* m_pACS;
	bool DeleteRecordByDBID(int nID, const std::string& table);

public:
	CDbTriggerActionDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS);
	~CDbTriggerActionDBSet();

	bool GetInstantDmgRecords(__DBSET_INSTANT_DMG_DB_RECORD_LST& result);
	bool GetInstantUpdateItemRecords(__DBSET_INSTANT_UPDATE_ITEM_DB_RECORD_LST& result);
	bool GetInstantDropItemRecords(__DBSET_INSTANT_DROP_ITEM_DB_RECORD_LST& result);
	bool GetInstantItemRecords(__DBSET_INSTANT_ITEM_DB_RECORD_LST& result);
	bool GetInstantGoldRecords(__DBSET_INSTANT_GOLD_DB_RECORD_LST& result);
	bool GetInstantTeleportRecords(__DBSET_INSTANT_TELEPORT_DB_RECORD_LST& result);
	bool GetInstantSkillPointRecords(__DBSET_INSTANT_SKILL_POINT_DB_RECORD_LST& result);
	bool GetInstantExperienceRecords(__DBSET_INSTANT_EXPERIENCE_DB_RECORD_LST& result);
	bool GetInstantCharReloadRecords(__DBSET_INSTANT_CHAR_RELOAD_DB_RECORD_LST& result);
	bool GetInstantPvpStateRecords(__DBSET_INSTANT_PVP_STATE_DB_RECORD_LST& result);
	bool GetInstantStatPointRecords(__DBSET_INSTANT_STAT_POINT_DB_RECORD_LST& result);
	bool GetInstantHwanLevelRecords(__DBSET_INSTANT_HWAN_LEVEL_DB_RECORD_LST& result);
	bool GetInstantMobSpawnNearPlayerRecords(__DBSET_INSTANT_MOB_SPAWN_NEAR_PLAYER_DB_RECORD_LST& result);
	bool GetInstantMobSpawnAtPosRecords(__DBSET_INSTANT_MOB_SPAWN_AT_POS_DB_RECORD_LST& result);
	bool GetInstantBuffsRecords(__DBSET_INSTANT_BUFFS_DB_RECORD_LST& result);
	bool GetInstantBuffs1Records(__DBSET_INSTANT_BUFFS1_DB_RECORD_LST& result);
	bool GetInstantZerkRecords(__DBSET_INSTANT_ZERK_DB_RECORD_LST& result);
	bool GetInstantSilkRecords(__DBSET_INSTANT_SILK_DB_RECORD_LST& result);

	bool DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Enum type, int nID);
	static std::string GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Enum type);
};