#pragma once
#include "pch.h"

class IGObj;

class CGame
{
private:
	typedef IGObj* (__cdecl* FN_GET_OBJ_BY_GAME_ID)(DWORD dwObjID);
	static FN_GET_OBJ_BY_GAME_ID s_pfnGetObjByGameID;

public:
	static void Initialize();
	static IGObj* GetObjByGameID(DWORD dwObjID);
};