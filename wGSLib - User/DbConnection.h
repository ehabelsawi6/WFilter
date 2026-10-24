#pragma once
#include "pch.h"

class CDbConnection
{
private:
	std::string m_strConnStr;
	SQLHANDLE m_hEnv;
	SQLHANDLE m_hConn;
public:
	CDbConnection(std::string strConnStr);
	virtual ~CDbConnection();

	bool Connect();
	void Disconnect();

	SQLHANDLE GetEnvHandle() const;
	SQLHANDLE GetConnHandle() const;
	std::string GetConnString() const;

	bool AllocStmt(SQLHANDLE& hStmt);
	bool FreeStmt(SQLHANDLE& hStmt);
};