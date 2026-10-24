#include "GameCommonHooks.h"
#include "../GameMain/GameMain.h"
#include "D3DEngine.h"
#include "D3DMisc.h"
#include "GUIs/IconWindow.h"
#include "../GameStuff/CICPlayer/CICPlayer.h"

using namespace OSHGui;
extern IconWindow* g_IconWindow;
extern bool g_isDrawable;
/*ADDRS*/

const DWORD cdwEndFrameHookAddr = (0x00BA57D2);
const DWORD cdwEndFrameHookJmpback = (cdwEndFrameHookAddr + 6);

HRESULT __stdcall nReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
typedef HRESULT(APIENTRY* Reset_t) (LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);

Reset_t g_pReset;

bool g_PlayerSpawned;

HRESULT __stdcall nReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	Application::Instance().GetRenderer().PreD3DReset();

	HRESULT hResult = g_pReset(pDevice, pPresentationParameters);
	if (hResult == D3D_OK)
	{
		Application::Instance().GetRenderer().PostD3DReset();
		auto size_f = Application::Instance().GetRenderer().GetDisplaySize();
		g_IconWindow->SetLocation(size_f.Width - 300, 178);
	}

	return hResult;
}

void __stdcall OnEndFrame()
{
	if (!g_CICPlayer)
	{
		Application::Instance().Disable();
	}
	if (g_isDrawable && g_CICPlayer && g_PlayerSpawned)
	{
		if (!Application::Instance().IsEnabled())
			Application::Instance().Enable();
		Application::Instance().GetRenderer().BeginRendering();
		Application::Instance().Render();
		Application::Instance().GetRenderer().EndRendering();
	}
}

__declspec(naked) void IL_OnAfterEndFrame()
{

	__asm pushad;
	__asm pushfd;

	OnEndFrame();

	__asm popfd;
	__asm popad;

	//old code, D3D device if i remember right...
	__asm mov ecx, dword ptr ds : [0x110F7EC];

	__asm jmp cdwEndFrameHookJmpback;
}

bool GameCommonHooks::InstallEndFrameHook()
{
	//Set the post-EndFrame hook
	auto addr = reinterpret_cast<void*>(cdwEndFrameHookAddr);
	DWORD oldProtect = 0;
	VirtualProtect(addr, 6, PAGE_EXECUTE_READWRITE, &oldProtect);
	g_MemoryHelper->SetTrampoline(true, addr, IL_OnAfterEndFrame, 6);

	return true;
}

bool GameCommonHooks::InstallResetFrameHook()
{
	auto d3dDevice9 = g_D3DMisc->GetDevice();
	// Retrieve our endscene address and reset for futher hooking if needed
	PDWORD32 pdwDeviceTable = (PDWORD32)d3dDevice9;
	pdwDeviceTable = (PDWORD32)pdwDeviceTable[0];
	LPVOID lp_Reset = (LPVOID)pdwDeviceTable[16];//reset pointer

	//Set the original ptr
	g_pReset = (Reset_t)lp_Reset;

	DetourTransactionBegin();
	DetourAttach(&(PVOID&)g_pReset, nReset);
	DetourTransactionCommit();

	return true;
}

GameCommonHooks::GameCommonHooks()
{
	InstallResetFrameHook();
	InstallEndFrameHook();
}

GameCommonHooks::~GameCommonHooks()
{
}