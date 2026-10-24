#include "IFSlotWithHelp.h"

void CIFSlotWithHelp::UpdateLocation(DWORD x, DWORD y)
{
	reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, int, int)>(0x6529A0)(this, x, y);
}
void CIFSlotWithHelp::AppendAdvancedInfo(CIFHelperBubbleWindow* window)
{
	reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, CIFHelperBubbleWindow*)>(0x0066FD60)(this, window);
}
void CIFSlotWithHelp::MakeBubble()
{
	reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*)>(0x00686DB0)(this);

}

void CIFSlotWithHelp::ShowGWnd(bool bVisible)
{
	reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, bool)>(0x00652B70)(this, bVisible);
}
