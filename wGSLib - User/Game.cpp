#include "pch.h"
#include "Game.h"

#define GET_OBJ_BY_ID_FN_OFFSET		0x00485D90

CGame::FN_GET_OBJ_BY_GAME_ID CGame::s_pfnGetObjByGameID;

void CGame::Initialize()
{
	s_pfnGetObjByGameID = reinterpret_cast<FN_GET_OBJ_BY_GAME_ID>(
		GET_OBJ_BY_ID_FN_OFFSET
		);
}

IGObj* CGame::GetObjByGameID(DWORD dwObjID)
{
	return s_pfnGetObjByGameID(dwObjID);
}