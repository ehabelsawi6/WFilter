#include "pch.h"
#include "RefDataManager.h"
#include "DbMgr.h"

#define GET_REF_OBJ_BY_OBJ_ID_FUNC_OFFSET					0x004260B0
#define REF_OBJ_MGR_FIRST_REF_OFFSET						0x00D16C80			


__UNIQUE_INFO_LST CRefDataManager::s_lstUniqueInfo;

__FORTRESSHEART_INFO_LST CRefDataManager::s_lstFortressHeartInfo;

bool CRefDataManager::LoadUniqueInfo()
{
	CFilterContentDBSet* pDbSet = CDbMgr::GetFilterContentDbSet();
	bool loaded = pDbSet->GetUniqueMonsterInfos(s_lstUniqueInfo);
	std::cout << __FUNCTION__ << " - Loaded " << s_lstUniqueInfo.size() << " records." << std::endl;
	return loaded;
}


bool CRefDataManager::LoadFortressInfo()
{
	CFilterContentDBSet* pDbSet = CDbMgr::GetFilterContentDbSet();
	bool loaded = pDbSet->GetFortressHeartInfos(s_lstFortressHeartInfo);
	std::cout << __FUNCTION__ << " - Loaded " << s_lstFortressHeartInfo.size() << " records." << std::endl;
	return loaded;
}

bool CRefDataManager::IsUniqueMonster(int dwObjID)
{
	__UNIQUE_INFO_LST_IT cur = s_lstUniqueInfo.begin();
	__UNIQUE_INFO_LST_IT end = s_lstUniqueInfo.end();

	while (cur != end)
	{
		SUniqueMonsterInfo record = *cur;

		if (record.RefObjID == dwObjID)
			return true;

		++cur;
	}
	return false;
}

bool CRefDataManager::IsFortressHeartStruct(int dwObjID)
{
	__FORTRESSHEART_INFO_LST_IT cur = s_lstFortressHeartInfo.begin();
	__FORTRESSHEART_INFO_LST_IT end = s_lstFortressHeartInfo.end();

	while (cur != end)
	{
		SFortressHeartInfo record = *cur;

		if (record.RefObjID == dwObjID)
			return true;

		++cur;
	}
	return false;
}

SUniqueMonsterInfo CRefDataManager::GetUniqueMonsterInfoByRefObjID(int dwObjID)
{
	__UNIQUE_INFO_LST_IT cur = s_lstUniqueInfo.begin();
	__UNIQUE_INFO_LST_IT end = s_lstUniqueInfo.end();

	while (cur != end)
	{
		SUniqueMonsterInfo record = *cur;

		if (record.RefObjID == dwObjID)
			return record;

		++cur;
	}
}

//0x00D6AA14 - set of objects, that one is for npcs 
//(first one = 0x00D16C80), we use it for mobs. there are more...
CRefObj* CRefDataManager::GetRefObjByID(int dwObjID)
{
	CRefDataManager* pRef = reinterpret_cast<CRefDataManager*>(REF_OBJ_MGR_FIRST_REF_OFFSET);

	CRefObj* pResult = NULL;
	DWORD dwCallAddr = GET_REF_OBJ_BY_OBJ_ID_FUNC_OFFSET;

	__asm push dwObjID;
	__asm mov edi, REF_OBJ_MGR_FIRST_REF_OFFSET;
	__asm call dwCallAddr;
	__asm mov pResult, eax;

	return pResult;
}