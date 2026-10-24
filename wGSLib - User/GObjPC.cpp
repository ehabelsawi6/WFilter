#include "pch.h"
#include "GObjPC.h"
#include "MemoryUtility.h"

#define ADD_ITEM_EXT_FN_OFFSET					0x004EE370
#define UPDATE_VITAL_STATE_FN_OFFSET			0x0052AA30
#define OFFSET_GOLD_FN_OFFSET					0x004E4B60
#define TELEPORT_TO_FN_OFFSET					0x004DF590
#define OFFSET_SKILL_POINT_FN_OFFSET			0x004E4C60		
#define OFFSET_EXP_POINT_FN_OFFSET				0x004E5250
#define OFFSET_ENTER_PVP_FN_OFFSET				0x004F0E90
#define UPDATE_ZERK_POINTS_FN_OFFSET			0x004E4D00
#define ALLOC_MSG_FOR_PEER_FN_OFFSET			0x004E0830
#define SEND_MSG_TO_PEER_FN_OFFSET				0x004E0860

CGObjPC::FN_ADD_ITEM_EXT CGObjPC::s_pfnAddItem_EXT;
CGObjPC::FN_UPDATE_VITAL_STATE CGObjPC::s_pfnUpdateVitalState;
CGObjPC::FN_OFFSET_GOLD CGObjPC::s_pfnOffsetGold;
CGObjPC::FN_TELEPORT_TO CGObjPC::s_pfnTeleportTo;
CGObjPC::FN_OFFSET_SKILL_POINT CGObjPC::s_pfnOffsetSkillPoint;
CGObjPC::FN_OFFSET_EXP_POINT CGObjPC::s_pfnOffsetExpPoint;
CGObjPC::FN_ENTER_PVP CGObjPC::s_pfnEnterPvp;
CGObjPC::FN_ALLOC_MSG_FOR_PEER CGObjPC::s_pfnAllocMsgForPeer;
CGObjPC::FN_SEND_MSG_TO_PEER CGObjPC::s_pfnSendMsgToPeer;

void CGObjPC::SetupFunctionPointers()
{
	s_pfnAddItem_EXT = reinterpret_cast<FN_ADD_ITEM_EXT>(ADD_ITEM_EXT_FN_OFFSET);
	s_pfnUpdateVitalState = reinterpret_cast<FN_UPDATE_VITAL_STATE>(UPDATE_VITAL_STATE_FN_OFFSET);
	s_pfnOffsetGold = reinterpret_cast<FN_OFFSET_GOLD>(OFFSET_GOLD_FN_OFFSET);
	s_pfnTeleportTo = reinterpret_cast<FN_TELEPORT_TO>(TELEPORT_TO_FN_OFFSET);
	s_pfnOffsetSkillPoint = reinterpret_cast<FN_OFFSET_SKILL_POINT>(OFFSET_SKILL_POINT_FN_OFFSET);
	s_pfnOffsetExpPoint = reinterpret_cast<FN_OFFSET_EXP_POINT>(OFFSET_EXP_POINT_FN_OFFSET);
	s_pfnEnterPvp = reinterpret_cast<FN_ENTER_PVP>(OFFSET_ENTER_PVP_FN_OFFSET);
	s_pfnAllocMsgForPeer = reinterpret_cast<FN_ALLOC_MSG_FOR_PEER>(ALLOC_MSG_FOR_PEER_FN_OFFSET);
	s_pfnSendMsgToPeer = reinterpret_cast<FN_SEND_MSG_TO_PEER>(SEND_MSG_TO_PEER_FN_OFFSET);
}

CInstancePC* CGObjPC::GetInstance() const
{
	return MEMUTIL_READ_BY_PTR_OFFSET(this, 0x34, CInstancePC*);
}
CGStorage CGObjPC::GetStorage() const
{
	return MEMUTIL_READ_BY_PTR_OFFSET(this, 0x1C10, CGStorage);
}

RefObjPC* CGObjPC::GetRefObj() const
{
	CInstancePC* pInst = this->GetInstance();
	return MEMUTIL_READ_BY_PTR_OFFSET(pInst, 0x18, RefObjPC*);
}

BOOL CGObjPC::CanSendMessage()
{
	if (this->GetInstance() == NULL)
		return FALSE;

	//Get msg block state.

	SObjectStateFlags* state = MEMUTIL_READ_BY_PTR_OFFSET(this, 0x30, SObjectStateFlags*);

	//TEST
	if (state->btMsgBlockState != 1 && this->GetLifeState() == LIFESTATE_ALIVE)
		return TRUE;

	return FALSE;
}

//Actually RefObjChar aligned (0x18[pos of CRefObjPC + 0x6C))
WORD CGObjPC::GetCurFreeStatPoints()
{
	CInstancePC* pInst = this->GetInstance();
	return MEMUTIL_READ_BY_PTR_OFFSET(pInst, 0x84, WORD);
}
//Actually RefObjChar aligned (0x18[pos of CRefObjPC + 0x6C))
void CGObjPC::SetCurFreeStatPoints(WORD wAmount)
{
	/*
	CInstancePC* pInst = this->GetInstance();
	MEMUTIL_WRITE_BY_PTR_OFFSET(pInst, 0x84, WORD, wAmount);
	*/

	const DWORD dwCallAddr = 0x004F92F0;
	DWORD dwTmpAmount = wAmount;
	CInstancePC* pInst = this->GetInstance();

	__asm pushad;

	__asm mov eax, pInst;
	__asm mov ecx, dwTmpAmount;
	__asm call dwCallAddr;

	__asm popad;
}

void CGObjPC::AddStrInt(WORD wStr, WORD wInt)
{
	const DWORD dwCallAddr = 0x00511470;

	DWORD dwTmpStr = wStr;
	DWORD dwTmpInt = wInt;

	this->SetCurFreeStatPoints(this->GetCurFreeStatPoints() + wStr + wInt);

	__asm pushad;

	//int
	__asm push dwTmpInt;

	//str
	__asm mov eax, dwTmpStr;

	__asm mov ebx, this;
	__asm call dwCallAddr;

	__asm popad;
}

int CGObjPC::GetDBID() const
{
	CInstancePC* pInstance = GetInstance();
	if (pInstance == NULL)
		return -1;

	return MEMUTIL_READ_BY_PTR_OFFSET(pInstance, 0x20, int);
}

/* 1 = Success, any other value = failure aka error code */
DWORD CGObjPC::AddItem(DWORD dwStorageType, LPCSTR lpszCodename, int nCount, BYTE btPlusValue)
{
	DWORD dwResultCode = 0;
	//s_pfnAddItem_EXT(this, dwStorageType, lpszCodename, nCount, dwResultCode, 0, false, 0, btPlusValue, 0, 1, 0, 0);
	s_pfnAddItem_EXT(this, dwStorageType, lpszCodename, nCount, dwResultCode, 0, false, 0, btPlusValue, 0, 1, 0, 0);
	return dwResultCode;
}

void CGObjPC::DealDamage(int nReasonMask, int nAmount)
{
	s_pfnUpdateVitalState(this, NULL, nAmount, 0, nReasonMask, 0);
}

void CGObjPC::AddGold(int nAmount, bool bShowDeliveryMsg)
{
	//Special cases (like 25) - 19, 20, 21... they are related to 100 000 and 200 000 
	s_pfnOffsetGold(this, nAmount, 25, true, bShowDeliveryMsg);
}

//see vft later
void CGObjPC::TeleportTo(SWorldID stWorldID, STeleportPos pos)
{
	s_pfnTeleportTo(this, stWorldID, pos, 2);
}

void CGObjPC::AddSkillPoints(int nAmount)
{
	s_pfnOffsetSkillPoint(this, nAmount, 1);
}

void CGObjPC::LiveSkill(int SilkID)
{
	DWORD32* SilkInfo = reinterpret_cast<DWORD32 * (__stdcall*)()>(0x5AA0B0)();
	SilkInfo[2] = SilkID;
	reinterpret_cast<int(__stdcall*)(DWORD32, DWORD32*)>(0x59B480)((DWORD32)this + 0xA30, SilkInfo);
}

void CGObjPC::AddExpPoints(DWORD64 qwLevelExp, DWORD64 qwSpExp)
{
	DWORD dwUnk = 0;
	s_pfnOffsetExpPoint(this, 0, qwLevelExp, qwSpExp, dwUnk);
}

void CGObjPC::SetPvpState(BYTE btState)
{
	s_pfnEnterPvp(this, btState);
}

void CGObjPC::TeleportToOwnPos()
{
	if (!this->CanSendMessage())
		return;

	SWorldID stWorldID;
	SPosInfo posInfo;

	this->GetWorldID(stWorldID);
	this->GetPosInfo(posInfo);

	this->TeleportTo(stWorldID, STeleportPos(posInfo));
}

//userpurge 0x004A9F40, member of CGObjChar, but defined @ IGObj, but what CGObjPC does is
//only sending packet to player, so need to cal CGObjChar one... userpurge, some mess.
//void CGObjPC::UpdateHwanLevel(BYTE btNewLevel)
//{
//	__asm pushad;
//	__asm pushfd;
//
//	//reordered for ebp...
//	__asm mov ecx, this;
//	__asm push btNewLevel;
//
//	//ebp must be assigned after pushing btNewLevel otherwise it will fail.
//	__asm mov ebp, NULL;
//
//	//this func is a member of CGObjPC/CGObjChar, also defined @ IGObj, but well the one @ CGObjPC seem
//	//to only send packet. TODO: Move this shit to proper place, but well its userpurge func so FUCK..
//	__asm mov eax, 0x004A9F40;
//	__asm call eax;
//
//	__asm popfd;
//	__asm popad;
//}

void CGObjPC::UpdateZerkLevel(int nAmount)
{
	BYTE btUnk1 = 0;
	//Temporal, for resister size to match.
	__asm movzx esi, btUnk1;
	
	//Arg3, btUnk1
	__asm push esi;

	//Arg2, nAmount
	__asm mov esi, nAmount;

	//Arg1, CGObjPC ptr
	__asm mov eax, this;


	__asm mov edx, UPDATE_ZERK_POINTS_FN_OFFSET;
	__asm call edx;
}


void CGObjPC::UpdateSilk(int nSilk, int nSilkGift, int nSilkPoint, bool bSendPacket)
{
	/*const DWORD CALL_ADDR = 0x004F0940;

	__asm movzx eax, bSendPacket;

	__asm push eax;
	__asm mov esi, this;
	__asm mov ecx, nSilkPoint;
	__asm mov edx, nSilkGift;
	__asm mov eax, nSilk;

	__asm call CALL_ADDR;*/
	reinterpret_cast<void(__thiscall*)(CGObjPC*, int, int, int,int)>(0x004F0940)(this, nSilk, nSilkGift, nSilkPoint, bSendPacket);
}

void CGObjPC::DropItem(char* szCodename, int ItemCount, int& plus)
{
	reinterpret_cast<void(__thiscall*)(CGObjPC*, const char*, int, int, int*, int, int, int, int)>(0x004AA680)(this, szCodename, ItemCount, 0, &plus, 0, 1, 0, 0);
}

void CGObjPC::SetGrantName(std::n_string* grantname)
{
	unsigned int CharID = this->GetDBID();

	__asm
	{
		push grantname;
		push 0x25;
		push this;

		mov ecx, CharID;
		xor edx, edx;

		mov eax, 0x005C80A0;
		call eax;
	}

}

CGObjPC* CGObjPC::GetObjPCByCharName(const char* charname)
{
	return reinterpret_cast<CGObjPC * (__cdecl*)(const char*)>(0x00485E20)(charname);
}

void CGObjPC::SetLiveItem(int slot, const char* itemcode)
{
	return CMemoryUtility::call_virtual<void(__thiscall*)(CGObjPC*, int, const char*)>(this, 141)(this, slot, itemcode);
}

void CGObjPC::inquire_same_item(const char* codename)
{
	return CMemoryUtility::call_virtual<void(__thiscall*)(CGObjPC*, int, const char*, int, int, int)>(this, 137)(this, 0, codename, 0, 0, 1);
}

void CGObjPC::UpdateHwan(char hwanLevel)
{
	reinterpret_cast<void(__thiscall*)(CGObjPC*, char)>(0x004A9F40)(this, hwanLevel);
}

void CGObjPC::SetCharState(char a2)
{
	reinterpret_cast<void(__thiscall*)(CGObjPC*, char, int, float)>(0x004A9C80)(this, a2, 255, 0.f);
}

void CGObjPC::UpdateSP(int amount)
{
	reinterpret_cast<void(__thiscall*)(CGObjPC*, int, char)>(0x004E4C60)(this, amount, 1);
}

CMsgStreamBuffer* CGObjPC::AllocMsgForPeer(WORD wMsgID)
{
	return s_pfnAllocMsgForPeer(this, wMsgID);
}

//send opcode to this character/object
void CGObjPC::SendMsgToPeer(CMsgStreamBuffer* pMsg)
{
	s_pfnSendMsgToPeer(this, pMsg);
}