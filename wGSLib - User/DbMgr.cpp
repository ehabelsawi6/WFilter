#include "pch.h"
#include "DbMgr.h"

#include "ConfigMgr.h"

//CDbConnection* CDbMgr::s_pAddonDbConnection;
CDbConnection* CDbMgr::s_pFilterContentDbConnection;
CDbTriggerActionDBSet* CDbMgr::s_pDbTriggerActionDbSet;
CRegionRestrictionDBSet* CDbMgr::s_pRegionRestrictionDbSet;
CSettingsDBSet* CDbMgr::s_pSettingsDbSet;
CMiscDBSet* CDbMgr::s_pMiscDbSet;
CFilterContentDBSet* CDbMgr::s_pFilterContentDbSet;


bool CDbMgr::Initialize()
{
	SGameServerConfig* pstGameServerConfig = CConfigMgr::GetGameServerConfig();
	//std::cout << pstGameServerConfig->strFilterContentDbConn << std::endl ;
	//s_pAddonDbConnection = new CDbConnection(pstGameServerConfig->strAddonDbConn);
	s_pFilterContentDbConnection = new CDbConnection(pstGameServerConfig->strFilterContentDbConn);

	//if (!s_pAddonDbConnection->Connect())
	//{
	//	std::cout << __FUNCTION__ << " - Failed to connect to the addon DB" << std::endl;
	//	s_pAddonDbConnection->Disconnect();
	//	return false;
	//}

	if (!s_pFilterContentDbConnection->Connect())
	{
		std::cout << __FUNCTION__ << " - Failed to connect to the filter content DB" << std::endl;
		//s_pAddonDbConnection->Disconnect();
		s_pFilterContentDbConnection->Disconnect();
		return false;
	}

	CAutoCriticalSection* pACS = new CAutoCriticalSection();

	s_pDbTriggerActionDbSet = new CDbTriggerActionDBSet(s_pFilterContentDbConnection, pACS);
	s_pRegionRestrictionDbSet = new CRegionRestrictionDBSet(s_pFilterContentDbConnection, pACS);
	s_pSettingsDbSet = new CSettingsDBSet(s_pFilterContentDbConnection, pACS);
	s_pMiscDbSet = new CMiscDBSet(s_pFilterContentDbConnection, pACS);
	s_pFilterContentDbSet = new CFilterContentDBSet(s_pFilterContentDbConnection, pACS);
	return true;
}

//CDbConnection* CDbMgr::GetAddonDbConnection()
//{
//	//return s_pAddonDbConnection;
//	return s_pFilterContentDbConnection;
//}


CDbConnection* CDbMgr::GetFilterContentDbConnection()
{
	return s_pFilterContentDbConnection;
}

CDbTriggerActionDBSet* CDbMgr::GetDbTriggerActionDbSet()
{
	return s_pDbTriggerActionDbSet;
}

CRegionRestrictionDBSet* CDbMgr::GetRegionRestrictionDbSet()
{
	return s_pRegionRestrictionDbSet;
}

CSettingsDBSet* CDbMgr::GetSettingsDbSet()
{
	return s_pSettingsDbSet;
}

CMiscDBSet* CDbMgr::GetMiscDbSet()
{
	return s_pMiscDbSet;
}

CFilterContentDBSet* CDbMgr::GetFilterContentDbSet()
{
	return s_pFilterContentDbSet;
}