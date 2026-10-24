#include "pch.h"
#include "CGStorage.h"

const DWORD cdwGetItemAddr = 0x004B8000;
const DWORD cdwMoveItemAddr = 0x004B7F80;
const DWORD cdwCanPushItemAddr = 0x004B92B0;
const DWORD cdwCheckAvatarsetIntegrityAddr = 0x004B8EE0;
const DWORD cdwCheckEquipsetIntegrityAddr = 0x004B8AD0;
const DWORD cdwCountSlotAddr = 0x004B87F0;
const DWORD cdwFindFirstEmptySlotAddr = 0x004B8260;
const DWORD cdwFindTotalEmptySlotAddr = 0x004B82E0;
const DWORD cdwMakeAllItemOfflinedAddr = 0x004B8A60;
const DWORD cdwPopItemAddr1 = 0x004B7F10;
const DWORD cdwPopItemAddr2 = 0x004B91D0;
const DWORD cdwSetItemAddr1 = 0x004B7E90;
const DWORD cdwCountEmptySlotAddr = 0x004B8770;
const DWORD cdwSwapItemAddr = 0x004B80F0;

//int __userpurge
//DEC_GStorage_GetItem_sub_4B8000@<eax>
//(srCGStorage *CGStorage@<esi>, int slot)
//returns: CGItemEquip*, CGItemExpendable*
CGItem* CGStorage::GetItem(BYTE slot)
{
	CGItem* pResult = NULL;

	__asm pushad;
	__asm push slot;
	__asm mov esi, this;
	__asm call cdwGetItemAddr;
	__asm mov pResult, eax;
	__asm popad;

	return pResult;
}

//int __userpurge 
//DEC_CGStorage_MoveItem_sub_4B7F80@<eax>
//(int sourceSlot_checkme@<ecx>, srCGStorage *CGStorage@<esi>, int fromSlot, int toSlot)
bool CGStorage::MoveItem(BYTE sourceSlot, BYTE destSlot)
{
	bool result = false;

	__asm pushad;

	//Just ensure everything is cleaned up
	__asm xor ecx, ecx;
	__asm xor esi, esi;


	__asm push destSlot;
	__asm push sourceSlot;
	__asm mov esi, this;
	__asm mov cl, sourceSlot;

	__asm call cdwMoveItemAddr;

	__asm mov result, al;

	__asm popad;

	return result;
}


//int __userpurge 
//DEC_CGStorage_CanPushItem_sub_4B92B0@<eax>
//(srCGStorage *CGStorage@<esi>, int slotPossibly)
bool CGStorage::CanPushItem(BYTE slot)
{
	bool result = false;

	__asm pushad;

	__asm push slot;
	__asm mov esi, this;
	__asm call cdwCanPushItemAddr;

	__asm mov result, al;

	__asm popad;

	return result;
}


//int __usercall
//DEC_CGStorage_CheckAvatarsetIntegrity_sub_4B8EE0@<eax>
//(int slot@<ecx>, srCGStorage *CGStorage@<esi>)
bool CGStorage::CheckAvatarsetIntegrity(BYTE slot)
{
	bool result = false;

	__asm pushad;

	__asm xor ecx, ecx;
	__asm mov esi, this;
	__asm mov cl, slot;
	__asm call cdwCheckAvatarsetIntegrityAddr;

	__asm mov result, al;

	__asm popad;

	return result;
}


//unk1 = 00CD3A80 - some trash... untested but called on teleport / login etc
//void __thiscall
//DEC_CGStorage_CheckEquipsetIntegrity_sub_4B8AD0
//(srCGStorage *CGStorage, int unk_00CD3A80h, int unkUsually_1d)
bool CGStorage::CheckEquipsetIntegrity(int unk1_00CD3A80h, int unk2_usually_1)
{
	bool result = false;

	__asm pushad;

	__asm push unk2_usually_1;
	__asm push unk1_00CD3A80h;
	__asm mov ecx, this;
	__asm call cdwCheckEquipsetIntegrityAddr;

	__asm popad;

	return result;
}


//countUsed = find count of slots USED, otherwise empty slot count
//int __userpurge
//DEC_CGStorage_CountItem_sub_4B8770@<eax>
//(srCGStorage *CGStorage@<esi>, int startSlot_1, int endSlot, int countUsed)
int CGStorage::CountSlot(BYTE startSlot, BYTE endSlot, bool countUsed)
{
	int result = 0;

	__asm pushad;

	__asm push countUsed;
	__asm push endSlot;
	__asm push startSlot;
	__asm mov esi, this;
	__asm call cdwCountEmptySlotAddr;

	__asm mov result, eax;

	__asm popad;

	return result;
}

//-1 on error
//char __userpurge
//DEC_CGStorage_FindFirstEmptySlot_sub_4B8260@<al>
//(srCGStorage *storage@<esi>, int startSlot)
BYTE CGStorage::FindFirstEmptySlot(BYTE startSlot)
{
	BYTE result = -1;

	__asm pushad;


	__asm push startSlot;
	__asm mov esi, this;
	__asm call cdwFindFirstEmptySlotAddr;

	__asm mov result, al;

	__asm popad;

	return result;
}


//char __userpurge
//DEC_CGStorage_FindTotalEmptySlot_sub_4B82E0@<al>
//(srCGStorage *obj@<esi>, int startSlot)
BYTE CGStorage::FindTotalEmptySlot(BYTE startSlot)
{
	BYTE result = -1;

	__asm pushad;

	__asm push startSlot;
	__asm mov esi, this;
	__asm call cdwFindTotalEmptySlotAddr;

	__asm mov result, al;

	__asm popad;

	return result;
}


//void __usercall
//DEC_CGStorage_MakeAllItemOfflined_sub_4B8A60
//(srCGStorage *CGStorage@<esi>)
void CGStorage::MakeAllItemOfflined()
{
	__asm pushad;
	__asm mov esi, this;
	__asm call cdwMakeAllItemOfflinedAddr;
	__asm popad;
}

//int __userpurge
//DEC_CGStorage_PopItem_sub_4B7F10@<eax>
//(srCGStorage *unkObj@<esi>, int slot)
CGItem* CGStorage::PopItem1(BYTE slot)
{
	CGItem* pResult = NULL;

	__asm pushad;

	__asm push slot;
	__asm mov esi, this;
	__asm call cdwPopItemAddr1;

	__asm mov pResult, eax;

	__asm popad;

	return pResult;
}

//int __userpurge
//DEC_CGStorage_PopItem_sub_4B91D0@<eax>
//(srCGStorage *CGStorage@<esi>, int slot)
CGItem* CGStorage::PopItem2(BYTE slot)
{
	CGItem* pResult = NULL;

	__asm pushad;

	__asm push slot;
	__asm mov esi, this;
	__asm call cdwPopItemAddr2;

	__asm mov pResult, eax;

	__asm popad;

	return pResult;
}

//CHECKME... CGObjPC is put @ ecx if item bought from npc
//int __userpurge
//DEC_CGStorage_SetItem_sub_4B7E90@<eax>
//(BYTE targetSlot@<ecx>, srCGStorage *CGStorage@<esi>, int CGItemEquip, int slot)
bool CGStorage::SetItem1(CGItem* item, BYTE slot, bool useCGObjPC)
{
	bool result = false;
	void* pcObj = this->pCGObjPC;

	__asm pushad;

	__asm push slot;
	__asm push item;
	__asm mov esi, this;

	__asm cmp useCGObjPC, TRUE;

	__asm je USE_PC_OBJ;
	__asm jmp USE_TARGET_SLOT_ID;

USE_PC_OBJ:
	__asm mov ecx, pcObj;

USE_TARGET_SLOT_ID:
	__asm xor ecx, ecx;
	__asm mov cl, slot;

	__asm call cdwSetItemAddr1;

	__asm mov result, al;

	__asm popad;

	return result;
}

//int __userpurge
//DEC_CGStorage_SwapItem_sub_4B80F0@<eax>
//(int fromSlotOrCGObjPC@<ecx>, srCGStorage *CGStorage@<esi>, int slot1, int slot2)
bool CGStorage::SwapItem(BYTE slot1, BYTE slot2)
{
	bool result = false;

	__asm pushad;

	__asm push slot2;
	__asm push slot1;
	__asm mov esi, this;
	__asm xor ecx, ecx;
	__asm mov cl, slot1;

	__asm call cdwSwapItemAddr;

	__asm mov result, al;

	__asm popad;

	return result;
}