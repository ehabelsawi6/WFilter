#include "pch.h"
#include "MainProcess.h"
#include "MsgStreamBuffer.h"


CMainProcess::FN_SET_MSG_HANDLER CMainProcess::s_pfnSetMsgHandler;
CMainProcess::FN_HANDLE_MSG CMainProcess::s_pfnHandleMsg;
//CMainProcess::FN_MSG_HANDLER CMainProcess::s_pfnCustomMsgHandler;
CMainProcess::FN_GET_INSTANCE CMainProcess::s_pfnGetInstance;
//__MSG_HANDLER_MAP CMainProcess::s_mapMsgHandlers;

#define SET_MSG_HANDLER_FUNC_OFFSET			0x0094CBE0
#define HANDLE_MSG_FUNC_OFFSET				0x0094CBF0
#define GET_INSTANCE_FUNC_OFFSET			0x00401D30



void hexdump(void* ptr, int buflen) {
	unsigned char* buf = (unsigned char*)ptr;
	int i, j;
	for (i = 0; i < buflen; i += 16) {
		printf("%06x: ", i);
		for (j = 0; j < 16; j++)
			if (i + j < buflen)
				printf("%02x ", buf[i + j]);
			else
				printf("   ");
		printf(" ");
		for (j = 0; j < 16; j++)
			if (i + j < buflen)
				printf("%c", isprint(buf[i + j]) ? buf[i + j] : '.');
		printf("\n");
	}
}


void CMainProcess::Initialize()
{
	s_pfnSetMsgHandler = reinterpret_cast<FN_SET_MSG_HANDLER>(SET_MSG_HANDLER_FUNC_OFFSET);
	s_pfnHandleMsg = reinterpret_cast<FN_HANDLE_MSG>(HANDLE_MSG_FUNC_OFFSET);
	s_pfnGetInstance = reinterpret_cast<FN_GET_INSTANCE>(GET_INSTANCE_FUNC_OFFSET);

	//CMainProcess* pInst = CMainProcess::GetInstance();

	//s_pfnSetMsgHandler(pInst, 0x7777, MyFilterMsgHandler);

	//std::cout << "Custom msg handler registered for 0x7777" << std::endl;

	//SR_READY_TO_PLAY, userpurge, weirrd one :P
	//s_pfnCustomMsgHandler = reinterpret_cast<FN_MSG_HANDLER>(0x00403350);


	DetourTransactionBegin();

	//DetourAttach(&(PVOID&)s_pfnSetMsgHandler, CMainProcess::MySetMsgHandler);
	DetourAttach(&(PVOID&)s_pfnHandleMsg, CMainProcess::MyHandleMsg);
	//DetourAttach(&(PVOID&)s_pfnCustomMsgHandler, CMainProcess::MyCustomMsgHandler);



	DetourTransactionCommit();

}

__int16 __fastcall CMainProcess::MySetMsgHandler(CMainProcess* self, void* /* dummy edx */, __int16 id, void* handler)
{
	printf("%s -> self = 0x%p, id = 0x%04X, handler = 0x%p\n",
		self, id, handler);

	return s_pfnSetMsgHandler(self, id, handler);
}

int __fastcall CMainProcess::MyHandleMsg(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{

	//printf("%s -> self = 0x%p, pMsg = 0x%p, pMassiveMsg = 0x%p\n",
	//	__FUNCTION__,
	//	self, pMsg, pMassiveMsg);

	int res = 0;

	try
	{
		res = s_pfnHandleMsg(self, pMsg, dwOverlappedJobID, lpParam, pMassiveMsg);
	}
	catch (...)
	{
		printf("%s - Exception occoured !\n", __FUNCTION__);
		printf("!!! This could lead to gameserver entering invalid state !!!\n");
		printf("!!! It is recommended to shut the server down until the issue is resolved !!!\n");

		if (pMsg != NULL)
		{
			printf("Dumping last [non-massive] msg.\n", __FUNCTION__);

			printf("MsgID = 0x%04X\n", pMsg->GetID());


			__int16 oldReadPos = pMsg->GetReadPos();
			__int16 oldWritePos = pMsg->GetWritePos();
			__int16 bytesToRead = (oldWritePos - 6);

			pMsg->SetReadPos(6);

			char* buffer = new char[bytesToRead];

			pMsg->Read(buffer, bytesToRead);

			hexdump(buffer, bytesToRead);

			delete[] buffer;

			pMsg->SetReadPos(oldReadPos);

			std::cout << std::endl;
		}
	}

	return res;
	//return s_pfnHandleMsg(self, pMsg, dwOverlappedJobID, lpParam, pMassiveMsg);
}

/*
void* __fastcall CMainProcess::MyFilterMsgHandler(
	CMainProcess* self, void* /* dummy edx * /, CMsgStreamBuffer* pMsg, int a3, int a4, int a5
)
{
	printf("[custom msg] %s entered ! self = 0x%p, pMsg = 0x%p, a3 = 0x%x, a4 = 0x%x, a5 = 0x%x\n",
		__FUNCTION__,
		self, pMsg, a3, a4, a5);

	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("ReadPos %d WritePos %d\n", wReadPos, wWritePos);

	int first = pMsg->Read<int>();
	BYTE second = pMsg->Read<BYTE>();
	std::string third = pMsg->ReadStringA();
	int fourth = pMsg->Read<int>();

	printf("First = %d, Second = 0x%x, Third = %s, Fouth = %d\n",
		first, second, third.c_str(), fourth);

	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}
*/

CMainProcess* CMainProcess::GetInstance()
{
	return s_pfnGetInstance();
}

void CMainProcess::RegisterMsgHandler(__int16 id, FN_MSG_HANDLER handler)
{
	s_pfnSetMsgHandler(CMainProcess::GetInstance(), id, handler);
	std::cout << __FUNCTION__ << " - Msg handler registered" << std::endl;
}

/*
void* __fastcall CMainProcess::MyCustomMsgHandler(
	CMainProcess* self, void* /* dummy edx * /, CMsgStreamBuffer* pMsg, int a3, int a4, int a5
)
{
	printf("%s entered ! self = 0x%p, pMsg = 0x%p, a3 = 0x%x, a4 = 0x%x, a5 = 0x%x\n",
		__FUNCTION__,
		self, pMsg, a3, a4, a5);
	return s_pfnCustomMsgHandler(self, pMsg, a3, a4, a5);
}
*/