#pragma once
#include "../../Helpers/CStringHelper.h"
class CIFStaticLb
{
public:
	char pad_0000[252]; //0x0000
	w_string_last* wszRegionName; //0x00FC
	char pad_0100[3904]; //0x0100
	const wchar_t* GetText();
	bool SetText(const wchar_t* src);
}; //Size: 0x1040
class CIFMiniMap
{
public:
	char pad_0000[1048]; //0x0000
	CIFStaticLb* MiniMapTitleLabel; //0x0418
	char pad_041C[3108]; //0x041C
}; //Size: 0x1040