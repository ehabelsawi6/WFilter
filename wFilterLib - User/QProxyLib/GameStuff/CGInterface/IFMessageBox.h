#pragma once
#include "../../Helpers/CStringHelper.h"
class IFMessageBoxButton
{
public:
	char pad_0000[52]; //0x0000
	uint32_t ID; //0x0034
	bool isVisible; //0x0038
	char pad_0039[7]; //0x0039
	uint32_t XSec; //0x0040
	uint32_t YSec; //0x0044
	uint32_t Width; //0x0048
	uint32_t Height; //0x004C
	void SetGWndSize(int width, int height);
	void MoveGWnd(int x, int y);
	bool SetText(const wchar_t* src);
}; //Size: 0x1430
class IFMessageBox
{
public:
	char pad_0000[64]; //0x0000
	uint32_t XSec; //0x0040
	uint32_t YSec; //0x0044
	uint32_t Width; //0x0048
	uint32_t Height; //0x004C
	char pad_0050[1972]; //0x0050
	IFMessageBoxButton* IFBtnCancel; //0x0804
	IFMessageBoxButton* IFBtnDeath; //0x0808
	IFMessageBoxButton* IFBtnReverse; //0x080C
	IFMessageBoxButton* IFCustomButton; //0x0810
	void SetGWndSize(int width, int height);
}; //Size: 0x1438