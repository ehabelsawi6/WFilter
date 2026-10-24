#ifndef CGSTORAGE_H
#define CGSTORAGE_H
#include "CGItem.h"
#include "pch.h"

struct PlayerInventorySlot
{
	enum Enum : BYTE
	{
		Hat = 0,
		Suit = 1,
		Shoulder = 2,
		Hand = 3,
		Leg = 4,
		Foot = 5,
		Weapon = 6,
		SecondaryWeapon = 7,
		JobSuitOrPvpCape = 8,
		Earring = 9,
		Necklace = 10,
		LeftRing = 11,
		RightRing = 12,
		FirstStorageSlot = 13,
	};
};

class CGStorage
{
public:
	char pad_0000[20]; //0x0000
	void* pCGObjPC; //0x0014

	//3 = body
	uintptr_t StorageType; //0x0018
	uintptr_t CurSlots; //0x001C
	uintptr_t MaxSlots; //0x0020

	//int __userpurge
	//DEC_GStorage_GetItem_sub_4B8000@<eax>
	//(srCGStorage *CGStorage@<esi>, int slot)
	CGItem* GetItem(BYTE slot);

	//bool __userpurge 
	//DEC_CGStorage_MoveItem_sub_4B7F80@<eax>
	//(int sourceSlot_checkme@<ecx>, srCGStorage *CGStorage@<esi>, int fromSlot, int toSlot)
	bool MoveItem(BYTE sourceSlot, BYTE destSlot);

	//int __userpurge 
	//DEC_CGStorage_CanPushItem_sub_4B92B0@<eax>
	//(srCGStorage *CGStorage@<esi>, int slotPossibly)
	bool CanPushItem(BYTE slot);

	//int __usercall
	//DEC_CGStorage_CheckAvatarsetIntegrity_sub_4B8EE0@<eax>
	//(int slot@<ecx>, srCGStorage *CGStorage@<esi>)
	bool CheckAvatarsetIntegrity(BYTE slot);

	//unk1 = 00CD3A80 - some trash... untested but called on teleport / login etc
	//void __thiscall
	//DEC_CGStorage_CheckEquipsetIntegrity_sub_4B8AD0
	//(srCGStorage *CGStorage, int unk_00CD3A80h, int unkUsually_1d)
	bool CheckEquipsetIntegrity(int unk1, int unk2_usually_1);

	//if u set countUsed to false only empty slots are counted
	//int __userpurge
	//DEC_CGStorage_CountItem_sub_4B8770@<eax>
	//(srCGStorage *CGStorage@<esi>, int startSlot_1, int endSlot, int countUsed)
	int CountSlot(BYTE startSlot, BYTE endSlot, bool countUsed);

	//char __userpurge
	//DEC_CGStorage_FindFirstEmptySlot_sub_4B8260@<al>
	//(srCGStorage *storage@<esi>, int startSlot)
	BYTE FindFirstEmptySlot(BYTE startSlot);

	//char __userpurge
	//DEC_CGStorage_FindTotalEmptySlot_sub_4B82E0@<al>
	//(srCGStorage *obj@<esi>, int startSlot)
	BYTE FindTotalEmptySlot(BYTE startSlot);

	//void __usercall
	//DEC_CGStorage_MakeAllItemOfflined_sub_4B8A60
	//(srCGStorage *CGStorage@<esi>)
	void MakeAllItemOfflined();

	//int __userpurge
	//DEC_CGStorage_PopItem_sub_4B7F10@<eax>
	//(srCGStorage *unkObj@<esi>, int slot)
	CGItem* PopItem1(BYTE slot);

	//int __userpurge
	//DEC_CGStorage_PopItem_sub_4B91D0@<eax>
	//(srCGStorage *CGStorage@<esi>, int slot)
	CGItem* PopItem2(BYTE slot);

	//int __userpurge
	//DEC_CGStorage_SetItem_sub_4B7E90@<eax>
	//(BYTE targetSlot@<ecx>, srCGStorage *CGStorage@<esi>, int CGItemEquip, int slot)
	bool SetItem1(CGItem* item, BYTE slot, bool useCGObjPC);

	//int __userpurge
	//DEC_CGStorage_SwapItem_sub_4B80F0@<eax>
	//(int fromSlotOrCGObjPC@<ecx>, srCGStorage *CGStorage@<esi>, int slot1, int slot2)
	bool SwapItem(BYTE slot1, BYTE slot2);

}; //Size: 0x0024



#endif