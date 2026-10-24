#include "OldItemMall.h"
#include "../../includes.h"
#include "../../GameStuff/CGInterface/CGInterface.h"
#include "../../GameStuff/CGInterface/IFItemMall.h"

const DWORD cdwOldItemMallHookAddr = 0x007BDEE0;
const DWORD cdwOldItemMallHookAddrJmpback = 0x007BDEE5;

__declspec(naked) void ASM_OnItemMallHook()
{
	__asm
	{
		CALL OldItemMall::OnDoStuff;
		MOV EAX, 0xEEC2E8;
		jmp cdwOldItemMallHookAddrJmpback;
	}
}


const DWORD cdwOldItemMallBuyItemHookAddr = 0x00799600;
const DWORD cdwOldItemMallBuyItemHookAddrJmpback = 0x0079960F;
const DWORD cdwOldItemMallBuyItemCallAddr = 0x8B51F0;
__declspec(naked) void ASM_OnItemMallBuy()
{
	__asm
	{
		PUSH 1;
		PUSH 0xA7;
		ADD ECX, 0x36C;
		CALL cdwOldItemMallBuyItemCallAddr;
		jmp cdwOldItemMallBuyItemHookAddrJmpback;
	}
}
void OldItemMall::OnDoStuff()
{
	if (g_CGInterface)
	{
		auto MallPtr = (IFItemMall*)g_CGInterface->field_36C.GetGUIObjectByID(167, 1);
		if (MallPtr)
		{
			if (MallPtr->BtnBuyingList->isVisible)
			{
				MallPtr->BtnBuyingList->isVisible = false;
				MallPtr->BtnObtainedList->isVisible = false;
				MallPtr->BtnWornBuy->isVisible = false;
				MallPtr->CIFItemMallZZIM->CIFButtonZZIM->isVisible = false;
			}
		}
	}
}

const DWORD ItemMallCloseAddr = 0x00652C87 + 2;
void OldItemMall::Initialize()
{
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOldItemMallHookAddr), ASM_OnItemMallHook);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOldItemMallBuyItemHookAddr), ASM_OnItemMallBuy);
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(ItemMallCloseAddr), 1);
	*(BYTE*)(ItemMallCloseAddr) = 0xC2;
	g_MemoryHelper->ReProtect();
}