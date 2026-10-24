#include "pch.h"
#include "SettingsDBSet.h"

CSettingsDBSet::CSettingsDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS)
{
	m_pDbConnection = pConn;
	m_pACS = pACS;
}

CSettingsDBSet::~CSettingsDBSet()
{

}

bool CSettingsDBSet::GetCustomNpcInteractionRecords(__DBSET_CUSTOM_NPC_INTERACTION_DB_RECORD_LST& result)
{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	const LPCSTR szQuery = "SELECT ID, CodeName128, InteractionID FROM _CustomNpcInteraction";

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

	do
	{
		SCustomNpcInteractionDbRecord record;
		ZeroMemory(&record, sizeof(SCustomNpcInteractionDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_CHAR, (SQLPOINTER)&record.szCodeName128, sizeof(record.szCodeName128), &cb);
		SQLGetData(hStmt, 3, SQL_C_LONG, (SQLPOINTER)&record.nInteractionID, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
	return true;
}
