#ifndef C_NIRMMANAGER_H
#define C_NIRMMANAGER_H
#include "../../includes.h"
#define g_CNIRMManager (*(CNIRMManager**)0x115dd40)
class CNIRMManager
{
public:

	char pad_0000[12]; //0x0000
	DWORD Status; //0x000C
	char pad_0010[12336]; //0x0010

	void* GetWindowActive(DWORD WindowID);

private:

};
#endif