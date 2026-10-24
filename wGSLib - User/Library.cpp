#include "pch.h"
#include "Library.h"
#include "ObjMgr.h"
#include "DbMgr.h"
#include "ConfigMgr.h"
#include "StaticPatches.h"
#include "DbTriggerActions.h"
#include "DamageMeter.h"
#include "Game.h"
#include "MainProcess.h"
#include "MsgStreamBuffer.h"
#include "RefDataManager.h"
#include "RegionRestrictionMgr.h"

//filter commands
void* __fastcall MyFilterMsgv1Handler(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("ReadPos %d WritePos %d\n", wReadPos, wWritePos);

	UINT CharID = pMsg->Read<UINT>();
	BYTE Type = pMsg->Read<BYTE>();


	CGObjPC* pPC = reinterpret_cast<CGObjPC*>(
		CGame::GetObjByGameID(CharID)
		);

	if (pPC != NULL)
	{
		if (pPC->CanSendMessage())
		{
			//	printf("[custom msg] entered ! MsgID = 0x%04X, CharID = %d, Type = %d\n", pMsg->GetID(), pPC->GetDBID(), Type);

			switch (Type)
			{
				//Grant name changing
			case 1:
			{
				std::n_string NewGrantName = std::n_string(pMsg->ReadStringA());
				pPC->SetGrantName(&NewGrantName);
			}
			break;
			//LIVE TITLE UPDATE
			case 2:
			{
				BYTE TitleID = pMsg->Read<BYTE>();
				pPC->UpdateHwan(TitleID);
			}
			break;
			//LIVE PVP CAPE
			case 3:
			{
				BYTE Cape = pMsg->Read<BYTE>();
				pPC->SetPvpState(Cape);
			}
			break;
			//LIVE TP AT SAME POS
			case 4:
			{
				pPC->TeleportToOwnPos();
			}
			break;
			//LIVE silk
			case 5:
			{
				int Silk = pMsg->Read<int>();
				int Git = pMsg->Read<int>();
				int Point = pMsg->Read<int>();
				bool SendPacket = pMsg->Read<bool>();
				pPC->UpdateSilk(Silk, Git, Point, SendPacket);
			}
			break;
			//LIVE gold
			case 6:
			{
				int Amount = pMsg->Read<int>();
				bool ShowMsg = pMsg->Read<bool>();
				pPC->AddGold(Amount, ShowMsg);
			}
			break;
			//LIVE deal dmg
			case 7:
			{
				int ResonMask = pMsg->Read<int>();
				int dmg = pMsg->Read<int>();

				pPC->DealDamage(ResonMask, dmg);
			}
			break;
			//LIVE teleport
			case 8:
			{
				int WorldLayerID = pMsg->Read<int>();
				int WorldID = pMsg->Read<int>();
				WORD wRegionID = pMsg->Read<WORD>();
				float X, Y, Z;
				X = pMsg->Read<float>();
				Y = pMsg->Read<float>();
				Z = pMsg->Read<float>();
				SWorldID stWorldID(WorldLayerID, WorldID);
				SPosInfo posInfo(wRegionID, X, Y, Z);
				pPC->TeleportTo(stWorldID, posInfo);
			}
			break;
			//LIVE Item
			case 9:
			{
				int Storgae = pMsg->Read<int>();
				std::string ItemCodeName = pMsg->ReadStringA();
				int Count = pMsg->Read<int>();
				BYTE Plus = pMsg->Read<BYTE>();
				char* chr = const_cast<char*>(ItemCodeName.c_str());
				pPC->AddItem(Storgae, chr, Count, Plus);
			}
			break;
			//LIVE Zerk Points
			case 10:
			{
				int Count = pMsg->Read<int>();
				pPC->UpdateZerkLevel(Count);
			}
			break;
			//LIVE sp Points
			case 11:
			{
				int Count = pMsg->Read<int>();
				pPC->UpdateSP(Count);
			}
			break;
			//LIVE Skill Assgin
			case 12:
			{
				int SkillId = pMsg->Read<int>();
				int Time = pMsg->Read<int>();
				CObjMgr::EngageBuffSkill1(pPC, SkillId, Time);
			}
			break;
			}
		}
	}

	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}

//filter commands
void* __fastcall MyFilterMsgv2Handler(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("ReadPos %d WritePos %d\n", wReadPos, wWritePos);

	UINT CharID = pMsg->Read<UINT>();

	CGObjPC* pPC = reinterpret_cast<CGObjPC*>(
		CGame::GetObjByGameID(CharID)
		);

	if (pPC != NULL)
	{
		if (pPC->CanSendMessage())
		{
			//printf("[custom msg] entered ! MsgID = 0x%04X, CharID = %d\n", pMsg->GetID(), pPC->GetDBID());

			std::n_string NewGrantName = std::n_string(pMsg->ReadStringA());
			pPC->SetGrantName(&NewGrantName);
		}
	}

	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}


//COSTOMTITLE
void* __fastcall MyFilterMsgCustomTitleHandler(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("[custom msg] entered MsgID = 0x%04X\n", pMsg->GetID());

	std::string Name = pMsg->ReadStringA();
	std::string Title = pMsg->ReadStringA();


	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}

//lock
void* __fastcall MyFilterMsgLockHandler(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("[custom msg] entered MsgID = 0x%04X\n", pMsg->GetID());

	BYTE LockTYPE = pMsg->Read<BYTE>();
	std::string lockPass = pMsg->ReadStringA();


	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}

//TITLE INFO
void* __fastcall MyFilterMsgSwitchTitleInfoHandler(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("[custom msg] entered MsgID = 0x%04X\n", pMsg->GetID());

	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}

//TITLE USE
void* __fastcall MyFilterMsgSwitchTitleSetHandler(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("[custom msg] entered MsgID = 0x%04X\n", pMsg->GetID());
	BYTE titleid = pMsg->Read<BYTE>();

	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}

//client info
void* __fastcall MyFilterMsgClientInfoHandler(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("[custom msg] entered MsgID = 0x%04X\n", pMsg->GetID());
	BYTE jobtype = pMsg->Read<BYTE>();
	BYTE curlevel = pMsg->Read<BYTE>();
	BYTE curregion = pMsg->Read<BYTE>();

	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}

//Reload Icon
void* __fastcall MyFilterMsgReloadIconHandler(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("[custom msg] entered MsgID = 0x%04X\n", pMsg->GetID());
	UINT CharID = pMsg->Read<UINT>();

	CGObjPC* pPC = reinterpret_cast<CGObjPC*>(
		CGame::GetObjByGameID(CharID)
		);

	if (pPC != NULL)
	{
		if (pPC->CanSendMessage())
		{
			pPC->TeleportToOwnPos();
		}
	}
	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}
//Return Empty Slots
void* __fastcall SetBodyMode(
	CMainProcess* self, void* /* dummy edx */, CMsgStreamBuffer* pMsg, DWORD dwOverlappedJobID, LPVOID lpParam, CMassiveMsg* pMassiveMsg
)
{
	WORD wReadPos = pMsg->GetReadPos();
	WORD wWritePos = pMsg->GetWritePos();

	//printf("[custom msg] entered MsgID = 0x%04X\n", pMsg->GetID());
	UINT CharID = pMsg->Read<UINT>();

	CGObjPC* pPC = reinterpret_cast<CGObjPC*>(
		CGame::GetObjByGameID(CharID)
		);

	if (pPC != NULL && pPC->CanSendMessage())
	{
		BYTE Type = pMsg->Read<BYTE>();
		pPC->SetBodyMode(Type);

	}


	if (pMsg->GetReadPos() != pMsg->GetWritePos())
		pMsg->SetReadPos(wWritePos);

	return NULL;//should be handler result i suppose idk
}
DWORD WINAPI StartupWorker(LPVOID lpParams)
{
	Sleep(1000);

	CConfigMgr::Initialize();

	if (!CConfigMgr::LoadIniSettings())
		return false;

	if (!CDbMgr::Initialize())
		return false;

	if (!CConfigMgr::LoadDbSettings())
		return false;

	if (!CObjMgr::Initialize())
		return false;

	//nothing on it cherno shit :V
	//if (!CDbTriggerActions::Initialize())
	//	return false;
	//Sleep(1000);
	if (!CRegionRestrictionMgr::Initialize())
		return false;

	//if (!CDebugHelper::Initialize())
		//return false;
		
	if (!CStaticPatches::Apply())
		return false;
		
	

	CGame::Initialize();

	CRefDataManager::LoadUniqueInfo();
	//CRefDataManager::LoadFortressInfo();

	CDamageMeter::Initialize();

	CMainProcess::Initialize();

	CMainProcess::RegisterMsgHandler(0x3500, (CMainProcess::FN_MSG_HANDLER)MyFilterMsgv1Handler);
	//CMainProcess::RegisterMsgHandler(0x3501, (CMainProcess::FN_MSG_HANDLER)MyFilterMsgv2Handler);
	//CMainProcess::RegisterMsgHandler(0x1202, (CMainProcess::FN_MSG_HANDLER)MyFilterMsgCustomTitleHandler);
	//CMainProcess::RegisterMsgHandler(0x1204, (CMainProcess::FN_MSG_HANDLER)MyFilterMsgLockHandler);
	//CMainProcess::RegisterMsgHandler(0x1200, (CMainProcess::FN_MSG_HANDLER)MyFilterMsgSwitchTitleInfoHandler);
	CMainProcess::RegisterMsgHandler(0x1201, (CMainProcess::FN_MSG_HANDLER)MyFilterMsgSwitchTitleSetHandler);
	//CMainProcess::RegisterMsgHandler(0x3560, (CMainProcess::FN_MSG_HANDLER)MyFilterMsgClientInfoHandler);
	//CMainProcess::RegisterMsgHandler(0x3502, (CMainProcess::FN_MSG_HANDLER)MyFilterMsgReloadIconHandler);
	//CMainProcess::RegisterMsgHandler(0x3503, (CMainProcess::FN_MSG_HANDLER)SetBodyMode);

	/*if (!CDbMgr::GetMiscDbSet()->CallGameServerStartedSP())
		return false;*/

	std::cout << __FUNCTION__ << " - wGSLib initialized" << std::endl;

	if (!CDbTriggerActions::StartDelivering())
		return false;

	return true;
}

bool CLibrary::Initialize()
{
	std::cout << "============================" << std::endl;
	std::cout << "wGSLib - v1.0.0 | Vsro v188" << std::endl;
	//std::cout << "========wFilter========" << std::endl;
	std::cout << "============================" << std::endl;

	//printf("Compile time: %s | %s\n", __DATE__, __TIME__);

	//std::cout << "======================================" << std::endl;
	CreateThread(NULL, 0, StartupWorker, NULL, 0, NULL);

	return true;
}


