#include "IFMessageBox.h"

void IFMessageBoxButton::SetGWndSize(int width, int height)
{
	reinterpret_cast<void(__thiscall*)(IFMessageBoxButton*, int, int)>(0x00652970)(this, width, height);
}

void IFMessageBoxButton::MoveGWnd(int x, int y)
{
	reinterpret_cast<void(__thiscall*)(IFMessageBoxButton*, int, int)>(0x006529A0)(this, x, y);
}

bool IFMessageBoxButton::SetText(const wchar_t * src)
{
	return reinterpret_cast<bool(__thiscall*)(IFMessageBoxButton*, const wchar_t*)>(0x00653AC0)(this, src);
}

void IFMessageBox::SetGWndSize(int width, int height)
{
	reinterpret_cast<void(__thiscall*)(IFMessageBox*, int, int)>(0x00652970)(this, width, height);
}
