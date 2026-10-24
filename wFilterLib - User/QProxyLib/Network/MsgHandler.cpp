#include "MsgHandler.h"
#include "NetCustoms.h"
#include "../GameMain/GameMain.h"
#include "../Defines.h"
#include "../GameFeatures/HWIDManager/HWIDManager.h"
#include "../D3DEngine/GUIs/ChestWindow.h"
#include "../GameStuff/CICPlayer/CICPlayer.h"
#include "../Character/Spawn/CharacterSpawn.h"
#include "../D3DEngine/GUIs/DPSMeterWindow.h"
#include "../D3DEngine/GUIs/UniqueStatus.h"
#include "../D3DEngine/GUIs/Top5KillCounter.h"
#include "../D3DEngine/GUIs/Top5FTWKillCounter.h"
//#include "../D3DEngine/GUIs/JobWindow.h"
#include "../GameStuff/CGInterface/CGInterface.h"
#include "../GameStuff/CharacterDependentData/CharacterDependentData.h"
#include "../Emojis/Emojis.h"
#include "../GameStuff/CGInterface/IFMinimap.h"
#include "../D3DEngine/GUIs/EventTimesWindow.h"
#include "../D3DEngine/GUIs//AccountLockedWindow.h"
#include "../D3DEngine/GUIs/Pandora/MainMenuWindow.h";
#include "../D3DEngine/GUIs/TitleManager.h"
#include "../D3DEngine/GUIs/GrantNameWindow.h"
#include "../D3DEngine/GUIs/DynamicShop.h"
#include "../D3DEngine/GUIs/CustomTitleWindow.h"

/*GUI STUFF*/
extern ChestWindow* chestWindow;
DPSMeterWindow* pDpsMeterWindow;
Top5KillCounterWindow* pTop5KillCounterWindow;
Top5FTWKillCounterWindow* pTop5FTWKillCounterWindow;
extern UniqueStatusWindow* uniqueStatusWindow;
extern EventTimesWindow* eventTimesWindow;
AccountLockedWindow* accountLockedWindow;
extern MainMenuWindow* mainMenuWindow;
extern TitleManagerWindow* titleManagerWindow;
extern GrantNameWindow* grantNameWindow;
extern DynamicShopWindow* dynamicShopWindow;
extern CustomTitleWindow* customTitleWindow;

//extern JobWindow* jobWindow;
bool g_DpsMeterUpdated = false;
/*END OF GUI STUFF*/

//#define SR_DEBUG

E_MSGHOOK_RESULT DefaultInMsgHandler(CMsgStreamBuffer*);
E_MSGHOOK_RESULT DefaultOutMsgHandler(CMsgStreamBuffer*);

E_MSGHOOK_RESULT HandleCharDataBegin(CMsgStreamBuffer*);
E_MSGHOOK_RESULT HandleCharData(CMsgStreamBuffer*);
E_MSGHOOK_RESULT HandleCharDataEnd(CMsgStreamBuffer*);
E_MSGHOOK_RESULT HandleCharSelection(CMsgStreamBuffer*);
E_MSGHOOK_RESULT HandleCustoms(CMsgStreamBuffer*);
E_MSGHOOK_RESULT HandleEffectUpdate(CMsgStreamBuffer*);


extern bool g_PlayerSpawned;

CMsgHandler::CMsgHandler()
{
	//m_GameUpdateHandler = new GameUpdateHandler();
	//m_UserActionHandler = new UserActionHandler();
	//m_MiscHandler = new MiscHandler();
	//m_ChatCommands = new ChatCommands();
}

CMsgHandler::~CMsgHandler()
{

}

void CMsgHandler::SetupHandlers()
{
	g_NetCustoms->SetDefaultInMsgHandler(DefaultInMsgHandler);
	g_NetCustoms->SetDefaultOutMsgHandler(DefaultOutMsgHandler);

	g_NetCustoms->SetInMsgHandler(MsgOpcodes::SERVER_CHARACTER_SCREEN, HandleCharSelection);

	g_NetCustoms->SetInMsgHandler(MsgOpcodes::SERVER_CHAR_DATA_BEGIN, HandleCharDataBegin);
	g_NetCustoms->SetInMsgHandler(MsgOpcodes::SERVER_CHAR_DATA, HandleCharData);
	g_NetCustoms->SetInMsgHandler(MsgOpcodes::SERVER_CHAR_DATA_END, HandleCharDataEnd);

	g_NetCustoms->SetInMsgHandler(MsgOpcodes::SERVER_CUSTOM, HandleCustoms);
	g_NetCustoms->SetInMsgHandler(MsgOpcodes::AFK_BUBBLES, HandleEffectUpdate);
}
void RemoveExistingUniqueData(const DWORD dead_object)
{
	if (g_CICPlayer)
	{
		bool remove_key_player = false;
		bool remove_key_unique = false;

		uint32_t remove_val_key = 0;

		auto it_1 = g_GlobalDataMgr->UniqueTargetHashmapPlayer.find(dead_object);
		if (it_1 != g_GlobalDataMgr->UniqueTargetHashmapPlayer.end()) //player gitti, player map'ten playerı sil, unique map'ten value 0 yap.
		{
			//printf("player kayboldu\n");
			remove_key_player = true;
			remove_val_key = it_1->second;
		}

		if (!remove_key_player) //player değil ise bak
		{
			auto it_2 = g_GlobalDataMgr->UniqueTargetHashmap.find(dead_object);
			if (it_2 != g_GlobalDataMgr->UniqueTargetHashmap.end()) //unique gitti, player mapten unique'i 0 yap, unique map'ten unique'i sil.
			{
				//printf("unique kayboldu\n");
				remove_key_unique = true;
				remove_val_key = it_2->first;

				CICPlayer* LastTarget = g_CICPlayer->GetCICPlayerByUniqueID(it_2->second);
				if (LastTarget)
				{
					LastTarget->RemoveEffect(g_GlobalDataMgr->GetEffectIdByName(L"SYSTEM_AGGRO_EFFECT"));
				}
			}
		}
		else //player gitmiş
		{
			g_GlobalDataMgr->UniqueTargetHashmapPlayer.erase(remove_val_key);

			if (g_GlobalDataMgr->UniqueTargetHashmap.count(remove_val_key) > 0)
				g_GlobalDataMgr->UniqueTargetHashmap[remove_val_key] = 0;

			return;
		}

		if (remove_key_unique)
		{
			g_GlobalDataMgr->UniqueTargetHashmap.erase(remove_val_key);

			if (g_GlobalDataMgr->UniqueTargetHashmapPlayer.count(remove_val_key) > 0)
				g_GlobalDataMgr->UniqueTargetHashmapPlayer[remove_val_key] = 0;
		}
	}
}

//s->c //lemme do some small cleanup
int8_t g_GroupSpawn_Type;
std::vector<DWORD> g_despawned_objects;
E_MSGHOOK_RESULT DefaultInMsgHandler(CMsgStreamBuffer* packet)
{
#ifdef IOMsgOutput
	printf("NetMsgIn 0x%02X\n", packet->GetID());
#endif
	const uint16_t opcode = packet->GetID();
	bool handled = false;


	
	if (opcode == MsgOpcodes::SERVER_ENVIROMENT_CELESTIAL_POSITION) {

		//auto pCIFMiniMap = (CIFMiniMap*)g_CGInterface->field_36C.GetGUIObjectByID(10, 1);
		if (g_CICPlayer /*&& pCIFMiniMap*/)
		{
		//	auto RegionStr = g_StringHelper->ws2s(std::wstring(pCIFMiniMap->MiniMapTitleLabel->GetText()));

			CMsgStreamBuffer* pCharInfo = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
			pCharInfo->Write<uint8_t>(MsgOpcodeTypes::ClientInfo);
			pCharInfo->Write<uint8_t>(g_CICPlayer->GetJobStatus());
			pCharInfo->Write<uint8_t>(g_CICPlayer->level);
			//pCharInfo->WriteStringA(RegionStr);
			pCharInfo->SendToServer();
		}

		handled = false;
	}
	if (opcode == MsgOpcodes::SERVER_ENTITY_LEVEL_UP) {

		uint32_t uniqueId = packet->Read<uint32_t>();

		if (uniqueId == g_CICPlayer->GetUniqueID()) {

			//auto pCIFMiniMap = (CIFMiniMap*)g_CGInterface->field_36C.GetGUIObjectByID(10, 1);
			//auto RegionStr = g_StringHelper->ws2s(std::wstring(pCIFMiniMap->MiniMapTitleLabel->GetText()));

			CMsgStreamBuffer* pCharInfo = new CMsgStreamBuffer(MsgOpcodes::CLIENT_CUSTOM);
			pCharInfo->Write<uint8_t>(MsgOpcodeTypes::ClientInfo);
			pCharInfo->Write<uint8_t>(g_CICPlayer->GetJobStatus());
			pCharInfo->Write<uint8_t>(g_CICPlayer->level);
			//pCharInfo->WriteStringA(RegionStr);
			pCharInfo->SendToServer();
		}

		handled = false;
	}
	if (opcode == MsgOpcodes::SERVER_GROUP_SPAWN_BEGIN)
	{
		g_GroupSpawn_Type = packet->Read<uint8_t>();

		handled = false;
	}
	if (opcode == MsgOpcodes::SERVER_GROUP_SPAWN_DATA) // possible the crash is here
	{
		if (g_GroupSpawn_Type == 2)
		{
			for (size_t i = 0; i < (packet->GetLength() / 4); i++)
			{
				DWORD dead_object = packet->Read<DWORD>();
				g_despawned_objects.push_back(dead_object);
			}
		}
		handled = false;
	}
	if (opcode == MsgOpcodes::SERVER_GROUP_SPAWN_END)
	{
		if (g_GroupSpawn_Type == 2)
		{
			for (auto& shit : g_despawned_objects)
			{
				RemoveExistingUniqueData(shit);
			}

			g_despawned_objects.clear();
			g_despawned_objects.shrink_to_fit();
		}
		handled = false;
	}
	if (opcode == MsgOpcodes::SERVER_SINGLE_OBJECT_DESPAWN)
	{
		if (g_CICPlayer)
		{
			DWORD dead_object = packet->Read<DWORD>();
			RemoveExistingUniqueData(dead_object);
		}
		handled = false;
	}
	if (opcode == 0x3305)
	{
		auto currentRegionID = g_GlobalDataMgr->GetCurrentRegion();
		//printf("current region = %d\n", currentRegionID);
		if (g_GlobalDataMgr->m_PartyDisabledRegions.find(currentRegionID) != g_GlobalDataMgr->m_PartyDisabledRegions.end())
		{
			if (g_CCharacterDependentData.PartyNumber > 0)
			{
				CMsgStreamBuffer* RemoveFromList = new CMsgStreamBuffer(0x706B);
				RemoveFromList->Write<uint32_t>(g_CCharacterDependentData.PartyNumber);
				RemoveFromList->SendToServer();
			}
			if (g_CCharacterDependentData.IsInParty())
			{
				CMsgStreamBuffer* pBuffer = new CMsgStreamBuffer(0x7061);
				pBuffer->SendToServer();
			}
		}
	}
	if (opcode == MsgOpcodes::SERVER_SKILL_CASTING_DATA)
	{


		uint8_t bSuccessFlag = packet->Read<uint8_t>();
		if (g_CICPlayer && bSuccessFlag == 1 && packet->GetLength() >= 20) // i'am just checking static size here, so i guess no any problems may occur while parsing.
		{
			uint8_t _type = packet->Read<uint8_t>();
			uint8_t _reason = packet->Read<uint8_t>();
			if (_type == 2)//Attack action
			{
				packet->Read<uint32_t>();// SKILL ID
				auto AttackerID = packet->Read<uint32_t>();// Skill Owner Unique ID
				packet->Read<uint32_t>();// Skill Instance Unique ID
				auto AttackedID = packet->Read<uint32_t>();// MAIN TARGET Unique ID
				if (AttackerID > 0)//Attacker ID will never be 0
				{
					//well, i'm stressed the one that i've used here,GetCICPlayerByUniqueID this function is nullable
					//well, no problems but I firstly need to verify that parsing xD kk
					auto CICAttacker = g_CICPlayer->GetCICPlayerByUniqueID(AttackerID);
					auto check_shit = *(DWORD*)(CICAttacker);
					if (CICAttacker && check_shit == 0xDE26C4) // checking if the unique id is MOB exactly a MOnster you know :D ye but the thing is that those client functions are already crashable
					{

						auto m_ObjectData = g_CGlobalDataManager->GetGenericObjectDataByID(CICAttacker->GetObjID());
						if (m_ObjectData && (m_ObjectData->rarity == 3 || m_ObjectData->rarity == 8))
						{

							//unique amk

							//printf("ptr = %02x\n", CICAttacker);
							auto effect = g_GlobalDataMgr->GetEffectIdByName(L"SYSTEM_AGGRO_EFFECT");
							auto it = g_GlobalDataMgr->UniqueTargetHashmap.find(AttackerID);
							if (it == g_GlobalDataMgr->UniqueTargetHashmap.end()) // first attack, let the shit begin.
							{
								g_GlobalDataMgr->UniqueTargetHashmap[AttackerID] = AttackedID;//i'am using these maps for unique target, lel this packet is a pain in the ass, i hope you are parsing it correctly xDD
								g_GlobalDataMgr->UniqueTargetHashmapPlayer[AttackedID] = AttackerID;

								auto CICAttacked = g_CICPlayer->GetCICPlayerByUniqueID(AttackedID);
								if (CICAttacked)
								{
									CICAttacked->MakeEffect(effect);
								}
							}
							else
							{
								if (it->second != AttackedID) // Attacker is changed, let them switch.
								{
									uint32_t oldTarget = it->second;

									auto CICOldTarget = g_CICPlayer->GetCICPlayerByUniqueID(oldTarget);
									if (CICOldTarget) CICOldTarget->RemoveEffect(effect);

									auto CICNewTarget = g_CICPlayer->GetCICPlayerByUniqueID(AttackedID);
									if (CICNewTarget) CICNewTarget->MakeEffect(effect);


									g_GlobalDataMgr->UniqueTargetHashmap[AttackerID] = AttackedID;
									g_GlobalDataMgr->UniqueTargetHashmap[AttackedID] = AttackedID;

									g_GlobalDataMgr->UniqueTargetHashmapPlayer.erase(oldTarget);
								}
								else if (it->second == AttackedID) //attacker is same, check if he still have the effect
								{
									auto CICCurrentTarget = g_CICPlayer->GetCICPlayerByUniqueID(AttackedID);
									if (CICCurrentTarget)
									{
										if (CICCurrentTarget->GetObjEffect() != effect)//Lemme show u so its safe to use.
											CICCurrentTarget->MakeEffect(effect);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (opcode == MsgOpcodes::SERVER_CHAT)
	{
		auto ChatType = packet->Read<uint8_t>();
		if (ChatType == 0x06) // Global
			handled = true;
	}
	if (opcode == MsgOpcodes::SERVER_TELEPORT)
		g_PlayerSpawned = false;
	/*if (opcode == MsgOpcodes::SERVER_INVENTORY_RESPONSE)
	{
		if (packet->Read<int8_t>() == 1 && packet->Read<int8_t>() == 0x18)
		{
			auto MallPtr = (IFItemMall*)g_CGInterface->field_36C.GetGUIObjectByID(167, 1);
			if (MallPtr)
			{
				MallPtr->isDisabled = 0;
			}
			return E_MSGHOOK_RESULT::BLOCK;
		}
		if (chestWindow)
			chestWindow->UpdateRemainingInventory();
	}*/

	return (handled) ? E_MSGHOOK_RESULT::BLOCK : E_MSGHOOK_RESULT::PASS_THROUGH;
}
E_MSGHOOK_RESULT DefaultOutMsgHandler(CMsgStreamBuffer* packet)
{
#ifdef IOMsgOutput
	printf("NetMsgOut 0x%02X\n", packet->GetID());
#endif
	const uint16_t opcode = packet->GetID();
	bool handled = false;
	if (opcode == 0x7021)
	{
		/*auto PCIFReverse = g_CGInterface->field_36C.GetGUIObjectByID(0, 1);
		printf("found window = %02x\n", PCIFReverse);*/
		auto pCIFMiniMap = (CIFMiniMap*)g_CGInterface->field_36C.GetGUIObjectByID(10, 1);
		if (pCIFMiniMap)
		{
			if (g_CICPlayer && g_CICPlayer->GetJobStatus() == 4)
			{
				auto NameStr = g_StringHelper->ws2s(g_CICPlayer->GetCharName()->c_str());
				g_DiscordMgrAddon->UpdateDetails("" + NameStr + " | Lv: " + std::to_string(g_CICPlayer->level) + "");
			}
			else
			{
				auto NameStr = g_StringHelper->ws2s(g_CICPlayer->GetCharName()->c_str());
				g_DiscordMgrAddon->UpdateDetails("Jobbing");
			}

			auto RegionStr = g_StringHelper->ws2s(std::wstring(pCIFMiniMap->MiniMapTitleLabel->GetText()));
			std::string RegionString = "" + RegionStr;
		g_DiscordMgrAddon->UpdateState(RegionString);
		}
	}
	if (opcode == 0x704C)
	{
		uint8_t ItemSlot = packet->Read<uint8_t>();
		uint16_t ItemType = packet->Read<uint16_t>();
		if (ItemType == 0x29ED || ItemType == 0x29EC)
		{
			packet->ReadStringA();
			if (!g_GlobalDataMgr->m_CurrentLinkedItemName.empty() && g_GlobalDataMgr->m_LinkedGlobalItemEnd != 0)
			{
				CMsgStreamBuffer* ItemUsePacket = new CMsgStreamBuffer(0x705C);
				ItemUsePacket->Write<uint8_t>(g_GlobalDataMgr->m_LinkedGlobalSlot);
				ItemUsePacket->Write<uint16_t>(ItemType);
				ItemUsePacket->Write<uint8_t>(g_GlobalDataMgr->m_LinkedGlobalItemBegin);
				ItemUsePacket->Write<uint8_t>(g_GlobalDataMgr->m_LinkedGlobalItemEnd);
				ItemUsePacket->WriteStringW(g_GlobalDataMgr->m_CurrentLinkedItemName.c_str());
				ItemUsePacket->SendToServer();
				g_GlobalDataMgr->m_CurrentLinkedItemName = std::wstring();
				g_GlobalDataMgr->m_LinkedGlobalItemBegin = 0;
				g_GlobalDataMgr->m_LinkedGlobalItemEnd = 0;
				return E_MSGHOOK_RESULT::PASS_THROUGH;
			}
		}

	}
	if (opcode == 0x3012)
	{
		if (pTop5FTWKillCounterWindow)
		{
			pTop5FTWKillCounterWindow->Close();
			pTop5FTWKillCounterWindow = nullptr;
		}
		if (pDpsMeterWindow)
		{
			pDpsMeterWindow->Close();
			pDpsMeterWindow = nullptr;
		}
		if (pTop5KillCounterWindow)
		{
			pTop5KillCounterWindow->Close();
			pTop5KillCounterWindow = nullptr;
		}

		if (mainMenuWindow)
		{
			mainMenuWindow->Close();
			mainMenuWindow = nullptr;
		}

		if (titleManagerWindow)
		{
			titleManagerWindow->Close();
			titleManagerWindow = nullptr;
		}

		if (uniqueStatusWindow)
		{
			uniqueStatusWindow->Close();
			uniqueStatusWindow = nullptr;
		}

		if (grantNameWindow)
		{
			grantNameWindow->Close();
			grantNameWindow = nullptr;
		}

		if (customTitleWindow)
		{
			customTitleWindow->Close();
			customTitleWindow = nullptr;
		}

		if (eventTimesWindow)
		{
			eventTimesWindow->Close();
			eventTimesWindow = nullptr;
		}

		if (dynamicShopWindow)
		{
			dynamicShopWindow->Close();
			dynamicShopWindow = nullptr;
		}


		g_PlayerSpawned = true;
		if(g_CICPlayer)
			g_GlobalDataMgr->ObjID = g_CICPlayer->GetObjID();
		/*auto pCIFMiniMap = (CIFMiniMap*)g_CGInterface->field_36C.GetGUIObjectByID(10, 1);
		if (pCIFMiniMap)
		{
			
			if (g_CICPlayer && g_CICPlayer->GetJobStatus() == 4)
			{
				auto NameStr = g_StringHelper->ws2s(g_CICPlayer->GetCharName()->c_str());
				g_DiscordMgrAddon->UpdateDetails("" + NameStr + " | Lv: " + std::to_string(g_CICPlayer->level) + "");
			}
			else
			{
				auto NameStr = g_StringHelper->ws2s(g_CICPlayer->GetCharName()->c_str());
				g_DiscordMgrAddon->UpdateDetails("Jobbing");
			}
			
			auto RegionStr = g_StringHelper->ws2s(std::wstring(pCIFMiniMap->MiniMapTitleLabel->GetText()));
			std::string RegionString = "" + RegionStr;
			g_DiscordMgrAddon->UpdateState(RegionString);
		}*/

		g_DiscordMgrAddon->UpdateState("In Game");

			

	}
	return (handled) ? E_MSGHOOK_RESULT::BLOCK : E_MSGHOOK_RESULT::PASS_THROUGH;
}
E_MSGHOOK_RESULT HandleCharDataBegin(CMsgStreamBuffer* packet)
{
	g_Character->GotData = false;
	g_PlayerSpawned = false;
	return E_MSGHOOK_RESULT::PASS_THROUGH;
}
E_MSGHOOK_RESULT HandleCharDataEnd(CMsgStreamBuffer* packet)
{
	if (g_Character->GotData)
	{
		HWIDManager* mgr = new HWIDManager();
		mgr->Initialize();
		mgr->Free();
		std::free(mgr);
		g_Character->GotData = false;
	}
	return E_MSGHOOK_RESULT::PASS_THROUGH;
}
E_MSGHOOK_RESULT HandleCharData(CMsgStreamBuffer* packet)
{
	if (!g_Character->GotData)
	{
		g_Character->Info->ServerTime = packet->Read<uint32_t>();
		g_Character->Info->RefObjID = packet->Read<uint32_t>();
		g_Character->Info->Scale = packet->Read<uint8_t>();
		g_Character->Info->CurLevel = packet->Read<uint8_t>();
		g_Character->Info->MaxLevel = packet->Read<uint8_t>();
		g_Character->Info->ExpOffset = packet->Read<uint64_t>();
		g_Character->Info->SExpOffset = packet->Read<uint32_t>();
		g_Character->Info->Gold = packet->Read<uint64_t>();
		g_Character->Info->SkillPoint = packet->Read<uint32_t>();
		packet->Read<uint16_t>();
		packet->Read<uint8_t>();
		packet->Read<uint32_t>();
		packet->Read<uint32_t>();
		packet->Read<uint32_t>();
		packet->Read<uint8_t>();
		packet->Read<uint8_t>();
		packet->Read<uint16_t>();
		packet->Read<uint32_t>();
		packet->Read<uint8_t>();
		packet->Read<uint8_t>(); // VHWANLEVEL
		g_Character->Info->InventorySize = packet->Read<uint8_t>();
		g_Character->GotData = true;

		if (accountLockedWindow)
		{
			accountLockedWindow->Close();
			accountLockedWindow = nullptr;
		}

	}
	return E_MSGHOOK_RESULT::PASS_THROUGH;
}

E_MSGHOOK_RESULT HandleCharSelection(CMsgStreamBuffer* packet)
{
	g_DiscordMgrAddon->UpdateState("Selecting Character");
	//g_DiscordMgrAddon->UpdateDetails("discord.gg/RUhWERK");

	g_Character->GotData = false;
	g_GlobalDataMgr->m_CurrentTitlesList.clear();
	g_GlobalDataMgr->m_NameColors.clear();
	g_GlobalDataMgr->GlobalChatLog.clear();

	
	return E_MSGHOOK_RESULT::PASS_THROUGH;
}
E_MSGHOOK_RESULT HandleEffectUpdate(CMsgStreamBuffer* packet)
{
	uint8_t type = packet->Read<uint8_t>();

	if (type == 0) // afk bubbles
	{
		auto effectType = packet->Read<uint8_t>();
		auto TargetUniqueId = packet->Read<uint32_t>();
		auto TargetPlayer = g_CICPlayer->GetCICPlayerByUniqueID(TargetUniqueId);

		if (TargetPlayer && effectType == 1) // if player isn't null and effect will be activated
		{
			auto effect = g_GlobalDataMgr->GetEffectIdByName(L"PARAM_SLEEP");
			TargetPlayer->MakeEffect(effect);
		}
		else if (TargetPlayer && effectType == 0)
		{
			auto effect = g_GlobalDataMgr->GetEffectIdByName(L"PARAM_SLEEP");
			if (TargetPlayer->GetObjEffect() == effect)
				TargetPlayer->RemoveEffect(effect);
		}
	}
	return E_MSGHOOK_RESULT::BLOCK;
}
E_MSGHOOK_RESULT HandleCustoms(CMsgStreamBuffer* packet)
{
	uint8_t OperationType = packet->Read<uint8_t>();
	if (OperationType == GameChatType::Custom) // custom msg
	{
		g_ChatManager->Handle(packet);
	}
	else if (OperationType == MsgOpcodeTypes::AntiPHBOT)
	{
		g_PHBotMgr->Handle(packet);
	}
	else if (OperationType == MsgOpcodeTypes::Chest_Response)
	{
		if (chestWindow)
		{
			uint8_t type = packet->Read<uint8_t>();
			if (type == 0x01)
			{
				chestWindow->OnRecvData(packet);
			}
			else if (type == 0x02)
			{
				uint32_t Index = packet->Read<uint32_t>();
				chestWindow->OnRemoveData(Index);
			}
		}
	}
	else if (OperationType == MsgOpcodeTypes::TitlesList)
	{
		uint16_t titleSize = packet->Read<uint16_t>();
		if (titleSize > 0)
		{
			g_GlobalDataMgr->m_CurrentTitlesList.clear();
			for (size_t i = 0; i < titleSize; i++)
			{
				auto hwanlevel = packet->Read<uint8_t>();
				if (hwanlevel == 255)
				{
					auto haveCustomTitle = g_GlobalDataMgr->m_CustomTitles.find(g_CICPlayer->GetCharName()->c_str());
					if (haveCustomTitle != g_GlobalDataMgr->m_CustomTitles.end())
						g_GlobalDataMgr->m_CurrentTitlesList.insert({ hwanlevel, haveCustomTitle->second });
				}
				else
					g_GlobalDataMgr->m_CurrentTitlesList.insert({ hwanlevel, g_GlobalDataMgr->GetHwanString(hwanlevel) });
			}
		}
	}
	else if (OperationType == MsgOpcodeTypes::OnCharacterInfo)
	{
		g_CharacterSpawn->OnUpdate(packet);
	}
	else if (OperationType == 0x42)
	{
		if (pDpsMeterWindow)
			pDpsMeterWindow->Close();

		pDpsMeterWindow = new DPSMeterWindow();
		pDpsMeterWindow->Show(std::shared_ptr<Form>(pDpsMeterWindow));
		pDpsMeterWindow->Start(packet);
	}
	else if (OperationType == 0x63) {
		auto type = packet->Read<uint8_t>();
		if (type == 1) {
			if (!accountLockedWindow)
			{
				accountLockedWindow = new AccountLockedWindow();
				accountLockedWindow->Show(std::shared_ptr<Form>(accountLockedWindow));
			}

		}
		else if (type == 2) {
			accountLockedWindow->Close();
			accountLockedWindow = nullptr;
			g_CGInterface->ShowMessage_PINK(L"You character has been unlocked");
		}

	}

	else if (OperationType == 0x25) // Unique Status Response
	{
		auto size = packet->Read<uint8_t>();
		for (size_t i = 0; i < size; i++)
		{
			auto RefObjID = packet->Read<uint32_t>();
			auto bState = packet->Read<uint8_t>();
			auto KillerName = packet->ReadStringA();
			auto Time = packet->ReadStringA();
			if (RefObjID > 0)
			{
				auto pObjectData = g_GlobalDataMgr->GetGenericObjectDataByID(RefObjID);
				auto szUniqueName = g_GlobalDataMgr->GetObjectName(pObjectData);
				bool isFound = false;
				for (auto& data : g_GlobalDataMgr->m_UniqueData)
				{
					if (data.RefObjID == RefObjID)
					{
						data.bState = bState;
						data.szKillerName = KillerName;
						data.UniqueName = szUniqueName;
						data.time = Time;
						isFound = true;
					}
				}
				if (!isFound)
				{
					UniqueNotifyData data;
					data.bState = bState;
					data.RefObjID = RefObjID;
					data.szKillerName = KillerName;
					data.time = Time;
					data.UniqueName = szUniqueName;
					g_GlobalDataMgr->m_UniqueData.push_back(data);
				}
			}
		}
		if (uniqueStatusWindow)
			uniqueStatusWindow->RefreshData(0);
	}
	else if (OperationType == 0x77)
	{
		if (g_CGInterface && g_CICPlayer)
		{
			if (!pTop5KillCounterWindow)
			{
				pTop5KillCounterWindow = new Top5KillCounterWindow();
				pTop5KillCounterWindow->Show(std::shared_ptr<Form>(pTop5KillCounterWindow));
			}
			pTop5KillCounterWindow->Start(packet);
		}
		return E_MSGHOOK_RESULT::BLOCK;
	}
	else if (OperationType == 0x78)
	{
		if (g_CGInterface && g_CICPlayer)
		{
			if (!pTop5FTWKillCounterWindow)
			{
				pTop5FTWKillCounterWindow = new Top5FTWKillCounterWindow();
				pTop5FTWKillCounterWindow->Show(std::shared_ptr<Form>(pTop5FTWKillCounterWindow));
			}
			pTop5FTWKillCounterWindow->Start(packet);
		}
		return E_MSGHOOK_RESULT::BLOCK;
	}
	else if (OperationType == 0x79)//Character icons data
	{
		auto size = packet->Read<uint32_t>();
		g_GlobalDataMgr->m_IconsData.clear();
		for (size_t i = 0; i < size; i++)
		{
			auto IconID = packet->Read<uint32_t>();
			auto IconPath = packet->ReadStringA();
			auto foundData = g_GlobalDataMgr->m_IconsData.find(IconID);
			if (foundData == g_GlobalDataMgr->m_IconsData.end())
			{
				auto Resource = g_ResourceMgr->LoadTextureFromPk2(n_string(IconPath));
				if (Resource != nullptr)
				{
					g_GlobalDataMgr->m_IconsData.insert({ IconID, Resource });
				}
			}
		}
	}
	else if (OperationType == 0x85)
	{
		auto size = packet->Read<uint8_t>();
		g_GlobalDataMgr->m_PartyDisabledRegions.clear();
		for (size_t i = 0; i < size; i++)
		{
			auto RegionID = packet->Read<int16_t>();
			if (g_GlobalDataMgr->m_PartyDisabledRegions.find(RegionID) == g_GlobalDataMgr->m_PartyDisabledRegions.end())
			{
				g_GlobalDataMgr->m_PartyDisabledRegions.insert(RegionID);
			}
		}
	}
	else if (OperationType == 0) // Item mall buy
	{
		auto PickPacket = new CMsgStreamBuffer(0xB034);
		auto Remaining = packet->GetLength() - 1;
		for (size_t i = 0; i < Remaining; i++)
		{
			PickPacket->Write<uint8_t>(packet->Read<uint8_t>());
		}

		//firstly get rid of the annoying message (we should hide it xd)
		g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C1F0), 2);
		*(BYTE*)(0x0087C1F0) = 0xEB;
		*(BYTE*)(0x0087C1F0 + 1) = 0x37;
		g_MemoryHelper->ReProtect();
		g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C15B), 1);
		*(BYTE*)(0x0087C15B) = 0x75;
		g_MemoryHelper->ReProtect();
		//first of all make a copy of original item
		PickPacket->SendToClient();
		//after giving the item, rollback the item gained msg so player will keep seeing it
		g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C1F0), 2);
		*(BYTE*)(0x0087C1F0) = 0x72;
		*(BYTE*)(0x0087C1F0 + 1) = 0x05;
		g_MemoryHelper->ReProtect();
		g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C15B), 1);
		*(BYTE*)(0x0087C15B) = 0x74;
		g_MemoryHelper->ReProtect();
	}
	else if (OperationType == 0x86)
	{
		g_GlobalDataMgr->m_EventsData.clear();
		EventData data;
		int8_t listSize = packet->Read<int8_t>();
		for (size_t i = 0; i < listSize; i++)
		{
			auto ID = packet->Read<int>();
			auto Name = packet->ReadStringA();
			auto Area = packet->ReadStringA();
			auto Description = packet->ReadStringA();
			auto Silks = packet->Read<int>();
			data.ID = ID;
			data.Name = Name;
			data.AreaName = Area;
			data.Description = Description;
			data.Rewards = Silks;
			g_GlobalDataMgr->m_EventsData.push_back(data);
		}
	}
	else if (OperationType == MsgOpcodeTypes::EventTimesResponse)
	{

		g_GlobalDataMgr->m_EventTimes.clear();

		int8_t eventSize = packet->Read<int8_t>();
		for (size_t i = 0; i < eventSize; i++) {

			EventTimes eTime;
			eTime.Name = packet->ReadStringA();
			eTime.Time = packet->ReadStringA();

			g_GlobalDataMgr->m_EventTimes.insert({ i,eTime });

		}

		if (eventTimesWindow)
			eventTimesWindow->RefreshData(0);
	}
	else if (OperationType == MsgOpcodeTypes::DShopResponse)
	{
		uint8_t type = packet->Read<uint8_t>();

		if (type == 1) {
			uint8_t Size = packet->Read<uint8_t>();

			if (Size > 0) {
				g_GlobalDataMgr->m_DSTitles.clear();

				for (size_t i = 0; i < Size; i++)
				{
					DSTitles eTitles;

					//eTitles.Id = packet->Read<uint32_t>();
					eTitles.TitleId = packet->Read<uint32_t>();
					eTitles.Price = packet->Read<uint32_t>();

					g_GlobalDataMgr->m_DSTitles.push_back(eTitles);
				}
			}

			g_GlobalDataMgr->DShopNameColorPrice = packet->Read<uint32_t>();
			g_GlobalDataMgr->DShopTitleColorPrice = packet->Read<uint32_t>();
			g_GlobalDataMgr->DShopCustomTitlePrice = packet->Read<uint32_t>();

		}
	}
	else if (OperationType == 0x99)
	{
		g_GlobalDataMgr->m_Settings.TitleManager = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.UniqueStatus = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.EventTimes = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.GrantName = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.CustomTitle = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.DynamicShop = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.Facebook = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.Discord = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.Website = packet->Read<bool>();
		g_GlobalDataMgr->m_Settings.FacebookLink = packet->ReadStringA();
		g_GlobalDataMgr->m_Settings.DiscordLink = packet->ReadStringA();
		g_GlobalDataMgr->m_Settings.WebsiteLink = packet->ReadStringA();

	}

	return E_MSGHOOK_RESULT::BLOCK;
}