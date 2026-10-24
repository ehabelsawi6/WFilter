#include "IFEquipment.h"

CSOItem* CIFEquipment::GetEquipmentObjectBySlot(BYTE SlotIndex)
{
	return reinterpret_cast<CSOItem*(__thiscall*)(CIFEquipment*, BYTE)>(0x006AB6E0)(this, SlotIndex);
}