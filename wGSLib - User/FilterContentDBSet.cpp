#include "pch.h"
#include "FilterContentDBSet.h"

CFilterContentDBSet::CFilterContentDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS)
{
	m_pDbConnection = pConn;
	m_pACS = pACS;
}

CFilterContentDBSet::~CFilterContentDBSet()
{

}

bool CFilterContentDBSet::GetUniqueMonsterInfos(__DBSET_UNIQUE_MONSTER_INFO_LST& result)
{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	//sprintf(szQuery,"SELECT RefObjID FROM %s","_GetUniqueMonsters()");
	sprintf(szQuery, "SELECT RefObjID FROM _GetUniqueMonsters");

	m_pACS->Enter();

	retCode = SQLExecDirectA(hStmt, (SQLCHAR*)szQuery, SQL_NTS);
	if (!SQL_SUCCEEDED(retCode))
	{
		std::cout << __FUNCTION__ << " - SQLExecDirect failed, query = " << szQuery << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return false;
	}

	retCode = SQLFetch(hStmt);

	if (retCode == SQL_NO_DATA)
	{
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return true;
	}

	if (!SQL_SUCCEEDED(retCode))
	{
		std::cout << __FUNCTION__ << " - SQLFetch failed, query = " << szQuery << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return false;
	}

	SQLINTEGER cb;

	int id = 0;

	do
	{
		SUniqueMonsterInfo record;
		ZeroMemory(&record, sizeof(SUniqueMonsterInfo));

		record.nID = id++;
		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.RefObjID, 0, &cb);
		//SQLGetData(hStmt, 2, SQL_C_CHAR, (SQLPOINTER)&record.szCodeName128, sizeof(record.szCodeName128), &cb);
		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
	return true;
}


bool CFilterContentDBSet::GetFortressHeartInfos(__DBSET_FORTRESS_HEART_INFO_LST& result)
{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,"SELECT RefObjID FROM %s","_GetFortressHearts()");

	m_pACS->Enter();

	retCode = SQLExecDirectA(hStmt, (SQLCHAR*)szQuery, SQL_NTS);
	if (!SQL_SUCCEEDED(retCode))
	{
		std::cout << __FUNCTION__ << " - SQLExecDirect failed, query = " << szQuery << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return false;
	}

	retCode = SQLFetch(hStmt);

	if (retCode == SQL_NO_DATA)
	{
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return true;
	}

	if (!SQL_SUCCEEDED(retCode))
	{
		std::cout << __FUNCTION__ << " - SQLFetch failed, query = " << szQuery << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return false;
	}

	SQLINTEGER cb;

	int id = 0;

	do
	{
		SFortressHeartInfo record;
		ZeroMemory(&record, sizeof(SFortressHeartInfo));

		record.nID = id++;
		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.RefObjID, 0, &cb);
		//SQLGetData(hStmt, 2, SQL_C_CHAR, (SQLPOINTER)&record.szCodeName128, sizeof(record.szCodeName128), &cb);
		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
	return true;
}
