#include "CNIRMManager.h"

void* CNIRMManager::GetWindowActive(DWORD WindowID)
{
	return reinterpret_cast<void*(__thiscall*)(CNIRMManager*, DWORD)>(0x00798c50)(this, WindowID);
}
