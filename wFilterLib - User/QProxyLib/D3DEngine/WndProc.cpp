#include "WndProc.h"
#include "../GameMain/GameMain.h"
#include "GUIs/ChestWindow.h"
#include <Input/WindowsMessage.hpp>
#include "GUIs/Pandora/SplashScreen.h"
#include "GUIs/Pandora/MainMenuWindow.h"
#include "GUIs/UniqueStatus.h"
#include "GUIs/TitleManager.h"
#include "GUIs/GrantNameWindow.h"
#include "GUIs/CustomTitleWindow.h"
#include "GUIs/RankingWindow.h"
#include "GUIs/EventManager.h"
#include "GUIs//EventTimesWindow.h"
#include "../GameStuff/CGInterface/CGInterface.h"
#include "../GameStuff/CNIRMManager/CNIRMManager.h"
#include "GUIs/AccountLockedWindow.h"
#include "GUIs/AccountLockWindow.h"
#include "GUIs/DynamicShop.h"

using namespace OSHGui;
Input::WindowsMessage input;
HWND g_orig_wndproc_hwnd;
WNDPROC g_orig_wndproc;

bool g_isDrawable = true;

//SplashScreen* g_SplashScreen;

extern ChestWindow* chestWindow;
extern MainMenuWindow* mainMenuWindow;
extern TitleManagerWindow* titleManagerWindow;
extern UniqueStatusWindow* uniqueStatusWindow;
extern GrantNameWindow* grantNameWindow;
extern CustomTitleWindow* customTitleWindow;
//extern RankingWindow* rankingWindow;
extern EventManagerWindow* eventManagerWindow;
extern EventTimesWindow* eventTimesWindow;
extern AccountLockedWindow* accountLockedWindow;
extern AccountLockWindow* accountLockWindow;
extern DynamicShopWindow* dynamicShopWindow;

const DWORD cdwOnMsgHandleHookAddr = 0x0078B6A8;
const DWORD cdwOnMsgHandleHookAddrRetn = 0x0078B690;
const DWORD cdwOnMsgHandleHookJmpback = 0x0078B6AD;

bool Handled(DWORD esp)
{
	if (*(uint32_t*)(esp + 0x2C) == VK_ESCAPE)
	{
		if (chestWindow)
		{
			chestWindow->Close();
			return true;
		}
		else if (uniqueStatusWindow)
		{
			uniqueStatusWindow->Close();
			uniqueStatusWindow = nullptr;
			return true;
		}
		/*else if (rankingWindow)
		{
			rankingWindow->Close();
			rankingWindow = nullptr;
			return true;
		}*/
		else if (titleManagerWindow)
		{
			titleManagerWindow->Close();
			titleManagerWindow = nullptr;
			return true;
		}
		else if (grantNameWindow)
		{
			grantNameWindow->Close();
			grantNameWindow = nullptr;
			return true;
		}
		else if (eventManagerWindow)
		{
			eventManagerWindow->Close();
			eventManagerWindow = nullptr;
			return true;
		}
		else if (customTitleWindow)
		{
			customTitleWindow->Close();
			customTitleWindow = nullptr;
			return true;
		}
		else if (mainMenuWindow)
		{
			mainMenuWindow->Close();
			mainMenuWindow = nullptr;
			return true;
		}
		else if (eventTimesWindow) {
			eventTimesWindow->Close();
			eventTimesWindow = nullptr;
			return true;
		}

		else if (accountLockWindow) {
			accountLockWindow->Close();
			accountLockWindow = nullptr;
			return true;
		}

		else if (dynamicShopWindow) {
			dynamicShopWindow->Close();
			dynamicShopWindow = nullptr;
			return true;
		}
	}
	return false;
}

__declspec(naked) void ASM_OnClientMsgHandler()
{
	__asm {
		pushad;
		pushfd;

		push esp;
		CALL Handled;

		cmp al, TRUE;
	je OnHappyEnd;
		pop esp;
		popfd;
		popad;
		LEA EAX, DWORD PTR SS : [ESP + 10];
		PUSH EAX;
		jmp cdwOnMsgHandleHookJmpback;
	OnHappyEnd:
		pop esp;
		popfd;
		popad;
		MOV EAX, 1;
		POP ESI;
		RET 0xC;
	}
}
//orig keychecker 00780800
std::string GetClipboardText()
{
	// Try opening the clipboard
	if (!OpenClipboard(nullptr))
		return "";
	  // Get handle of clipboard object for ANSI text
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData == nullptr)
			return "";

	  // Lock the handle to get the actual text pointer
		char* pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr)
			return "";
		

	  // Save text in a string class instance
		std::string text(pszText);

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	return text;
}

LRESULT CALLBACK WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MSG new_msg;
	new_msg.hwnd = hwnd;
	new_msg.message = msg;
	new_msg.wParam = wParam;
	new_msg.lParam = lParam;
	if (g_orig_wndproc_hwnd != hwnd)
	{
		g_orig_wndproc_hwnd = hwnd;
	}
	if (*(DWORD**)0x0110F80C) // if cginterface is set
	{
		//if (new_msg.message == WM_KEYUP) {
		//	if (new_msg.wParam == 'V' || new_msg.wParam == 'v') {
		//		auto CtrlState = GetKeyState(VK_LSHIFT);
		//		if (CtrlState == -127 || CtrlState == -128) {
		//			g_CGInterface->ShowMessage_BLUE(CStringHelper::s2ws(GetClipboardText()));

		//			std::string text = GetClipboardText();
		//			//ReplyMessage()
		//			for (size_t i = 0; i < text.size(); i++)
		//			{
		//				MSG new_msg2;
		//				new_msg2.hwnd = hwnd;
		//				new_msg2.message = text[i];
		//				new_msg2.wParam = text[i];
		//				new_msg2.lParam = lParam;

		//				input.ProcessMessage(&new_msg2);
		//				
		//			}
		//			return 1;
		//		}
		//	}
		//}
		switch (new_msg.message)
		{
		case WM_PASTE:
			g_CGInterface->ShowMessage_BLUE(CStringHelper::s2ws(GetClipboardText()));
			break;
		case WM_CLOSE:
			exit(EXIT_SUCCESS);
			break;
		case WM_KEYDOWN:
			
		//if (new_msg.wParam == 'f' || new_msg.wParam == 'F')
		//{
		//	if (g_CICPlayer)
		//	{
		//		if (g_CNIRMManager->GetWindowActive(0x96) == 0)
		//		{
		//			g_CGInterface->SwitchToStallNetwork(true);
		//		}
		//		else 
		//		{
		//			g_CGInterface->SwitchToStallNetwork(false);
		//		}
		//	}
		//}
		//break;
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		case WM_CHAR:
		case WM_SYSCHAR:
		case WM_IME_CHAR:
		case VK_BACK:
		case VK_DELETE:
		{
			if ((accountLockWindow && accountLockWindow->tb_pinCode->GetIsFocused()) ||  (accountLockWindow && accountLockWindow->tb_pinCode2->GetIsFocused()) || (accountLockedWindow && accountLockedWindow->tb_pinCode->GetIsFocused()) || (grantNameWindow && grantNameWindow->tb_GrantName->GetIsFocused()) || (customTitleWindow && customTitleWindow->tb_CustomTitle->GetIsFocused()))
			{
				if (wParam != VK_RETURN)
					input.ProcessMessage(&new_msg);
				return 1;
			}
		}
		break;
		case WM_MOUSEMOVE:
		{
			if (GetKeyState(VK_RBUTTON) < 0)
				return CallWindowProc(g_orig_wndproc, hwnd, msg, wParam, lParam);
			else
			{
				if (input.ProcessMessage(&new_msg))
				{
					return 1;
				}
			}
		}
		break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MOUSEWHEEL:
		{
			if (input.ProcessMessage(&new_msg))
			{
				return 1;
			}
		}
		break;
		}
	}
	if (g_CGInterface && new_msg.message == WM_LBUTTONDOWN)
	{
		CIFSlotWithHelp* slotptr = (CIFSlotWithHelp*)g_CurrentIfUnderCursor;
		//printf("current if under cursor = %02x\n", slotptr);
		auto ALTState = GetKeyState(VK_MENU);
		auto MouseState = GetKeyState(VK_LBUTTON);
		if (slotptr && (ALTState == -127 || ALTState == -128) && (MouseState == -127 || MouseState == -128))
		{
			if (*(DWORD*)slotptr == 0xDA18E4 || *(DWORD*)slotptr == 0xD9E0FC)
			{
				if (*(DWORD*)slotptr == 0xD9E0FC)
				{
					CIFStatic* shit = (CIFStatic*)(slotptr);
					if (shit)
					{
						slotptr = shit->pSlot;
					}
				}
				auto slotId = (slotptr->dwSlotID - 87);
				if ((slotptr->getPtr->selfPtr == 0xDA775C || slotptr->getPtr->selfPtr == 0xDA18E4) && (slotId >= 13 && slotId <= 108))
				{
					if (slotptr->pCSOItem)
					{
						CIFWholeChat* pWholeChat = (CIFWholeChat*)g_CGInterface->field_36C.GetGUIObjectByID(56, 0);
						if (pWholeChat)
						{
							auto pCIFEdit = pWholeChat->pCIFEdit;
							if (pCIFEdit)
							{
								if (g_GlobalDataMgr->m_LinkedGlobalItemEnd > 0)
								{
									std::wstring msg = L"You're allowed to link only one item once per global.";
									g_CGInterface->ShowMessage_BLUE(msg);
									g_CGInterface->SendGuideMsg(msg, 0xFFFFFFFF);
									return 1;
								}
								auto currStr = std::wstring(pCIFEdit->GetText());
								currStr.append(L" ");
								g_GlobalDataMgr->m_LinkedGlobalItemBegin = currStr.length();
								auto ObjectData = g_GlobalDataMgr->GetGenericObjectDataByID(slotptr->pCSOItem->dwObjID);
								auto Item = L"<"+g_GlobalDataMgr->GetObjectName(ObjectData)+L">";
								std::wstring underline = L"\u035F";
								std::wstring ItemName;
								for (auto &c : Item)
								{
									std::wstring bkp(1, c);
									ItemName.append(underline);
									ItemName.append(bkp);
								}
								pCIFEdit->SetText(std::wstring(currStr).append(ItemName.append(L" ")).c_str());

								g_GlobalDataMgr->m_LinkedGlobalItemEnd = std::wstring(pCIFEdit->GetText()).length();
								g_GlobalDataMgr->m_CurrentLinkedItemName = ItemName;
								g_GlobalDataMgr->m_LinkedGlobalSlot = slotId;
							}
						}
					}
					return TRUE; // handled
				}
			}
		}
	}
	return CallWindowProc(g_orig_wndproc, hwnd, msg, wParam, lParam);
}

const DWORD cdwOnF12PressedAddr = 0x0079E1C0;
const DWORD cdwOnF12PressedAddrJmpback = 0x0079E1C6;
void OnF12Callback(DWORD esi)
{
	g_isDrawable = *(bool*)(esi + 0x71C);
	//if (!g_isDrawable)
	//{
	//	g_SplashScreen = new SplashScreen();
	//	g_SplashScreen->GetFormClosingEvent() += FormClosingEventHandler([&](Control* sender, bool canClose)
	//		{
	//			g_SplashScreen = nullptr;
	//		});
	//	g_SplashScreen->Show(std::shared_ptr<Form>(g_SplashScreen));
	//}
	//else
	//{
	//	if (g_SplashScreen)
	//	{
	//		g_SplashScreen->Close();
	//		g_SplashScreen = nullptr;
	//	}
	//}
}
__declspec(naked) void ASM_OnF12Pressed()
{
	__asm
	{
		pushad;
		pushfd;
		push esi;
		CALL OnF12Callback;
		pop esi;
		popfd;
		popad;

		MOV DWORD PTR FS : [0], EAX;
		jmp cdwOnF12PressedAddrJmpback;
	}
}
WndProc::WndProc()
{
	D3DDEVICE_CREATION_PARAMETERS d3dcp;
	g_D3DMisc->GetDevice()->GetCreationParameters(&d3dcp);
	g_orig_wndproc = (WNDPROC)SetWindowLongPtr(d3dcp.hFocusWindow, GWL_WNDPROC, (LONG)(LONG_PTR)WndProcHandler);

	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnMsgHandleHookAddr), ASM_OnClientMsgHandler);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnF12PressedAddr), ASM_OnF12Pressed);
}

WndProc::~WndProc()
{
}