#pragma once
#include "pch.h"
#include "DbConnection.h"
#include "DbTriggerActionDBSet.h"
#include "RegionRestrictionDBSet.h"
#include "SettingsDBSet.h"
#include "MiscDBSet.h"
#include "FilterContentDBSet.h"

class CDbMgr
{
private:
	//static CDbConnection* s_pAddonDbConnection;
	static CDbConnection* s_pFilterContentDbConnection;
	static CDbTriggerActionDBSet* s_pDbTriggerActionDbSet;
	static CRegionRestrictionDBSet* s_pRegionRestrictionDbSet;
	static CSettingsDBSet* s_pSettingsDbSet;
	static CMiscDBSet* s_pMiscDbSet;
	static CFilterContentDBSet* s_pFilterContentDbSet;
public:
	static bool Initialize();
	//static CDbConnection* GetAddonDbConnection();
	static CDbConnection* GetFilterContentDbConnection();
	static CDbTriggerActionDBSet* GetDbTriggerActionDbSet();
	static CRegionRestrictionDBSet* GetRegionRestrictionDbSet();
	static CSettingsDBSet* GetSettingsDbSet();
	static CMiscDBSet* GetMiscDbSet();
	static CFilterContentDBSet* GetFilterContentDbSet();
};