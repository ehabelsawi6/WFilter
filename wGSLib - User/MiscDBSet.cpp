#include "pch.h"
#include "MiscDBSet.h"
#include "ConfigMgr.h"

CMiscDBSet::CMiscDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS)
{
	m_pDbConnection = pConn;
	m_pACS = pACS;
}

CMiscDBSet::~CMiscDBSet()
{

}

bool CMiscDBSet::CallUniqueEnteredSP(char* szUniqueName)
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
	sprintf(szQuery, "EXEC _OnUniqueEntered '%s'", szUniqueName);

	m_pACS->Enter();

	retCode = SQLExecDirectA(hStmt, (SQLCHAR*)szQuery, SQL_NTS);
	if (!SQL_SUCCEEDED(retCode))
	{
		std::cout << __FUNCTION__ << " - SQLExecDirect failed, query = " << szQuery << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return false;
	}

	m_pDbConnection->FreeStmt(hStmt);

	m_pACS->Leave();

	return true;
}

bool CMiscDBSet::CallUniqueKilledSP(char* szUniqueName, char* szKillerName)
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
	sprintf(szQuery, "EXEC _OnUniqueKilled '%s', '%s'", szUniqueName, szKillerName);

	m_pACS->Enter();

	retCode = SQLExecDirectA(hStmt, (SQLCHAR*)szQuery, SQL_NTS);
	if (!SQL_SUCCEEDED(retCode))
	{
		std::cout << __FUNCTION__ << " - SQLExecDirect failed, query = " << szQuery << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return false;
	}

	m_pDbConnection->FreeStmt(hStmt);

	m_pACS->Leave();

	return true;
}

bool CMiscDBSet::CallGameServerStartedSP()
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
	sprintf(szQuery, "EXEC _OnGameServerStarted %d", CConfigMgr::GetGameServerConfig()->nServerID);

	m_pACS->Enter();

	retCode = SQLExecDirectA(hStmt, (SQLCHAR*)szQuery, SQL_NTS);
	if (!SQL_SUCCEEDED(retCode))
	{
		std::cout << __FUNCTION__ << " - SQLExecDirect failed, query = " << szQuery << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return false;
	}

	m_pDbConnection->FreeStmt(hStmt);

	m_pACS->Leave();

	return true;
}