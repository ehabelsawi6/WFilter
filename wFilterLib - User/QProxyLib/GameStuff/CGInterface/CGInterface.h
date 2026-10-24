#ifndef Q_CGINTERFACE_H
#define Q_CGINTERFACE_H
#include "../../stdafx.h"
#include <d3d9types.h>
#include "../../Helpers/CStringHelper.h"
#include "../../GameMain/GameMain.h"
#include "IFMainPopup.h"
#include "IFItemMall.h"

#define g_CGInterface (*(CGInterface**)0x0110F80C)
#define g_CurrentIfUnderCursor (*(CGWndBase**)0x0110F608)
#define blueMSGptr 0x0077B580
#define pinkMSGptr 0x00777BF0
#define greenMSGptr 0x0077B5B0

class CControler
{
public:
	char pad_0000[80]; //0x0000
	uint32_t cursorPosX; //0x0050
	uint32_t cursorPosY; //0x0054
	char pad_0058[4072]; //0x0058
}; //Size: 0x1040
#define g_Controler (*(CControler**)0x0110F7D4)
typedef void(__thiscall * fpShowMessage_t)(int pthis, w_string_last *msg);
struct CGWndBase {
public:
	int8_t pad97[97];
	bool IsVisible();
	void write(int a1, D3DCOLOR color, wchar_t* msg, int a2, int a3);
private:
	bool m_bVisible;
};
class CInterfaceBuilder
{
public:
	CGWndBase* GetGUIObjectByID(int id, int a2);
};
class CIFStatic
{
public:
	char _pad_to_instance[0x30];
	CIFSlotWithHelp* pSlot;
};

class CGInterface {
public:
	char _pad0[0x36C]; // Add a padding to shift the field
	CInterfaceBuilder field_36C;
	char _pad1[0x3AC]; // Add a padding to shift the field
	bool isVisible;
	void ShowMessage_PINK(std::wstring msg);
	void ShowMessage_GREEN(std::wstring msg);
	void ShowMessage_BLUE(std::wstring msg);
	void SendGuideMsg(std::wstring msg, int color);
	void SendColoredMsg(GameChatType type, std::wstring Message, DWORD color);
	void SendColoredMsgA(GameChatType type, std::string Message, DWORD color);
	void SwitchQuestWindow();
	void SwitchToStallNetwork(bool Enabled);
	class CIFMainPopup* GetMainPopup();
};
#endif