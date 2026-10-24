#pragma once
#include "../../stdafx.h"
#include "CSOItem.h"
#include "IFSlotWithHelp.h"
class CIFEquipment
{
private:
	char pad_to_location[0x40];
	DWORD PosX;
	DWORD PosY;
	char pad_to_visible[0x19];
	bool isVisible;
	bool isActive;
	char _pad_to_avatar_item_obj[0x580]; // old 5E4
	CIFSlotWithHelp* pSlotWithHelp;

public:
	class CSOItem* GetEquipmentObjectBySlot(BYTE SlotIndex);
	DWORD GetX()
	{
		return this->PosX;
	}
	DWORD GetY()
	{
		return this->PosY;
	}
	CIFSlotWithHelp* getAvatarSlot()
	{
		return this->pSlotWithHelp;
	}
	void SetActive(bool active)
	{
		this->isActive = active;
	}
};