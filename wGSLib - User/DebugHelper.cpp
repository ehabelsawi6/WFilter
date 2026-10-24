#include "pch.h"
//#include "pch.h"
//#include "DebugHelper.h"
//#include "ConfigMgr.h"
//#include "ObjMgr.h"
//
//#define TOP_LEVEL_EXCEPTION_FILTER_HOOK_OFFSET						0x0095CB00
//#define ENDLESS_LOOP_CHECKER_HOOK_OFFSET							0x00401390
//#define TOP_LEVEL_EXCEPTION_MINIDUMP_WRITER_FUNC_OFFSET				0x0095C4E0
//
//#pragma pack(push, 4)
//struct STopLevelExceptionDumpWriterParams
//{
//	DWORD dwThreadID;
//	_EXCEPTION_POINTERS* pException;
//};
//#pragma pack(pop)
//
//typedef BOOL(WINAPI* fnIsDebuggerPresent)();
//typedef DWORD(WINAPI* fnTopLevelExceptionFilter)(struct _EXCEPTION_POINTERS* pExceptionInfo);
//typedef DWORD(WINAPI* fnEndlessLoopChecker)(LPVOID lpThreadParam);
//typedef DWORD(WINAPI* fnWriteTopLevelExceptionMinidump)(struct STopLevelExceptionDumpWriterParams* pParams);
//
//fnIsDebuggerPresent pfnIsDebuggerPresent = NULL;
//fnTopLevelExceptionFilter pfnTopLevelExceptionFilter = NULL;
//fnEndlessLoopChecker pfnEndlessLoopChecker = NULL;
//fnWriteTopLevelExceptionMinidump pfnWriteTopLevelExceptionMinidump = NULL;
//
//BOOL WINAPI MyIsDebuggerPresent()
//{
//	printf("IsDebuggerPresent entered\n");
//
//	return TRUE;
//}
//
//BOOL WINAPI MyTopLevelExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo)
//{
//	SDebugConfig* pConfig = CConfigMgr::GetDebugConfig();
//
//	std::string exRecordInfo = CDebugHelper::DumpExceptionRecord(pExceptionInfo->ExceptionRecord);
//	std::string exContextInfo = CDebugHelper::DumpExceptionContext(pExceptionInfo->ContextRecord);
//	//std::string stackDump = CDebugHelper::DumpStack(0x128);
//
//	std::stringstream ss;
//	ss << "==========================================" << std::endl;
//	ss << exRecordInfo << std::endl;
//	ss << "==========================================" << std::endl;
//	ss << exContextInfo << std::endl;
//	ss << "==========================================" << std::endl;
//	//ss << stackDump << std::endl;
//	//ss << "==========================================" << std::endl;
//
//	if (pConfig->bMinidumpOnTopLevelException)
//	{
//		STopLevelExceptionDumpWriterParams params;
//
//		params.dwThreadID = GetCurrentThreadId();
//		params.pException = pExceptionInfo;
//
//		pfnWriteTopLevelExceptionMinidump(&params);
//
//		ss << "Mini dump has been writen" << std::endl;
//	}
//
//	ss << "Call some highly trained squirrel to fix this unfortunate issue :( someone like bedo. -_-" << std::endl;
//
//	std::cout << ss.str().c_str() << std::endl;
//
//
//
//	//Stand by :)
//	while (TRUE)
//	{
//		Sleep(1000);
//	}
//	return TRUE;
//}
//
//DWORD WINAPI MyEndlessLoopChecker(LPVOID lpThreadParam)
//{
//	//printf("endless loop checker is disabled\n");
//	return 0;
//}
//
//void PrintItemInfo(CGItem* pItem)
//{
//	printf("CGItem ptr = %p, ItemId = %d, RefItemId = %d, Desc = %s\n",
//		pItem,
//		pItem->pCInstanceItem->ItemId,
//		pItem->pCInstanceItem->RefItemId,
//		pItem->pCInstanceItem->pCRefObjItem->DescriptionText);
//}
//
//DWORD WINAPI DebugWorker(LPVOID lpParam)
//{
//	while (true)
//	{
//		Sleep(1000);
//		//system("cls");
//		//printf("iter...\n");
//
//		std::list<CGObjPC*> players = CObjMgr::GetPlayers();
//
//
//		for (std::list<CGObjPC*>::iterator it = players.begin(); it != players.end(); it++)
//		{
//			CGObjPC* item = (CGObjPC*)(*it);
//
//			//printf("Unique ID = %d CharID = %d CharName16 = %s\nPtr: %p\n",
//			//	item->UniqueID,
//			//	item->iCInstancePC->CharID,
//			//	item->iCInstancePC->CharName16,
//			//	item);
//
//			//printf("level = %d max = %d\n", item->GetLevel(), item->GetMaxLevel());
//			//printf("health = %d max = %d\n", item->GetHealth(), item->GetMaxHealth());
//
//			//for (int i = 0; i < item->iCGStorage_Normal.MaxSlots; i++)
//			//{
//			//	CGItem* equipItem = item->iCGStorage_Normal.GetItem(i);
//
//			//	if (equipItem != NULL)
//			//	{
//			//		std::cout << "Body slot " << i;
//			//		PrintItemInfo(equipItem);
//			//	}
//			//}
//
//			//std::cout << "---------------------------------------------" << std::endl;
//			//for (int i = 0; i < item->iCGStorage_Avatar.MaxSlots; i++)
//			//{
//			//	CGItem* equipItem = item->iCGStorage_Avatar.GetItem(i);
//			//	if (equipItem != NULL)
//			//	{
//			//		std::cout << "Avatar slot " << i;
//			//		PrintItemInfo(equipItem);
//			//	}
//			//}
//
//			if (item->CanSendMessage())
//			{
//				CGItem* equipItem1 = item->iCGStorage_Normal.GetItem(PlayerInventorySlot::FirstStorageSlot);
//				//CGItem* equipItem2 = item->iCGStorage_Normal.GetItem(PlayerInventorySlot::FirstStorageSlot + 1);
//				//if (equipItem1 != NULL && equipItem2 != NULL)
//				//{
//					//printf("SETT items...\n");
//					//Sleep(2000);
//
//				//item->iCGStorage_Normal.SwapItem(PlayerInventorySlot::FirstStorageSlot, PlayerInventorySlot::FirstStorageSlot + 1);
//				//Sleep(5000);
//				//item->iCGStorage_Normal.MoveItem(13, PlayerInventorySlot::FirstStorageSlot + 1);
//				//Sleep(5000);
//				//item->iCGStorage_Normal.SetItem1(equipItem1, PlayerInventorySlot::FirstStorageSlot + 2, 0);
//				Sleep(2000);
//				printf("done...\n");
//				//Sleep(2000);
//			}
//			//}
//		}
//	}
//}
//
//bool CDebugHelper::Initialize()
//{
//	SDebugConfig* pConfig = CConfigMgr::GetDebugConfig();
//	SetDebugPrivilege(pConfig->bDebugPrivilege);
//
//	DetourTransactionBegin();
//
//	if (pConfig->bDebuggerPresent)
//	{
//		CDebugHelper::SetDebugPrivilege(TRUE);
//
//		HMODULE hKernel32 = GetModuleHandleA("Kernel32.dll");
//		pfnIsDebuggerPresent = reinterpret_cast<fnIsDebuggerPresent>(GetProcAddress(hKernel32, "IsDebuggerPresent"));
//
//		//DetourAttach(&(PVOID&)pfnIsDebuggerPresent, MyIsDebuggerPresent);
//	}
//
//	if (pConfig->bTopLevelExceptionHook)
//	{
//		pfnTopLevelExceptionFilter = reinterpret_cast<fnTopLevelExceptionFilter>(TOP_LEVEL_EXCEPTION_FILTER_HOOK_OFFSET);
//		DetourAttach(&(PVOID&)pfnTopLevelExceptionFilter, MyTopLevelExceptionFilter);
//	}
//
//
//	if (pConfig->bMinidumpOnTopLevelException)
//	{
//		pfnWriteTopLevelExceptionMinidump = reinterpret_cast<fnWriteTopLevelExceptionMinidump>(TOP_LEVEL_EXCEPTION_MINIDUMP_WRITER_FUNC_OFFSET);
//	}
//
//	if (pConfig->bDisableEndlessLoopChecker)
//	{
//		pfnEndlessLoopChecker = reinterpret_cast<fnEndlessLoopChecker>(ENDLESS_LOOP_CHECKER_HOOK_OFFSET);
//		DetourAttach(&(PVOID&)pfnEndlessLoopChecker, MyEndlessLoopChecker);
//	}
//
//	if (pConfig->bLogLastNetMsgs)
//	{
//	}
//
//	DetourTransactionCommit();
//
//	//std::cout << "Debugger presence = " << pfnIsDebuggerPresent() << std::endl;
//
//	//CreateThread(NULL, 0, DebugWorker, NULL, 0, 0);
//	return true;
//}
//
//BOOL CDebugHelper::SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
//{
//	TOKEN_PRIVILEGES tp;
//	LUID luid;
//
//	if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid))
//		return FALSE;
//
//	tp.PrivilegeCount = 1;
//	tp.Privileges[0].Luid = luid;
//	tp.Privileges[0].Attributes = (bEnablePrivilege) ? SE_PRIVILEGE_ENABLED : NULL;
//
//	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
//		return FALSE;
//
//	return TRUE;
//}
//
//
//BOOL CDebugHelper::SetDebugPrivilege(BOOL bEnable)
//{
//	HANDLE hToken;
//
//	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
//		return FALSE;
//
//	if (!CDebugHelper::SetPrivilege(hToken, SE_DEBUG_NAME, bEnable))
//		return FALSE;
//
//	return TRUE;
//}
//
//std::string CDebugHelper::DumpExceptionRecord(_EXCEPTION_RECORD* pRecord)
//{
//	std::stringstream ss;
//	ss << "Begin exception record dump" << std::endl;
//	ss << "ExceptionCode=0x" << std::uppercase << std::hex << pRecord->ExceptionCode << std::endl;
//	ss << "ExceptionFlags=0x" << std::uppercase << std::hex << pRecord->ExceptionFlags << std::endl;
//	ss << "ExceptionRecord=0x" << std::uppercase << std::hex << pRecord->ExceptionRecord << std::endl;
//	ss << "NumberParameters=" << std::uppercase << pRecord->NumberParameters << std::endl;
//
//	for (int i = 0; i < pRecord->NumberParameters; i++)
//	{
//		ss << "Param IDX=" << i << ", value = 0x" << std::uppercase << std::hex << pRecord->ExceptionInformation[i] << std::endl;
//	}
//	ss << "End exception record dump" << std::endl;
//
//	return ss.str();
//}
//
//std::string CDebugHelper::DumpExceptionContext(_CONTEXT* pContext)
//{
//	std::stringstream ss;
//	ss << "Begin exception context dump" << std::endl;
//	ss << "ContextFlags=0x" << std::uppercase << std::hex << pContext->ContextFlags << std::endl;
//
//	ss << "General purpose registers" << std::endl;
//
//	ss << "EDI=0x" << std::uppercase << std::hex << pContext->Edi << std::endl;
//	ss << "ESI=0x" << std::uppercase << std::hex << pContext->Esi << std::endl;
//	ss << "EBX=0x" << std::uppercase << std::hex << pContext->Ebx << std::endl;
//	ss << "EDX=0x" << std::uppercase << std::hex << pContext->Edx << std::endl;
//	ss << "ECX=0x" << std::uppercase << std::hex << pContext->Ecx << std::endl;
//	ss << "EAX=0x" << std::uppercase << std::hex << pContext->Eax << std::endl;
//
//	ss << "Service & other registers" << std::endl;
//
//	ss << "EBP=0x" << std::uppercase << std::hex << pContext->Ebp << std::endl;
//	ss << "EIP(FAULTY CODE OFFSET)=0x" << std::uppercase << std::hex << pContext->Eip << std::endl;
//	ss << "SEG_CS=0x" << std::uppercase << std::hex << pContext->SegCs << std::endl;
//	ss << "EFLAGS=0x" << std::uppercase << std::hex << pContext->EFlags << std::endl;
//	ss << "ESP(STACK)=0x" << std::uppercase << std::hex << pContext->Esp << std::endl;
//	ss << "SEG_SS=0x" << std::uppercase << std::hex << pContext->SegSs << std::endl;
//
//	ss << "End exception context dump" << std::endl;
//	return ss.str();
//}
//
//std::string CDebugHelper::DumpStack(int count)
//{
//	return std::string("[not implemented]");
//}