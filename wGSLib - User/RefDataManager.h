#pragma once
#include "pch.h"

struct SUniqueMonsterInfo;
struct SFortressHeartInfo;

#define __UNIQUE_INFO_LST                               std::list<SUniqueMonsterInfo>
#define __UNIQUE_INFO_LST_IT                            __UNIQUE_INFO_LST::iterator

#define __FORTRESSHEART_INFO_LST                               std::list<SFortressHeartInfo>
#define __FORTRESSHEART_INFO_LST_IT                            __FORTRESSHEART_INFO_LST::iterator

class CRefObj;

class CRefDataManager
{
private:
	static __UNIQUE_INFO_LST s_lstUniqueInfo;
	static __FORTRESSHEART_INFO_LST s_lstFortressHeartInfo;

public:
	static bool LoadUniqueInfo();
	static bool LoadFortressInfo();
	static bool IsUniqueMonster(int dwObjID);
	static bool IsFortressHeartStruct(int dwObjID);
	static SUniqueMonsterInfo GetUniqueMonsterInfoByRefObjID(int dwObjID);
	static CRefObj* GetRefObjByID(int dwObjID);
};