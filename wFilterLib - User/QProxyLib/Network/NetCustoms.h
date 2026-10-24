#pragma once
#include "../stdafx.h"
#include "MsgStreamBuffer.h"

enum class E_MSGHOOK_RESULT
{
	PASS_THROUGH,
	BLOCK
};

using __MSG_HANDLER = std::function<E_MSGHOOK_RESULT(CMsgStreamBuffer*)>;
using __MSG_HANDLER_MAP = std::map<uint16_t, __MSG_HANDLER>;
using __MSG_HANDLER_MAP_IT = __MSG_HANDLER_MAP::iterator;

using FN_RECEIVE_MSG = bool(__thiscall*)(void* pSender, CMsgStreamBuffer* pMsg);
using FN_SEND_MSG = void**(__cdecl*)(const CMsgStreamBuffer*);

class CNetCustoms
{
private:
	__MSG_HANDLER_MAP m_inMsgHandlerMap;
	__MSG_HANDLER_MAP m_outMsgHandlerMap;
	__MSG_HANDLER m_inMsgDefaultHandler;
	__MSG_HANDLER m_outMsgDefaultHandler;


public:
	CNetCustoms();
	~CNetCustoms();

	void Initialize();

	void SetDefaultInMsgHandler(__MSG_HANDLER handler);
	void SetDefaultOutMsgHandler(__MSG_HANDLER handler);


	void SetInMsgHandler(uint16_t id, __MSG_HANDLER handler);
	void SetOutMsgHandler(uint16_t id, __MSG_HANDLER handler);

	E_MSGHOOK_RESULT HandleMsgIn(CMsgStreamBuffer* pMsg);
	E_MSGHOOK_RESULT HandleMsgOut(CMsgStreamBuffer* pMsg);

	static FN_RECEIVE_MSG s_fnRecvMsg;
	static FN_SEND_MSG s_fnSendMsg;

}; 