#pragma once
#include "../../stdafx.h"
#include "CSOItem.h"
#include "IFHelperBubbleWindow.h"
class Helper
{
public:
	DWORD selfPtr;
};
class CIFSlotWithHelp
{
public:
	char pad_0000[48]; //0x0000
	Helper* getPtr;
	DWORD dwSlotID; //0x0034
	char pad_0038[8]; //0x0038
	DWORD XPos; //0x0040
	DWORD YPos; //0x0044
	DWORD dwWidth; //0x0048
	DWORD dwHeight; //0x004C
	char pad_0050[16]; //0x0050
	int8_t N00000067; //0x0060
	bool bisVisible; //0x0061
	char pad_0062[286]; //0x0062
	bool bIconVisible; //0x0180
	char pad_0181[491]; //0x0181
	DWORD dwSlotType; //0x036C
	DWORD dwSlotType2; //0x0370
	char pad_0374[28]; //0x0374
	CSOItem* pCSOItem; //0x0390 total 916
	char pad_0394[820]; //0x6C8
	void UpdateLocation(DWORD x, DWORD y);
	void AppendAdvancedInfo(CIFHelperBubbleWindow* window);
	void MakeBubble();
	void ShowGWnd(bool bVisible);
}; //Size: 0x140C