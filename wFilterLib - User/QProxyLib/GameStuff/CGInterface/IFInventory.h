#pragma once
#include "../../stdafx.h"
#include "CSOItem.h"
#include "IFEquipment.h"
class CIFInventory
{
public:
	char pad_to_slots[944];
	unsigned int pSlots;
	class CSOItem* GetItemBySlot(BYTE SlotIndex);
	void ShowGWnd(bool bVisible);
};