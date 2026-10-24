#include "IFInventory.h"

CSOItem* CIFInventory::GetItemBySlot(BYTE SlotIndex)
{
	return reinterpret_cast<CSOItem*(__thiscall*)(CIFInventory*, BYTE)>(0x006B3E50)(this, SlotIndex);
}

void CIFInventory::ShowGWnd(bool bVisible)
{
	reinterpret_cast<void(__thiscall*)(CIFInventory*, bool)>(0x00652B70)(this, bVisible);
}
