#include "pch.h"
#include "GObjChar.h"
#include "MemoryUtility.h"


void CGObjChar::SetBodyMode(BYTE bodymode)
{
	CMemoryUtility::call_virtual<void(__thiscall*)(CGObjChar*, BYTE, BYTE, float, BYTE)>(this, 198)(this, bodymode, -1, 0.f, 0);
}