#ifndef Q_CHAT_MANAGER_H
#define Q_CHAT_MANAGER_H
#include "../../stdafx.h"
#include "../../Network/MsgStreamBuffer.h"
enum GameChatType
{
	Normal = 1,
	Private = 2,
	NormalGM = 3,
	Party = 4,
	Guild = 5,
	Global = 6,
	Notice = 7,
	Stall = 9,
	Union = 11,
	NPC = 13,
	Custom = 15,
	Academy = 16
};
enum CustomMsgType
{
	Guide = 1,
	Red,
	Green,
	Blue,
	Colored
};
class ChatManager
{
public:
	ChatManager();

	void Handle(CMsgStreamBuffer* packet);
	void WriteChatA(GameChatType type, const char* msg, DWORD color, uint32_t fontStyle) const;
	void WriteChatA(GameChatType type, const char* msg, DWORD color) const;
	void WriteChatW(GameChatType type, const wchar_t* msg, DWORD color, uint32_t fontStyle) const;
	void WriteChatW(GameChatType type, const wchar_t* msg, DWORD color) const;
private:

};
#endif