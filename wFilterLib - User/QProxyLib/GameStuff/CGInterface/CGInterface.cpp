#include "CGInterface.h"
#include "../CICPlayer/CICPlayer.h"

void CGWndBase::write(int a1, D3DCOLOR color, wchar_t* msg, int a2, int a3)
{
	reinterpret_cast<void(__thiscall*)(CGWndBase*, int, D3DCOLOR, wchar_t*, int, int)>(0x007B89E0)(this, a1, color, msg, a2, a3);
}

void CGInterface::SendGuideMsg(std::wstring msg, int color)
{
	if (!g_CGInterface || !g_CICPlayer)
		return;
	CGWndBase* systemmessage = g_CGInterface->field_36C.GetGUIObjectByID(68, 1);
	wchar_t* test = const_cast<wchar_t*>(msg.c_str());
	systemmessage->write(0xFF, color, test, 0, 1);
}

void CGInterface::ShowMessage_BLUE(std::wstring msg)
{
	if (!g_CGInterface || !g_CICPlayer)
		return;
	w_string_last str = w_string_last(msg);
	reinterpret_cast<fpShowMessage_t>(blueMSGptr)(reinterpret_cast<int>(g_CGInterface), &str);
}

void CGInterface::ShowMessage_GREEN(std::wstring msg)
{
	if (!g_CGInterface || !g_CICPlayer)
		return;
	w_string_last str = w_string_last(msg);
	reinterpret_cast<fpShowMessage_t>(greenMSGptr)(reinterpret_cast<int>(g_CGInterface), &str);
}

void CGInterface::ShowMessage_PINK(std::wstring msg)
{
	if (!g_CGInterface || !g_CICPlayer)
		return;
	w_string_last str = w_string_last(msg);
	reinterpret_cast<fpShowMessage_t>(pinkMSGptr)(reinterpret_cast<int>(g_CGInterface), &str);
}

void CGInterface::SendColoredMsg(GameChatType type, std::wstring Message, DWORD color)
{
	if (!g_CGInterface || !g_CICPlayer)
		return;
	if (type == GameChatType::Custom)
	{
		this->SendGuideMsg(Message, color);
		return;
	}
	g_ChatManager->WriteChatW(type, Message.c_str(), color, 1);
}

void CGInterface::SendColoredMsgA(GameChatType type, std::string Message, DWORD color)
{
	if (!g_CGInterface || !g_CICPlayer)
		return;
	g_ChatManager->WriteChatA(type, Message.c_str(), color, 1);
}

void CGInterface::SwitchQuestWindow()
{
	return reinterpret_cast<void(__thiscall*)(CGInterface*)>(0x007990E0)(this);
}

void CGInterface::SwitchToStallNetwork(bool Enabled)
{
	return reinterpret_cast<void(__thiscall*)(CGInterface*, bool)>(0x00799020)(this, Enabled);
}

CGWndBase* CInterfaceBuilder::GetGUIObjectByID(int id, int a2)
{
	return reinterpret_cast<CGWndBase*(__thiscall*)(CInterfaceBuilder*, int, int)>(0x008B51F0)(this, id, a2);
}
bool CGWndBase::IsVisible()
{
	return this->m_bVisible;
}

CIFMainPopup* CGInterface::GetMainPopup(void)
{
	return reinterpret_cast<CIFMainPopup*(__thiscall*)(CGInterface*)>(0x00798D00)(this);
}
