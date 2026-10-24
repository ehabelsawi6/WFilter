#pragma once
#include "pch.h"

class CDbTriggerActions
{
private:
	static HANDLE s_hDeliveryThread;
public:
	static bool Initialize();
	static bool StartDelivering();
	static void StopDelivering();

	static bool DeliverDamage();
	static bool DeliverUpdateItem();
	static bool DeliverDropItem();
	static bool DeliverItems();
	static bool DeliverGold();
	static bool DeliverTeleports();
	static bool DeliverSkillPoints();
	static bool DeliverExperience();
	static bool DeliverCharReload();
	static bool DeliverPvpState();
	static bool DeliverStatPoints();
	static bool DeliverHwanLevel();
	static bool DeliverMobSpawnsNearPlayer();
	static bool DeliverMobSpawnsAtPos();
	static bool DeliverBuffs();
	static bool DeliverBuffs1();
	static bool DeliverBerserker();
	static bool DeliverSilk();
};