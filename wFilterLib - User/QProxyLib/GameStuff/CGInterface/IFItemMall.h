#pragma once
class CIFButton
{
public:
	char pad_0000[56]; //0x0000
	bool isVisible; //0x0038
	char pad_0039[1031]; //0x0039
}; //Size: 0x0440
class IFItemMallZZIM
{
public:
	char pad_0000[1040]; //0x0000
	CIFButton* CIFButtonZZIM; //0x0410
	char pad_0414[1060]; //0x0414
}; //Size: 0x0838
class IFItemMall
{
public:
	char pad_0000[2000]; //0x0000
	CIFButton* BtnWornBuy; //0x07D0
	char pad_07D4[4]; //0x07D4
	CIFButton* BtnBuyingList; //0x07D8
	CIFButton* BtnObtainedList; //0x07DC
	char pad_07E0[40]; //0x07E0
	IFItemMallZZIM* CIFItemMallZZIM; //0x0808
	char pad_080C[16]; //0x080C
	bool isDisabled; //0x081C
	char pad_081D[1059]; //0x081D
}; //Size: 0x0C40