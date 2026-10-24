#pragma once
#include "pch.h"

class CMsgStreamBuffer;
class CMassiveMsg;

/*
#define __MSG_HANDLER_MAP			std::map<__int16, CMainProcess::FN_MSG_HANDLER>
#define __MSG_HANDLER_MAP_IT		__MSG_HANDLER_MAP::iterator
*/

//They use this dynamic type shit for this one too... lol. 
//.rdata:00B4038C ; const ServerFramework::CServerProcessOverlap::`vftable'
//.rdata:00ADEFFC vftable         dd offset DEC_CMainProcess_fn_0_GetTypename_sub_4025E0

class CMainProcess
{
public:
	typedef void* (__thiscall* FN_MSG_HANDLER)(CMainProcess*, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg);

	static void Initialize();
	static CMainProcess* GetInstance();
	static void RegisterMsgHandler(__int16 msgID, FN_MSG_HANDLER handler);

private:
	//ServerFramework::CServerProcessBase::SetHandler -> 0094CBE0 (vft)
	
	typedef CMainProcess* (__stdcall* FN_GET_INSTANCE)();

	//VFT FN 7 ?
	typedef __int16(__thiscall* FN_SET_MSG_HANDLER)(CMainProcess*, __int16 id, void* handler);

	typedef int(__thiscall* FN_HANDLE_MSG)(
		CMainProcess*, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
		);

	static FN_SET_MSG_HANDLER s_pfnSetMsgHandler;
	static FN_HANDLE_MSG s_pfnHandleMsg;
	static FN_GET_INSTANCE s_pfnGetInstance;
	//static __MSG_HANDLER_MAP s_mapMsgHandlers;


	//static FN_MSG_HANDLER s_pfnCustomMsgHandler;

	static __int16 __fastcall MySetMsgHandler(CMainProcess* self, void* /* dummy edx */, __int16 id, void* handler);

	static int __fastcall MyHandleMsg(
		CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
	);

	/*
	static void* __fastcall MyFilterMsgHandler(
		CMainProcess* self, void* /* dummy edx * /, CMsgStreamBuffer* pMsg, int a3, int a4, int a5
	);
	*/

	//static void* __fastcall MyCustomMsgHandler(
	//	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, int a3, int a4, int a5
	//);
	

};