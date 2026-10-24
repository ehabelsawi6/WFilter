#include "CharacterSpawn.h"
#include "../../GameMain/GameMain.h"
//#include "../../D3DEngine/GUIs//AccountLockedWindow.h"

const DWORD cdwOnCharacterSpawnAddr = 0x009DE626;
const DWORD cdwOnCharacterSpawnAddrJmpback = 0x009DE62B;
const DWORD cdwOnCharacterRefreshCall = 0x008B4400;
const DWORD cdwOnCharacterRefreshJmpback = 0x009C292A;

CharacterSpawn* g_CharacterSpawn;
//AccountLockedWindow* accountLockedWindow;

__declspec(naked) void ASM_NewTitleColor()
{
	__asm
	{
		CALL cdwOnCharacterRefreshCall;
		pushad;
		pushfd;
		push esi;
		call CharacterSpawn::OnRefresh;

		popfd;
		popad;
		jmp cdwOnCharacterRefreshJmpback;
	}
}

void CharacterSpawn::OnRefresh(CICPlayer* player)
{
	if (g_CICPlayer && player && ((*(DWORD*)player == (0xDE2E7C) || *(DWORD*)player == (0xDE2C24))))
	{
		auto PlayerHwanLevel = player->GetHwanLevel();
		if (PlayerHwanLevel == 255)
		{
			auto customtitle = g_GlobalDataMgr->m_CustomTitles.find(player->GetCharName()->c_str());
			if (customtitle != g_GlobalDataMgr->m_CustomTitles.end())
			{
				w_string_last wstrptr = w_string_last(g_StringHelper->s2ws(customtitle->second).append(L" ").c_str());
				player->GetTitleFontTexture()->SetText(&wstrptr);
			}
		}
		
		auto hasTitleColor = g_GlobalDataMgr->m_TitleColors.find(player->GetCharName()->c_str());
		if (hasTitleColor != g_GlobalDataMgr->m_TitleColors.end())
			player->GetTitleFontTexture()->SetColor(hasTitleColor->second);

		if (g_GlobalDataMgr->GetCurrentRegion() == 25580)
		{
			if (player == g_CICPlayer)
				player->SetClothes(4);
			else
				player->SetClothes(3);
		}
	}
}

__declspec (naked) void ASM_OnCharacterSpawnAttempt()
{
	__asm
	{
		pushad;
		pushfd;

		//lea eax, [edi + 0x114];
		//push eax;
		PUSH EDI;

		CALL CharacterSpawn::OnSpawn;

		popfd;
		popad;
		MOV EAX, DWORD PTR[EDX + 0x40];
		MOV ECX, EDI;
		jmp cdwOnCharacterSpawnAddrJmpback;
	}
}
void CharacterSpawn::OnUpdate(CMsgStreamBuffer* packet)
{
	auto PlayerUniqueID = packet->Read<uint32_t>();
	auto TargetPlayer = g_CICPlayer->GetCICPlayerByUniqueID(PlayerUniqueID);
	if (TargetPlayer)
	{
		auto NameColor = packet->Read<uint32_t>();//namecolor
		auto TitleColor = packet->Read<uint32_t>();//titlecolor
		auto HasCustomTitle = packet->Read<uint8_t>();//has custom title?
		if (HasCustomTitle)
		{
			auto HwanLevel = TargetPlayer->GetHwanLevel();
			auto Custom_Title = packet->ReadStringA();

			bool hasFound = false;
			for (auto &pCustomTitle : g_GlobalDataMgr->m_CustomTitles)
			{
				if (pCustomTitle.first == TargetPlayer->GetCharName()->c_str())
				{
					hasFound = true;
					pCustomTitle.second = Custom_Title;


					if (HwanLevel == 255)
					{
						w_string_last strptr = w_string_last(g_StringHelper->s2ws(Custom_Title).append(L" ").c_str());
						TargetPlayer->GetTitleFontTexture()->SetText(&strptr);
					}
				}
			}
			if (!hasFound)
			{
				g_GlobalDataMgr->m_CustomTitles.insert({ TargetPlayer->GetCharName()->c_str(), Custom_Title });


				if (HwanLevel == 255)
				{
					w_string_last strptr = w_string_last(g_StringHelper->s2ws(Custom_Title).append(L" ").c_str());
					TargetPlayer->GetTitleFontTexture()->SetText(&strptr);
				}
			}

			if (g_CICPlayer)
			{
				auto SelfUniqueID = g_CICPlayer->GetUniqueID();
				if (PlayerUniqueID == SelfUniqueID)
				{
					auto hasTitle = g_GlobalDataMgr->m_CurrentTitlesList.find(255);
					if (hasTitle == g_GlobalDataMgr->m_CurrentTitlesList.end())
					{
						g_GlobalDataMgr->m_CurrentTitlesList.insert({ 255, Custom_Title });
					}
					else
					{
						for (auto &titles : g_GlobalDataMgr->m_CurrentTitlesList)
						{
							if (titles.first == 255)
							{
								titles.second = Custom_Title;
							}
						}
					}

					if (HwanLevel == 255)
					{
						w_string_last strptr = w_string_last(g_StringHelper->s2ws(Custom_Title).append(L" ").c_str());
						TargetPlayer->GetTitleFontTexture()->SetText(&strptr);
					}
				}
			}
		}
		if (NameColor != 0)
		{
			TargetPlayer->UpdateNameColor(NameColor);
			bool isFoundAndUpdated = false;
			for (auto &Player : g_GlobalDataMgr->m_NameColors)
			{
				if (Player.first == TargetPlayer->GetCharName()->c_str())
				{
					isFoundAndUpdated = true;
					Player.second = NameColor;
					break;
				}
			}
			if (!isFoundAndUpdated)
				g_GlobalDataMgr->m_NameColors.insert({ TargetPlayer->GetCharName()->c_str(), NameColor });
		}
		else if (NameColor == 0 && TargetPlayer) {

			TargetPlayer->UpdateNameColor(0xFFFFFF);

			if (g_GlobalDataMgr->m_NameColors.find(TargetPlayer->GetCharName()->c_str()) != g_GlobalDataMgr->m_NameColors.end())
			{
				g_GlobalDataMgr->m_NameColors.erase(TargetPlayer->GetCharName()->c_str());
			}
		}
		if (TitleColor != 0)
		{
			TargetPlayer->GetTitleFontTexture()->SetColor(TitleColor);

			bool isFoundAndUpdated = false;
			for (auto &Player : g_GlobalDataMgr->m_TitleColors)
			{
				if (Player.first == TargetPlayer->GetCharName()->c_str())
				{
					isFoundAndUpdated = true;
					Player.second = TitleColor;
					break;
				}
			}
			if (!isFoundAndUpdated)
				g_GlobalDataMgr->m_TitleColors.insert({ TargetPlayer->GetCharName()->c_str(), TitleColor });
		}
		else if(TitleColor == 0 && TargetPlayer) {

			TargetPlayer->GetTitleFontTexture()->SetColor(0xFFFF00);

			if (g_GlobalDataMgr->m_TitleColors.find(TargetPlayer->GetCharName()->c_str()) != g_GlobalDataMgr->m_TitleColors.end())
			{
				g_GlobalDataMgr->m_TitleColors.erase(TargetPlayer->GetCharName()->c_str());
			}
		}
		auto CustomIcon = packet->Read<uint32_t>();
		if (CustomIcon != 0)
		{
			auto iconData = g_GlobalDataMgr->m_CharacterIcons.find(TargetPlayer->GetCharName()->c_str());
			if (iconData == g_GlobalDataMgr->m_CharacterIcons.end())
			{
				g_GlobalDataMgr->m_CharacterIcons.insert({ TargetPlayer->GetCharName()->c_str(), CustomIcon });
			}
			else // if exists
			{
				for (auto &val : g_GlobalDataMgr->m_CharacterIcons)
				{
					if (val.first == TargetPlayer->GetCharName()->c_str())
					{
						if (val.second != CustomIcon)
							val.second = CustomIcon;
					}
				}
			}
		}
		else if(TargetPlayer && TargetPlayer->GetCharName()->c_str() != L"")
		{
			if (g_GlobalDataMgr->m_CharacterIcons.find(TargetPlayer->GetCharName()->c_str()) != g_GlobalDataMgr->m_CharacterIcons.end())
			{
				g_GlobalDataMgr->m_CharacterIcons.erase(TargetPlayer->GetCharName()->c_str());
			}
		}
		//auto CustomTitleCredits = packet->Read<uint8_t>();
		auto DSPoints = packet->Read<uint32_t>();

		if (g_CICPlayer)
		{
			auto SelfUniqueID = g_CICPlayer->GetUniqueID();
			if (TargetPlayer->GetUniqueID() == g_CICPlayer->GetUniqueID())
			{
				//g_GlobalDataMgr->m_CustomTitleCredits = CustomTitleCredits;
				g_GlobalDataMgr->DSPoints = DSPoints;
				
			}
		}

	/*	auto isLocked = packet->Read<uint8_t>();

		if (isLocked) {
			if (!accountLockedWindow)
			{
				accountLockedWindow = new AccountLockedWindow();
				accountLockedWindow->Show(std::shared_ptr<Form>(accountLockedWindow));
			}
		}*/
	}
}
void CharacterSpawn::OnSpawn(CICPlayer* player)
{
	if (g_CICPlayer && player && *(DWORD*)player == 0xDE2E7C)
	{
		auto PlayerUniqueID = player->GetUniqueID();
		CMsgStreamBuffer* request = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
		request->Write<uint8_t>(MsgOpcodeTypes::OnCharacterInfoRequest);
		request->Write<uint32_t>(PlayerUniqueID);
		request->SendToServer();
	}
}

void CharacterSpawn::Initialize()
{
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnCharacterSpawnAddr), ASM_OnCharacterSpawnAttempt);
	g_MemoryHelper->replaceOffset(0x009D0221, g_MemoryHelper->addr_from_this(&CICPlayer::UpdateNameColor)); //charname color hook
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(0x009C2925), ASM_NewTitleColor);

	g_MemoryHelper->ReplaceByte(reinterpret_cast<void*>(0x00A60FC4), (int8_t)0xEB);
	g_MemoryHelper->ReplaceByte(reinterpret_cast<void*>(0x00A60FA6), (int8_t)0xEB);
}
