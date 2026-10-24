#pragma once
#include "pch.h"
#include "DbConnection.h"
#include "AutoCriticalSection.h"


class CMiscDBSet
{
private:
	CDbConnection* m_pDbConnection;
	CAutoCriticalSection* m_pACS;

public:
	CMiscDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS);
	~CMiscDBSet();


	bool CallUniqueEnteredSP(char* szUniqueName);
	bool CallUniqueKilledSP(char* szUniqueName, char* szKillerName);
	bool CallGameServerStartedSP();
};