#include "OldAlchemy.h"
#include "../../GameMain/GameMain.h"

//Required stuff for ccaving
const DWORD cdwAlchemyWindowJmpBackAddr = 0x00798E3C;
const DWORD cdwAlcmButtonAddr = 0x00479B3E;

const DWORD alcmButtonFreeSpaceAddr = 0x00D7FF75;

const DWORD cdwButtonImagePath = 0x00479B6D;

const DWORD cdwAlchemyIcons = 0x00D8BA22;

const DWORD cdwCNIFAlchemyWnd = 0x00DB9C90;//DB9C90:"res_ui\\nifenchantwnd.2dt"

const DWORD cdwOnAlchemyClosed = 0x0059E538;
const DWORD cdwOnAlchemyClosedJmpback = 0x0059E53D;
//TEST BYTE PTR [ESP + 8], 1

bool patched = false;
void AlchemyPatch::PatchAlchemyValue(BYTE val)
{
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwAlcmButtonAddr), 1);
	*(BYTE*)cdwAlcmButtonAddr = val;
	g_MemoryHelper->ReProtect();
}
void AlchemyPatch::PatchAlchemyImagePath(BYTE val1, BYTE val2, BYTE val3)
{
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwButtonImagePath), 4);
	*(BYTE*)(cdwButtonImagePath + 1) = val1;
	*(BYTE*)(cdwButtonImagePath + 2) = val2;
	*(BYTE*)(cdwButtonImagePath + 3) = val3;
	g_MemoryHelper->ReProtect();
}
void OnAlchemyEnchantWnd()
{
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwAlchemyIcons), 1);
	*(BYTE*)cdwAlchemyIcons = 0x6B;
	g_MemoryHelper->ReProtect();
	patched = false;
	AlchemyPatch::PatchAlchemyValue(0xF);
	AlchemyPatch::PatchAlchemyImagePath(0x75, 0xFF, 0xD7); // push alcmButtonFreeSpaceAddr
}
void OnAlchemyEnchantWndClose()
{
	AlchemyPatch::PatchAlchemyValue(0xA);
	AlchemyPatch::PatchAlchemyImagePath(0x70, 0x7D, 0xE1); // PUSH 0xE17D70
	// skill icons
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(cdwAlchemyIcons), 1);
	*(BYTE*)cdwAlchemyIcons = 0x67;
	g_MemoryHelper->ReProtect();
}

__declspec(naked) void ASM_OnAlchemyWndCalled()
{
	__asm
	{
		push cdwCNIFAlchemyWnd
		pushad
		pushfd
		call OnAlchemyEnchantWnd
		popfd
		popad
		jmp cdwAlchemyWindowJmpBackAddr
	}
}

__declspec(naked) void ASM_OnAlchemyWndClosed()
{
	__asm
	{
		TEST BYTE PTR[ESP + 8], 1;
		pushad;
		pushfd;
		CALL OnAlchemyEnchantWndClose;
		popfd;
		popad;
		jmp cdwOnAlchemyClosedJmpback;
	}
}
void AlchemyPatch::Initialize()
{
	std::string addr = "interface\\alchemy\\alcm_windowclose.ddj";
	g_MemoryHelper->UnProtect(reinterpret_cast<void*>(alcmButtonFreeSpaceAddr), addr.length());
	for (size_t i = 0; i < addr.length(); i++)
	{
		*(BYTE*)(alcmButtonFreeSpaceAddr + i) = addr[i];
	}
	g_MemoryHelper->ReProtect();
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(0x00798E37), ASM_OnAlchemyWndCalled);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(0x0059E538), ASM_OnAlchemyWndClosed);

}