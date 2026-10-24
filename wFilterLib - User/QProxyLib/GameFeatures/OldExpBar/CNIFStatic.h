#pragma once

#include "CNIFWnd.h"

class CNIFStatic : public CNIFWnd { // 872 bytes
public:
	virtual void SetText(wchar_t* format, ...);
	char pad[32];
	
};
