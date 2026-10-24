#pragma once
#include "pch.h"
#include "DbConnection.h"
#include "AutoCriticalSection.h"

struct SUniqueMonsterInfo
{
	int nID;
	int RefObjID;
	//char szCodeName128[128];
};

struct SFortressHeartInfo
{
	int nID;
	int RefObjID;
	//char szCodeName128[128];
};

#define __DBSET_UNIQUE_MONSTER_INFO_LST				std::list<SUniqueMonsterInfo>
#define __DBSET_UNIQUE_MONSTER_INFO_LST_IT			__DBSET_INSTANT_DMG_DB_RECORD_LST::iterator

#define __DBSET_FORTRESS_HEART_INFO_LST				std::list<SFortressHeartInfo>
#define __DBSET_FORTRESS_HEART_INFO_LST_IT			__DBSET_FORTRESS_HEART_INFO_LST::iterator


class CFilterContentDBSet
{
private:
	CDbConnection* m_pDbConnection;
	CAutoCriticalSection* m_pACS;

public:
	CFilterContentDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS);
	~CFilterContentDBSet();

	bool GetUniqueMonsterInfos(__DBSET_UNIQUE_MONSTER_INFO_LST& result);
	bool GetFortressHeartInfos(__DBSET_FORTRESS_HEART_INFO_LST& result);
};