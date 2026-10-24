#include "CharacterIcons.h"
#include "../../GameMain/GameMain.h"
const DWORD fornopping = 0x009DED3D;
const DWORD onCharIconHookAddr = 0x009DED43;
const DWORD onCharIconHookAddrJmpback = 0x009DED4C;
const DWORD onCharIconIgnore = 0x9DEDE1;
void* lastFoundedIcon;

__declspec(naked) void OnIconCheck()
{
	__asm
	{
		pushad;
		pushfd;
		PUSH ECX;
		CALL CharacterIcons::OnCharacterIcon;
		CMP AL, TRUE;
		je patch;
		popfd;
		popad;
		jmp onCharIconIgnore;
	patch:
		popfd;
		popad;
		MOV EDX, DWORD PTR[0x110AB38];
		MOV EAX, lastFoundedIcon;
		jmp onCharIconHookAddrJmpback;
	}
}

void CharacterIcons::Initialize()
{
	g_MemoryHelper->SetNop(onCharIconHookAddr, 6);
	g_MemoryHelper->SetNop(fornopping, 6);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(onCharIconHookAddr), OnIconCheck);
}

bool __stdcall CharacterIcons::OnCharacterIcon(CICPlayer * player)
{
	if (g_CICPlayer && player && (*(DWORD*)player == (0xDE2E7C) || *(DWORD*)player == (0xDE2C24)))
	{
		if (g_CICPlayer != player && g_GlobalDataMgr->m_PartyDisabledRegions.find(g_GlobalDataMgr->GetCurrentRegion()) != g_GlobalDataMgr->m_PartyDisabledRegions.end())
		{
			lastFoundedIcon = nullptr;
			return FALSE;
		}
		else if (player->GetJobStatus() != 4)
		{
			lastFoundedIcon = nullptr;
			return FALSE;
		}
			auto foundedInfo = g_GlobalDataMgr->m_CharacterIcons.find(player->GetCharName()->c_str());
			if (foundedInfo != g_GlobalDataMgr->m_CharacterIcons.end())
			{
				auto foundedTheIcon = g_GlobalDataMgr->m_IconsData.find(foundedInfo->second);
				if (foundedTheIcon != g_GlobalDataMgr->m_IconsData.end())
				{
					lastFoundedIcon = foundedTheIcon->second;
					return TRUE;
				}
			}
	}
	lastFoundedIcon = nullptr;
	return FALSE;
}
