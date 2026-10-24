#include "pch.h"
#include "DbTriggerActionDBSet.h"
#include "ConfigMgr.h"

CDbTriggerActionDBSet::CDbTriggerActionDBSet(CDbConnection* pConn, CAutoCriticalSection* pACS)
{
	m_pDbConnection = pConn;
	m_pACS = pACS;
}

CDbTriggerActionDBSet::~CDbTriggerActionDBSet()
{

}

bool CDbTriggerActionDBSet::GetInstantDmgRecords(__DBSET_INSTANT_DMG_DB_RECORD_LST& result)
{
	try {
		SQLHANDLE hStmt = SQL_NULL_HSTMT;

		if (!m_pDbConnection->AllocStmt(hStmt))
		{
			std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
			m_pDbConnection->FreeStmt(hStmt);
			return false;
		}

		SQLRETURN retCode;
		char szQuery[1024] = { 0 };
		sprintf(szQuery,
			"SELECT ID, CharID, ReasonMask, Amount FROM %s ",
			GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Damage).c_str());

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
			SInstantDmgDbRecord record;
			ZeroMemory(&record, sizeof(SInstantDmgDbRecord));

			SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
			SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
			SQLGetData(hStmt, 3, SQL_C_LONG, (SQLPOINTER)&record.nReasonMask, 0, &cb);
			SQLGetData(hStmt, 4, SQL_C_LONG, (SQLPOINTER)&record.nAmount, 0, &cb);

			result.push_back(record);
			retCode = SQLFetch(hStmt);
		} while (SQL_SUCCEEDED(retCode));

		m_pDbConnection->FreeStmt(hStmt);

		m_pACS->Leave();
	}
	catch (...) {

	}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantUpdateItemRecords(__DBSET_INSTANT_UPDATE_ITEM_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, Slot, CodeName FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::UpdateItem).c_str());

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
		SInstantChangeItemDbRecord record;
		ZeroMemory(&record, sizeof(SInstantChangeItemDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_LONG, (SQLPOINTER)&record.nSlot, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_CHAR, (SQLPOINTER)&record.szCodename, sizeof(record.szCodename), &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);

	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantDropItemRecords(__DBSET_INSTANT_DROP_ITEM_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, CodeName, Count, Plus FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::DropItem).c_str());

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
		SInstantDropItemDbRecord record;
		ZeroMemory(&record, sizeof(SInstantDropItemDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_CHAR, (SQLPOINTER)&record.szCodename, sizeof(record.szCodename), &cb);
		SQLGetData(hStmt, 4, SQL_C_LONG, (SQLPOINTER)&record.nCount, 0, &cb);
		SQLGetData(hStmt, 5, SQL_C_LONG, (SQLPOINTER)&record.nPlus, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);

	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantItemRecords(__DBSET_INSTANT_ITEM_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, StorageType, CodeName, Count, Plus FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Item).c_str());

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
		SInstantItemDbRecord record;
		ZeroMemory(&record, sizeof(SInstantItemDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_TINYINT, (SQLPOINTER)&record.btStorageType, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_CHAR, (SQLPOINTER)&record.szCodename, sizeof(record.szCodename), &cb);
		SQLGetData(hStmt, 5, SQL_C_LONG, (SQLPOINTER)&record.nItemCount, 0, &cb);
		SQLGetData(hStmt, 6, SQL_C_TINYINT, (SQLPOINTER)&record.btPlusValue, 0, &cb);
		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();

	}
	catch (...) {

	}
	return true;
}


bool CDbTriggerActionDBSet::GetInstantGoldRecords(__DBSET_INSTANT_GOLD_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, Amount, ShowDeliveryMsg FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Gold).c_str());

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
		SInstantGoldDbRecord record;
		ZeroMemory(&record, sizeof(SInstantGoldDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_LONG, (SQLPOINTER)&record.nAmount, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_BIT, (SQLPOINTER)&record.bShowDeliveryMsg, 0, &cb);
		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantTeleportRecords(__DBSET_INSTANT_TELEPORT_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, WorldLayerID, WorldID, RegionID, PosX, PosY, PosZ FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Teleport).c_str());

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
		SInstantTeleportDbRecord record;
		ZeroMemory(&record, sizeof(SInstantGoldDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_USHORT, (SQLPOINTER)&record.wWorldLayerID, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_USHORT, (SQLPOINTER)&record.wWorldID, 0, &cb);
		SQLGetData(hStmt, 5, SQL_C_LONG, (SQLPOINTER)&record.wRegionID, 0, &cb);
		SQLGetData(hStmt, 6, SQL_C_FLOAT, (SQLPOINTER)&record.fltPosX, 0, &cb);
		SQLGetData(hStmt, 7, SQL_C_FLOAT, (SQLPOINTER)&record.fltPosY, 0, &cb);
		SQLGetData(hStmt, 8, SQL_C_FLOAT, (SQLPOINTER)&record.fltPosZ, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));


	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();

}
catch (...) {

}

	return true;
}

bool CDbTriggerActionDBSet::GetInstantSkillPointRecords(__DBSET_INSTANT_SKILL_POINT_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery, "SELECT ID, CharID, Amount FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::SkillPoint).c_str());

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
		SInstantSkillPointDbRecord record;
		ZeroMemory(&record, sizeof(SInstantSkillPointDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_LONG, (SQLPOINTER)&record.nAmount, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();

}
catch (...) {

}

	return true;
}

bool CDbTriggerActionDBSet::GetInstantExperienceRecords(__DBSET_INSTANT_EXPERIENCE_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, LevelExperience, SkillExperience FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Experience).c_str());

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
		SInstantExperienceDbRecord record;
		ZeroMemory(&record, sizeof(SInstantExperienceDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_SBIGINT, (SQLPOINTER)&record.qwLevelExperience, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_SBIGINT, (SQLPOINTER)&record.qwSkillExperience, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();

}
catch (...) {

}

	return true;
}


bool CDbTriggerActionDBSet::GetInstantCharReloadRecords(__DBSET_INSTANT_CHAR_RELOAD_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery, "SELECT ID, CharID FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::CharReload).c_str());

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
		SInstantCharReloadDbRecord record;
		ZeroMemory(&record, sizeof(SInstantCharReloadDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}

	return true;
}

bool CDbTriggerActionDBSet::GetInstantPvpStateRecords(__DBSET_INSTANT_PVP_STATE_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, State FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::PvpState).c_str());

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
		SInstantPvpStateDbRecord record;
		ZeroMemory(&record, sizeof(SInstantPvpStateDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_TINYINT, (SQLPOINTER)&record.btState, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();

}
catch (...) {

}

	return true;
}

bool CDbTriggerActionDBSet::GetInstantStatPointRecords(__DBSET_INSTANT_STAT_POINT_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, FreeStatPoints, Str, Int FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::StatPoint).c_str());

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
		SInstantStatPointDbRecord record;
		ZeroMemory(&record, sizeof(SInstantStatPointDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_SHORT, (SQLPOINTER)&record.wFreeStatPoints, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_SHORT, (SQLPOINTER)&record.wStr, 0, &cb);
		SQLGetData(hStmt, 5, SQL_C_SHORT, (SQLPOINTER)&record.wInt, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantHwanLevelRecords(__DBSET_INSTANT_HWAN_LEVEL_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, Level FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::HwanLevel).c_str());

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
		SInstantHwanLevelDbRecord record;
		ZeroMemory(&record, sizeof(SInstantHwanLevelDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_TINYINT, (SQLPOINTER)&record.btLevel, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantMobSpawnNearPlayerRecords(__DBSET_INSTANT_MOB_SPAWN_NEAR_PLAYER_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, Type, Range, RefObjID FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::MobSpawnNearPlayer).c_str());

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
		SInstantMobSpawnNearPlayerDbRecord record;
		ZeroMemory(&record, sizeof(SInstantMobSpawnNearPlayerDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_TINYINT, (SQLPOINTER)&record.btType, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_FLOAT, (SQLPOINTER)&record.fltRange, 0, &cb);
		SQLGetData(hStmt, 5, SQL_C_LONG, (SQLPOINTER)&record.dwRefObjID, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantMobSpawnAtPosRecords(__DBSET_INSTANT_MOB_SPAWN_AT_POS_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, ServerID, WorldLayerID, WorldID, RegionID, PosX, PosY, PosZ, MobType, Range, RefObjID FROM %s WHERE ServerID=%d",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::MobSpawnAtPos).c_str(),
		CConfigMgr::GetGameServerConfig()->nServerID
	);

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
		SInstantMobSpawnAtPosDbRecord record;
		ZeroMemory(&record, sizeof(SInstantMobSpawnAtPosDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nServerID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_SHORT, (SQLPOINTER)&record.wWorldLayerID, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_SHORT, (SQLPOINTER)&record.wWorldID, 0, &cb);
		SQLGetData(hStmt, 5, SQL_C_SHORT, (SQLPOINTER)&record.wRegionID, 0, &cb);
		SQLGetData(hStmt, 6, SQL_C_FLOAT, (SQLPOINTER)&record.fltPosX, 0, &cb);
		SQLGetData(hStmt, 7, SQL_C_FLOAT, (SQLPOINTER)&record.fltPosY, 0, &cb);
		SQLGetData(hStmt, 8, SQL_C_FLOAT, (SQLPOINTER)&record.fltPosZ, 0, &cb);
		SQLGetData(hStmt, 9, SQL_C_TINYINT, (SQLPOINTER)&record.btMobType, 0, &cb);
		SQLGetData(hStmt, 10, SQL_C_FLOAT, (SQLPOINTER)&record.fltRange, 0, &cb);
		SQLGetData(hStmt, 11, SQL_C_LONG, (SQLPOINTER)&record.dwRefObjID, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
		//printf("GetInstantMobSpawnAtPosRecords   ID: %d |MobID : %d", record.nID, record.dwRefObjID);

	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantBuffsRecords(__DBSET_INSTANT_BUFFS_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, CodeName128 FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Buffs).c_str());

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
		SInstantBuffsDbRecord record;
		ZeroMemory(&record, sizeof(SInstantBuffsDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_CHAR, (SQLPOINTER)&record.szCodeName128, sizeof(record.szCodeName128), &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantBuffs1Records(__DBSET_INSTANT_BUFFS1_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, SkillID,Time FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Buffs1).c_str());

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
		SInstantBuffs1DbRecord record;
		ZeroMemory(&record, sizeof(SInstantBuffs1DbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_LONG, (SQLPOINTER)&record.nSkillID, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_LONG, (SQLPOINTER)&record.nTime, 0, &cb);


		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::GetInstantZerkRecords(__DBSET_INSTANT_ZERK_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, Points FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Berserker).c_str());

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
		SInstantZerkDbRecord record;
		ZeroMemory(&record, sizeof(SInstantZerkDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_LONG, (SQLPOINTER)&record.nPoints, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}


bool CDbTriggerActionDBSet::GetInstantSilkRecords(__DBSET_INSTANT_SILK_DB_RECORD_LST& result)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		return false;
	}

	SQLRETURN retCode;
	char szQuery[1024] = { 0 };
	sprintf(szQuery,
		"SELECT ID, CharID, Silk, SilkGift, SilkPoint, SendPacket FROM %s ",
		GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Silk).c_str());

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
		SInstantSilkDbRecord record;
		ZeroMemory(&record, sizeof(SInstantSilkDbRecord));

		SQLGetData(hStmt, 1, SQL_C_LONG, (SQLPOINTER)&record.nID, 0, &cb);
		SQLGetData(hStmt, 2, SQL_C_LONG, (SQLPOINTER)&record.nCharID, 0, &cb);
		SQLGetData(hStmt, 3, SQL_C_LONG, (SQLPOINTER)&record.nSilk, 0, &cb);
		SQLGetData(hStmt, 4, SQL_C_LONG, (SQLPOINTER)&record.nSilkGift, 0, &cb);
		SQLGetData(hStmt, 5, SQL_C_LONG, (SQLPOINTER)&record.nSilkPoint, 0, &cb);
		SQLGetData(hStmt, 6, SQL_C_BIT, (SQLPOINTER)&record.bSendPacket, 0, &cb);

		result.push_back(record);
		retCode = SQLFetch(hStmt);
	} while (SQL_SUCCEEDED(retCode));

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}

bool CDbTriggerActionDBSet::DeleteInstantDeliveryRecords(E_INSTANT_DELIVERY_RECORD_TYPE::Enum type, int nID)
{
	std::string strTableName = GetTableNameByRecordType(type);
	DeleteRecordByDBID(nID, strTableName);

	return true;
}

std::string CDbTriggerActionDBSet::GetTableNameByRecordType(E_INSTANT_DELIVERY_RECORD_TYPE::Enum type)
{
	std::string name;

	switch (type)
	{
	case E_INSTANT_DELIVERY_RECORD_TYPE::Damage:
		name = "_InstantDmgDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::Item:
		name = "_InstantItemDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::Gold:
		name = "_InstantGoldDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::Teleport:
		name = "_InstantTeleportDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::SkillPoint:
		name = "_InstantSkillPointDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::Experience:
		name = "_InstantExperienceDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::CharReload:
		name = "_InstantCharReloadDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::PvpState:
		name = "_InstantPvpStateDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::StatPoint:
		name = "_InstantStatPointDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::HwanLevel:
		name = "_InstantHwanLevelDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::MobSpawnNearPlayer:
		name = "_InstantMobSpawnNearPlayerDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::MobSpawnAtPos:
		name = "_InstantMobSpawnAtPosDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::Buffs:
		name = "_InstantBuffsDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::Buffs1:
		name = "_InstantBuffsByIDAndTimeDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::Berserker:
		name = "_InstantZerkDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::Silk:
		name = "_InstantSilkDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::UpdateItem:
		name = "_InstantUpdateItemDelivery";
		break;
	case E_INSTANT_DELIVERY_RECORD_TYPE::DropItem:
		name = "_InstantDropItemDelivery";
		break;
	}

	return name;
}

bool CDbTriggerActionDBSet::DeleteRecordByDBID(int nID, const std::string& table)
{
	try{
	SQLHANDLE hStmt = SQL_NULL_HSTMT;

	if (!m_pDbConnection->AllocStmt(hStmt))
	{
		std::cout << __FUNCTION__ << " - Failed to allocate stmt" << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
	}


	const LPCSTR szQueryFormat = "DELETE FROM %s WHERE ID=%d";
	char szQuery[512] = { 0 };
	sprintf(szQuery, szQueryFormat, table.c_str(), nID);

	m_pACS->Enter();

	SQLRETURN retCode = SQLExecDirectA(hStmt, (SQLCHAR*)szQuery, SQL_NTS);

	if (!SQL_SUCCEEDED(retCode))
	{
		std::cout << __FUNCTION__ << " - SQLExecDirect failed, query = " << szQuery << std::endl;
		m_pDbConnection->FreeStmt(hStmt);
		m_pACS->Leave();
		return false;
	}

	m_pDbConnection->FreeStmt(hStmt);
	m_pACS->Leave();
}
catch (...) {

}
	return true;
}