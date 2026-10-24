#pragma once
#include "pch.h"
#include "DbConnection.h"
#include "AutoCriticalSection.h"

struct SHideNameRegionDbRecord
{
	int nID;
	WORD wRegionID;
};


#define __DBSET_HIDE_NAME_REGION_DB_RECORD_LST			std::list<SHideNameRegionDbRecord>
#define __DBSET_HIDE_NAME_REGION_DB_RECORD_LST_IT		__DBSET_HIDE_NAME_REGION_DB_RECORD_LST::iterator

class CRegionRestrictionDBSet
{
private:
	CDbConnection* m_pDbConnection;
	CAutoCriticalSection* m_pACS;
public:
	CRegionRestrictionDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS);
	~CRegionRestrictionDBSet();

	bool GetHideNameRegionRecords(__DBSET_HIDE_NAME_REGION_DB_RECORD_LST& result);
};