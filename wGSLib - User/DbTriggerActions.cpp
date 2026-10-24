#include "pch.h"
#include "DbTriggerActions.h"

#include "ConfigMgr.h"
#include "DbMgr.h"
#include "DbTriggerActionDBSet.h"
#include "GObjPC.h"
#include "ObjMgr.h"
#include <thread>

HANDLE CDbTriggerActions::s_hDeliveryThread = NULL;


bool CDbTriggerActions::DeliverDamage()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_DMG_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantDmgRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain dmg dealer records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_DMG_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_DMG_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantDmgDbRecord record = (SInstantDmgDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->DealDamage(record.nReasonMask, record.nAmount);
				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Damage, itCur->nID))
					printf("%s - WTF?! Failed to delete dmg dealer record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverUpdateItem()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_UPDATE_ITEM_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantUpdateItemRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain Update Item dealer records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_UPDATE_ITEM_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_UPDATE_ITEM_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantChangeItemDbRecord record = (SInstantChangeItemDbRecord)(*itCur);

		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->SetLiveItem(record.nSlot, record.szCodename);
				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::UpdateItem, itCur->nID))
					printf("%s - WTF?! Failed to delete update item dealer record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverDropItem()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_DROP_ITEM_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantDropItemRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain drop Item dealer records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_DROP_ITEM_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_DROP_ITEM_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantDropItemDbRecord record = (SInstantDropItemDbRecord)(*itCur);

		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->DropItem(record.szCodename, record.nCount, record.nPlus);
				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::DropItem, itCur->nID))
					printf("%s - WTF?! Failed to delete drop item dealer record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverItems()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_ITEM_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantItemRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain instant item delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_ITEM_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_ITEM_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantItemDbRecord record = (SInstantItemDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				DWORD dwItemAddResult = pPC->AddItem(record.btStorageType, record.szCodename, record.nItemCount, record.btPlusValue);
				if (dwItemAddResult == 1)
				{
					if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Item, record.nID))
						printf("%s - WTF?! Failed to delete item delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
				}
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverGold()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_GOLD_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantGoldRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain gold delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_GOLD_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_GOLD_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantGoldDbRecord record = (SInstantGoldDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->AddGold(record.nAmount, record.bShowDeliveryMsg);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Gold, record.nID))
					printf("%s - WTF?! Failed to delete gold delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverTeleports()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_TELEPORT_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantTeleportRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain teleport delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_TELEPORT_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_TELEPORT_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantTeleportDbRecord record = (SInstantTeleportDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				SPosInfo posInfo(record.wRegionID, record.fltPosX, record.fltPosY, record.fltPosZ);
				SWorldID stWorldID(record.wWorldLayerID, record.wWorldID);

				STeleportPos teleportPos(posInfo);

				pPC->TeleportTo(stWorldID, teleportPos);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Teleport, record.nID))
					printf("%s - WTF?! Failed to delete teleport delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverSkillPoints()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_SKILL_POINT_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantSkillPointRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain gold delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_SKILL_POINT_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_SKILL_POINT_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantSkillPointDbRecord record = (SInstantSkillPointDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->AddSkillPoints(record.nAmount);
				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::SkillPoint, record.nID))
					printf("%s - WTF?! Failed to delete skill points delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverExperience()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_EXPERIENCE_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantExperienceRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain gold delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_EXPERIENCE_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_EXPERIENCE_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantExperienceDbRecord record = (SInstantExperienceDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->AddExpPoints(record.qwLevelExperience, record.qwSkillExperience);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Experience, record.nID))
					printf("%s - WTF?! Failed to delete experience points delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverCharReload()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_CHAR_RELOAD_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantCharReloadRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain char reload delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_CHAR_RELOAD_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_CHAR_RELOAD_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantCharReloadDbRecord record = (SInstantCharReloadDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->TeleportToOwnPos();

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::CharReload, record.nID))
					printf("%s - WTF?! Failed to delete char reload delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
}
catch (...) {

}

	return true;
}


bool CDbTriggerActions::DeliverPvpState()
{
	try {

	
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_PVP_STATE_DB_RECORD_LST lstRecords;
	if (!pDbSet->GetInstantPvpStateRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain char reload delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_PVP_STATE_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_PVP_STATE_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantPvpStateDbRecord record = (SInstantPvpStateDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->SetPvpState(record.btState);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::PvpState, record.nID))
					printf("%s - WTF?! Failed to delete pvp state delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
	}
	catch (...) {

	}
	return true;

}

bool CDbTriggerActions::DeliverStatPoints()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_STAT_POINT_DB_RECORD_LST lstRecords;

	if (!pDbSet->GetInstantStatPointRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain free stat point delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_STAT_POINT_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_STAT_POINT_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantStatPointDbRecord record = (SInstantStatPointDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				//Can be delivered instantly, without reload.
				if (record.wStr > 0 || record.wInt > 0)
				{
					pPC->AddStrInt(record.wStr, record.wInt);
				}

				if (record.wFreeStatPoints > 0)
				{
					pPC->SetCurFreeStatPoints(pPC->GetCurFreeStatPoints() + record.wFreeStatPoints);
					pPC->TeleportToOwnPos();
				}

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::StatPoint, record.nID))
					printf("%s - WTF?! Failed to delete stat point delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
	}
	catch (...) {

	}
	return true;
}

bool CDbTriggerActions::DeliverHwanLevel()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_HWAN_LEVEL_DB_RECORD_LST lstRecords;

	if (!pDbSet->GetInstantHwanLevelRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain hwan level delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_HWAN_LEVEL_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_HWAN_LEVEL_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantHwanLevelDbRecord record = (SInstantHwanLevelDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->UpdateHwan(record.btLevel);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::HwanLevel, record.nID))
					printf("%s - WTF?! Failed to delete stat hwan level delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
	}
	catch (...) {

	}
	return true;
}

bool CDbTriggerActions::DeliverMobSpawnsNearPlayer()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_MOB_SPAWN_NEAR_PLAYER_DB_RECORD_LST lstRecords;

	if (!pDbSet->GetInstantMobSpawnNearPlayerRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain mob spawn near player records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_MOB_SPAWN_NEAR_PLAYER_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_MOB_SPAWN_NEAR_PLAYER_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantMobSpawnNearPlayerDbRecord record = (SInstantMobSpawnNearPlayerDbRecord)(*itCur);
		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				CObjMgr::SpawnMonsterNearPlayer(pPC, record.btType, record.fltRange, record.dwRefObjID);
				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::MobSpawnNearPlayer, record.nID))
					printf("%s - WTF?! Failed to delete mob spawn near player delivery record id %d, char id %d\n", __FUNCTION__, record.nID, record.nCharID);
			}
		}
	}
	}
	catch (...) {

	}
	return true;
}

bool CDbTriggerActions::DeliverMobSpawnsAtPos()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_MOB_SPAWN_AT_POS_DB_RECORD_LST lstRecords;

	if (!pDbSet->GetInstantMobSpawnAtPosRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain mob spawn at pos records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_MOB_SPAWN_AT_POS_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_MOB_SPAWN_AT_POS_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantMobSpawnAtPosDbRecord record = (SInstantMobSpawnAtPosDbRecord)(*itCur);

		SPosInfoForMobSpawn* pPosInfo = new SPosInfoForMobSpawn(
			record.wRegionID, record.fltPosX, record.fltPosY, record.fltPosZ
		);

		SWorldID sWorldID(record.wWorldLayerID, record.wWorldID);
		CObjMgr::SpawnMonster(pPosInfo, record.btMobType, record.fltRange, record.dwRefObjID, sWorldID);
	//	printf ("ID: %d |MobID : %d", record.nID,record.dwRefObjID);
		if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::MobSpawnAtPos, record.nID))
			printf("%s - WTF?! Failed to delete mob spawn at pos delivery record id %d\n", __FUNCTION__, record.nID);
	}
	}
	catch (...) {

	}
	return true;
}

bool CDbTriggerActions::DeliverBuffs()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_BUFFS_DB_RECORD_LST lstRecords;

	if (!pDbSet->GetInstantBuffsRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain instant buffs delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_BUFFS_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_BUFFS_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantBuffsDbRecord record = (SInstantBuffsDbRecord)(*itCur);

		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				CObjMgr::EngageBuffSkill(pPC, record.szCodeName128);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Buffs, record.nID))
					printf("%s - WTF?! Failed to delete instant buff delivery record id %d\n", __FUNCTION__, record.nID);
			}
		}
	}
	}
	catch (...) {

	}
	return true;
}

bool CDbTriggerActions::DeliverBuffs1()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_BUFFS1_DB_RECORD_LST lstRecords;

	if (!pDbSet->GetInstantBuffs1Records(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain instant buffs delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_BUFFS1_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_BUFFS1_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantBuffs1DbRecord record = (SInstantBuffs1DbRecord)(*itCur);

		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				CObjMgr::EngageBuffSkill1(pPC, record.nSkillID, record.nTime);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Buffs1, record.nID))
					printf("%s - WTF?! Failed to delete instant buff delivery record id %d\n", __FUNCTION__, record.nID);
			}
		}
	}
	}
	catch (...) {

	}
	return true;
}
bool CDbTriggerActions::DeliverBerserker()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_ZERK_DB_RECORD_LST lstRecords;

	if (!pDbSet->GetInstantZerkRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain instant berserker delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_ZERK_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_ZERK_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantZerkDbRecord record = (SInstantZerkDbRecord)(*itCur);

		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->UpdateZerkLevel(record.nPoints);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Berserker, record.nID))
					printf("%s - WTF?! Failed to delete zerk delivery record id %d\n", __FUNCTION__, record.nID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

bool CDbTriggerActions::DeliverSilk()
{
	try{
	CDbTriggerActionDBSet* pDbSet = CDbMgr::GetDbTriggerActionDbSet();

	__DBSET_INSTANT_SILK_DB_RECORD_LST lstRecords;

	if (!pDbSet->GetInstantSilkRecords(lstRecords))
	{
		std::cout << __FUNCTION__ << " - Failed to obtain instant silk delivery records" << std::endl;
		return false;
	}

	__DBSET_INSTANT_SILK_DB_RECORD_LST_IT itCur = lstRecords.begin();
	__DBSET_INSTANT_SILK_DB_RECORD_LST_IT itEnd = lstRecords.end();

	for (; itCur != itEnd; itCur++)
	{
		SInstantSilkDbRecord record = (SInstantSilkDbRecord)(*itCur);

		CGObjPC* pPC = CObjMgr::GetPlayerByDBID(record.nCharID);

		if (pPC != NULL)
		{
			if (pPC->CanSendMessage())
			{
				pPC->UpdateSilk(record.nSilk, record.nSilkGift, record.nSilkPoint, record.bSendPacket);

				if (!pDbSet->DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Silk, record.nID))
					printf("%s - WTF?! Failed to delete silk delivery record id %d\n", __FUNCTION__, record.nID);
			}
		}
	}
}
catch (...) {

}
	return true;
}

//DWORD WINAPI DeliveryWorker(LPVOID lpParam)
void DeliveryWorker()
{
	SDbTriggerActionsConfig* pstConfig = CConfigMgr::GetDbTriggerActionsConfig();

	//int nDeliveryCount = 0;
	int nPollInterval = 2000;

	while (true)
	{
	//	DWORD dwStartTime = GetTickCount();
		try
		{
			Sleep(nPollInterval);

			if (pstConfig->bDeliverDamage)
				CDbTriggerActions::DeliverDamage();

			if (pstConfig->bDeliverItems)
				CDbTriggerActions::DeliverItems();

			if (pstConfig->bDeliverGold)
				CDbTriggerActions::DeliverGold();

			if (pstConfig->bDeliverTeleports)
				CDbTriggerActions::DeliverTeleports();

			if (pstConfig->bDeliverSkillPoints)
				CDbTriggerActions::DeliverSkillPoints();

			if (pstConfig->bDeliverExperience)
				CDbTriggerActions::DeliverExperience();

			if (pstConfig->bDeliverCharReload)
				CDbTriggerActions::DeliverCharReload();

			if (pstConfig->bDeliverPvpState)
				CDbTriggerActions::DeliverPvpState();

			if (pstConfig->bDeliverStatPoints)
				CDbTriggerActions::DeliverStatPoints();

			if (pstConfig->bDeliverHwanLevel)
				CDbTriggerActions::DeliverHwanLevel();

			if (pstConfig->bDeliverMobSpawnNearPlayer)
				CDbTriggerActions::DeliverMobSpawnsNearPlayer();

			if (pstConfig->bDeliverMobSpawnAtPos)
				CDbTriggerActions::DeliverMobSpawnsAtPos();

			if (pstConfig->bDeliverBuffs)
				CDbTriggerActions::DeliverBuffs();

			if (pstConfig->bDeliverBuffsByID)
				CDbTriggerActions::DeliverBuffs1();

			if (pstConfig->bDeliverZerk)
				CDbTriggerActions::DeliverBerserker();

			if (pstConfig->bDeliverSilk)
				CDbTriggerActions::DeliverSilk();

			if (pstConfig->bDeliverUpdateItem)
				CDbTriggerActions::DeliverUpdateItem();

			if (pstConfig->bDeliverDropItem)
				CDbTriggerActions::DeliverDropItem();
		}
		catch (const std::exception& ex)
		{
			printf("%s error reason %s\n", __FUNCTION__, ex.what());

		}
		

		//	++nDeliveryCount;
	//	DWORD dwDelay = (GetTickCount() - dwStartTime);

		//if (pstConfig->bEnableDelayReportMsg)
		//	printf("[%d] Delivery delay = %d ticks (%d ms)\n", nDeliveryCount, dwDelay, (dwDelay - nDeliveryCount));
	}

}

bool CDbTriggerActions::Initialize()
{
	return true;
}


bool CDbTriggerActions::StartDelivering()
{
	//assert(s_hDeliveryThread == NULL && "DB trigger action delivery worker already started");
	//s_hDeliveryThread = CreateThread(NULL, 0, DeliveryWorker, NULL, 0, NULL);
	try
	{
		std::thread t1(DeliveryWorker);
		t1.join();

	}
	catch (const std::exception& ex)
	{
		printf("%s error reason %s\n", __FUNCTION__, ex.what());

	}
	

	return true;
}

void CDbTriggerActions::StopDelivering()
{
	if (s_hDeliveryThread != NULL)
	{
		TerminateThread(s_hDeliveryThread, 0);
	}
}