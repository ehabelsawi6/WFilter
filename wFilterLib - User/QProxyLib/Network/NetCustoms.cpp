#include "NetCustoms.h"
#include "MsgStreamBuffer.h"
#include "../GameMain/GameMain.h"
#define MSG_HANDLE_RECV_OFFSET			0x00BA8F70
#define MSG_HANDLE_SEND_OFFSET			0x008418D0


using fnRecvMsg = bool(__thiscall*)(void* pSender, CMsgStreamBuffer* pMsg);
using fnSendMsg = void**(__cdecl*)(const CMsgStreamBuffer*);
bool __fastcall HandleMsgInEx(void* pSender, void* /* dummy edx */, CMsgStreamBuffer* pMsg);
void** __cdecl HandleMsgOutEx(CMsgStreamBuffer* pMsg);


FN_RECEIVE_MSG CNetCustoms::s_fnRecvMsg = nullptr;
FN_SEND_MSG CNetCustoms::s_fnSendMsg = nullptr;

extern CNetCustoms* g_NetCustoms;

CNetCustoms::CNetCustoms()
{
	m_inMsgDefaultHandler = [](CMsgStreamBuffer*) { return E_MSGHOOK_RESULT::PASS_THROUGH; };
	m_outMsgDefaultHandler = [](CMsgStreamBuffer*) { return E_MSGHOOK_RESULT::PASS_THROUGH; };
}

CNetCustoms::~CNetCustoms()
{

}

void CNetCustoms::Initialize()
{
	s_fnRecvMsg = reinterpret_cast<fnRecvMsg>(MSG_HANDLE_RECV_OFFSET);
	s_fnSendMsg = reinterpret_cast<fnSendMsg>(MSG_HANDLE_SEND_OFFSET);


	DetourTransactionBegin();
	DetourAttach(&(PVOID&)s_fnRecvMsg, HandleMsgInEx);
	DetourAttach(&(PVOID&)s_fnSendMsg, HandleMsgOutEx);
	DetourTransactionCommit();
}

void CNetCustoms::SetDefaultInMsgHandler(__MSG_HANDLER handler) { m_inMsgDefaultHandler = handler; };
void CNetCustoms::SetDefaultOutMsgHandler(__MSG_HANDLER handler) { m_outMsgDefaultHandler = handler; };

void CNetCustoms::SetInMsgHandler(uint16_t id, __MSG_HANDLER handler)
{
	if (m_inMsgHandlerMap.find(id) != m_inMsgHandlerMap.end())
		m_inMsgHandlerMap[id] = handler;
	else
		m_inMsgHandlerMap.insert(std::make_pair(id, handler));
};

void CNetCustoms::SetOutMsgHandler(uint16_t id, __MSG_HANDLER handler)
{
	if (m_outMsgHandlerMap.find(id) != m_outMsgHandlerMap.end())
		m_outMsgHandlerMap[id] = handler;
	else
		m_outMsgHandlerMap.insert(std::make_pair(id, handler));
};


E_MSGHOOK_RESULT CNetCustoms::HandleMsgIn(CMsgStreamBuffer* pMsg)
{
	__MSG_HANDLER_MAP_IT it = m_inMsgHandlerMap.find(pMsg->GetID());
	return (it != m_inMsgHandlerMap.end() ? it->second(pMsg) : m_inMsgDefaultHandler(pMsg));
}

E_MSGHOOK_RESULT CNetCustoms::HandleMsgOut(CMsgStreamBuffer* pMsg)
{
	__MSG_HANDLER_MAP_IT it = m_outMsgHandlerMap.find(pMsg->GetID());
	return (it != m_outMsgHandlerMap.end() ? it->second(pMsg) : m_outMsgDefaultHandler(pMsg));
}


bool __fastcall HandleMsgInEx(void* pSender, void* /* dummy edx */, CMsgStreamBuffer* pMsg)
{
	//printf("v3\n");
	E_MSGHOOK_RESULT result = g_NetCustoms->HandleMsgIn(pMsg);
	bool passThrough = false;


	switch (result)
	{
	case E_MSGHOOK_RESULT::PASS_THROUGH:
		passThrough = true;
		pMsg->Seek(0);
		break;
	case E_MSGHOOK_RESULT::BLOCK:
		passThrough = false;
		pMsg->Seek(pMsg->GetLength());
		break;
	}

	if (!passThrough)
		return false;

	return CNetCustoms::s_fnRecvMsg(pSender, pMsg);
}

void** __cdecl HandleMsgOutEx(CMsgStreamBuffer* pMsg)
{
	E_MSGHOOK_RESULT result = g_NetCustoms->HandleMsgOut(pMsg);

	bool passThrough = false;

	switch (result)
	{
	case E_MSGHOOK_RESULT::PASS_THROUGH:
		passThrough = true;
		pMsg->Seek(0);
		break;
	case E_MSGHOOK_RESULT::BLOCK:
		pMsg->Seek(pMsg->GetLength());
		passThrough = false;
		break;
	}

	if (!passThrough)
		return false;

	return CNetCustoms::s_fnSendMsg(pMsg);
}
