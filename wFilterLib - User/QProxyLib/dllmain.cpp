// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "GameMain/GameMain.h"
#include "Defines.h"
#include "D3DEngine/D3DMisc.h"
#include "D3DEngine/ResourceManager.h"
#include "Character/Spawn/CharacterSpawn.h"
#include "GameStuff/CGInterface/IFSlotWithHelp.h"
#include "Licensing/LicenseManager.h"
#include "ClientCommonSettings/ClientCommonSettings.h"
#include "GameFeatures/OldItemMall/OldItemMall.h"
#include "GameStuff/InterfaceActions/InterfaceActions.h"
#include "GameFeatures/ParamRare/CParamRare.h"
#include "GameFeatures/OldAlchemy/OldAlchemy.h"
#include "GameFeatures/OldLoginScreen/char_select.h"
#include "GameFeatures/OldExpBar/CNIFUnderMenuBar.h"
#include "WebManager/WebManager.h"
#include "IFItemComparison.h"
#include "GameStuff/OldThreeJob/OldThreeJob.h"
//
/*Discord SDK*/


 std::string g_DiscordLargeImageText = VMProtectDecryptStringA("wFilter V3");
 std::string g_DiscordStatusMessage = VMProtectDecryptStringA("Loading...");
 std::string g_DiscordDetails = VMProtectDecryptStringA("");
 std::string g_Discord_App_Id = VMProtectDecryptStringA("1004056809520255178");



/*End of Discord SDK*/

HMODULE g_hModule;
HMODULE sro_client = 0;

void InitializeLibrary()
{


	g_GlobalItemLinking = new GlobalItemLinking();
	g_GlobalItemLinking->Initialize();
	Sleep(1000);
	g_MemoryHelper = new MemoryHelper();
	g_StringHelper = new CStringHelper();
	g_NetCustoms = new CNetCustoms();
	g_MsgHandler = new CMsgHandler();
	g_Character = new Character();
	g_ResourceMgr = new ResourceManager();
	g_D3DMisc = new D3DMisc();
	g_CGEffSoundBody = new CGEffSoundBody();
	g_DiscordMgrAddon = new Discord();
	g_PHBotMgr = new PHBotManager();
	g_ChatManager = new ChatManager();
	g_GlobalDataMgr = new CGlobalDataManager();
	g_CharacterSpawn = new CharacterSpawn();
	g_CharacterIcons = new CharacterIcons();
	ClientCommonSettings* g_Settings = new ClientCommonSettings();

	CMemPoolManager::Initialize();
	g_NetCustoms->Initialize();
	g_MsgHandler->SetupHandlers();

	g_Character->Init();
	g_ResourceMgr->Initialize();
//	g_DiscordMgrAddon->Initialize();
//	g_DiscordMgrAddon->Update();
	g_CharacterSpawn->Initialize();
	g_CharacterIcons->Initialize();
	g_Settings->Initialize();

	g_D3DEngine = new D3DEngine();
	g_GameCommonHooks = new GameCommonHooks();

	//isro sys Comparison with old tool tip
	g_MemoryHelper->replaceOffset(0x00682AFC, g_MemoryHelper->addr_from_this(&CIFItemComparison::AppendAdvancedInfo));
	g_MemoryHelper->replaceOffset(0x00682D6E, g_MemoryHelper->addr_from_this(&CIFItemComparison::AppendAdvancedInfo));
	g_MemoryHelper->replaceOffset(0x00682FBE, g_MemoryHelper->addr_from_this(&CIFItemComparison::AppendAdvancedInfo));
	g_MemoryHelper->replaceOffset(0x0068320E, g_MemoryHelper->addr_from_this(&CIFItemComparison::AppendAdvancedInfo));

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )	
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);
		g_hModule = hModule;
		sro_client = GetModuleHandle(NULL);
#ifdef DevConsole
		AllocConsole();
		freopen("CONOUT$", "w+", stdout);
		SetConsoleTitleA("Debug Console");
#endif
		//char_select_override();
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitializeLibrary, NULL, 0, NULL);
	} 
		break;
    case DLL_PROCESS_DETACH:
		return FALSE;
        break;
    }
    return TRUE;
}

