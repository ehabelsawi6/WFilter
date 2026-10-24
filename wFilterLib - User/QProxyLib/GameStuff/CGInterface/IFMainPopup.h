#pragma once
#include "IFInventory.h"
#include "IFEquipment.h"

class CIFPlayerInfo
{
public:
	char pad_0000[964]; //0x0000
	uint32_t StartPoint; //0x03C4
};
class CIFMainPopup
{
private:
	char pad_to_location[0x40];
	DWORD PosX;
	DWORD PosY;
	char pad_to_visible[0x19];
	bool isVisible;
	char pad_to_cifplayerinfo[0x76E];
	CIFPlayerInfo* m_CIFPlayerInfo;
public:
	class CIFEquipment* GetEquipment();
	class CIFInventory* GetInventory();
	bool GetVisible()
	{
		return this->isVisible;
	}
	void SetVisible(const bool visible)
	{
		this->isVisible = visible;
	}
	DWORD GetX()
	{
		return this->PosX;
	}
	DWORD GetY()
	{
		return this->PosY;
	}
	void SetX(const DWORD x)
	{
		this->PosX = x;
	}
	void SetY(const DWORD y)
	{
		this->PosY = y;
	}
	CIFPlayerInfo* GetPlayerInfo()
	{
		return this->m_CIFPlayerInfo;
	}
};