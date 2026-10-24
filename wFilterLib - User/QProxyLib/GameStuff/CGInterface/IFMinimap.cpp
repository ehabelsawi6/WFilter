#include "IFMinimap.h"

const wchar_t * CIFStaticLb::GetText()

{
	return reinterpret_cast<const wchar_t*(__thiscall*)(const CIFStaticLb*)>(0x00653350)(this);
}

bool CIFStaticLb::SetText(const wchar_t * src)
{
	reinterpret_cast<void(__thiscall*)(CIFStaticLb*, const wchar_t*)>(0x00635EA0)(this, src);
	return true;
}
