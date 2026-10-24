#include "ChatManager.h"
#include "../../GameMain/GameMain.h"
#include "../../GameStuff/CGInterface/CGInterface.h"
#include "../../GameStuff/CICPlayer/CICPlayer.h"
#include "../../GameStuff/CGInterface/IFSlotWithHelp.h"

typedef void(__thiscall* fnWriteNormalChat)(
	void*, uint32_t type, const wchar_t* msg,
	DWORD color, uint32_t fontStyle);

fnWriteNormalChat m_WriteNormalChat = NULL;

ChatManager::ChatManager()
{
	m_WriteNormalChat = reinterpret_cast<fnWriteNormalChat>(0x00777C30);
}

void ChatManager::WriteChatA(GameChatType type, const char* msg, DWORD color, uint32_t fontStyle) const
{
	//TODO: Global var for ptr
	void* ecx = g_MemoryHelper->RefPtr<void*>(0x110F80C);

	std::string msgA(msg);
	std::wstring msgW(msgA.begin(), msgA.end());
	m_WriteNormalChat(ecx, type, msgW.c_str(), color, 1);
}



void ChatManager::WriteChatA(GameChatType type, const char* msg, DWORD color) const
{
	WriteChatA(type, msg, color, 1);
}

void ChatManager::WriteChatW(GameChatType type, const wchar_t* msg, DWORD color, uint32_t fontStyle) const
{
	void* ecx = g_MemoryHelper->RefPtr<void*>(0x110F80C);
	m_WriteNormalChat(ecx, type, msg, color, fontStyle);
}

void ChatManager::WriteChatW(GameChatType type, const wchar_t* msg, DWORD color) const
{
	WriteChatW(type, msg, color, 1);
}
void ChatManager::Handle(CMsgStreamBuffer* packet)
{
	if (g_CGInterface && g_CICPlayer)
	{
		const uint8_t msgType = packet->Read<uint8_t>();
		const uint8_t writeToRight = packet->Read<bool>();

		const std::wstring Message = packet->ReadStringW();

		switch ((CustomMsgType)msgType)
		{
		case Blue:
			g_CGInterface->ShowMessage_BLUE(Message);
			g_CGInterface->SendGuideMsg(Message, 0x0080ff);
			break;
		case Green:
			g_CGInterface->ShowMessage_GREEN(Message);
			g_CGInterface->SendGuideMsg(Message, 0x008b8b);
			break;
		case Red:
			g_CGInterface->ShowMessage_PINK(Message);
			g_CGInterface->SendGuideMsg(Message, 0xFFC0CB);
			break;
		case Guide:
			g_CGInterface->SendGuideMsg(Message, 0xdbca9d);
			break;
		case Colored:
			const GameChatType type = (GameChatType)packet->Read<uint8_t>();
			const DWORD color = packet->Read<DWORD>();
			if (type == GameChatType::Global)
			{
				uint32_t UniqueID = packet->Read<uint32_t>();
				uint8_t hasLinkedItem = packet->Read<uint8_t>(); // this is the same flag
				if (hasLinkedItem)
				{
					auto temporaryPacket = new CMsgStreamBuffer(0xB034);
					for (size_t i = 0; i < ((packet->GetLength() - 15) - (Message.length() * 2)); i++)
					{
						auto byte = packet->Read<uint8_t>();

						temporaryPacket->Write<uint8_t>(byte);
					}
					GlobalChat chat;

					chat.index = 0;
					chat.msg = (wchar_t*)Message.c_str();
					chat.completed = false;
					chat.buffer = temporaryPacket;
					g_GlobalDataMgr->GlobalChatLog.push_back(chat);
					//cloned the item and added it to the list, so revive the old item back. oh fuck that

				}
				auto Sender = g_CICPlayer->GetCICPlayerByUniqueID(UniqueID);
				if (Sender)
				{
					g_CGInterface->SendColoredMsg(type, Message, color);
					auto splitted = g_StringHelper->wsplit(Message, L':');
					w_string_last string = w_string_last(splitted[1]);
					Sender->ShowMessageAbove(&string, color);
				}
				else
					g_CGInterface->SendColoredMsg(type, Message, color);
			}
			else
				g_CGInterface->SendColoredMsg(type, Message, color);
			break;
		}

		if (writeToRight)
			g_CGInterface->SendGuideMsg(Message, 0xdbca9d);
	}
}
