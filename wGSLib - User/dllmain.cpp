


// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Library.h"
#include <ctime>
#include <VMProtectSDK.h>

#define Anoha
//#define Exorue

//HWID gen
#include <IPHlpApi.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"VMProtectSDK32.lib")



static HMODULE hm = NULL;

void InitializeLibrary()
{
    AllocConsole();
    freopen("CONOUT$", "w+", stdout);
 //   std::cout << __FUNCTION__ << " - entered" << std::endl;

#ifdef REMOTE_DEBUG
    MessageBox(0, L"Please attach debugger", L"Please attach debugger", MB_OK);
#endif


    CLibrary::Initialize();
}

__declspec(dllexport) void libLoad() {

    InitializeLibrary();

}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        hm = hModule;

        InitializeLibrary();
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


