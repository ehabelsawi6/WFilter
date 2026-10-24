#pragma once
#include "pch.h"
#include "DbConnection.h"
#include "AutoCriticalSection.h"

struct SCustomNpcInteractionDbRecord
{
	int nID;
	char szCodeName128[128];
	int nInteractionID;
};

#define __DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST		std::list<SCustomNpcInteractionDbRecord>
#define __DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST_IT		__DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST::iterator

class CSettingsDBSet
{
private:
	CDbConnection* m_pDbConnection;
	CAutoCriticalSection* m_pACS;
public:
	CSettingsDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS);
	~CSettingsDBSet();

	bool GetCustomNpcInteractionRecords(__DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST& result);
};