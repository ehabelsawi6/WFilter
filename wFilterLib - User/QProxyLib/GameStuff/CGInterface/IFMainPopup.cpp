#include "IFMainPopup.h"

CIFEquipment* CIFMainPopup::GetEquipment(void)
{
	return reinterpret_cast<CIFEquipment*(__thiscall*)(CIFMainPopup*)>(0x006A1D50)(this);
}

CIFInventory* CIFMainPopup::GetInventory(void)
{
	return reinterpret_cast<CIFInventory*(__thiscall*)(CIFMainPopup*)>(0x006A1D20)(this);
}