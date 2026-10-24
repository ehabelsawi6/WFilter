#pragma once
#include "pch.h"

#define REMODEL_PLACEHOLDER

#define REMODEL_DECLARE_VIRTUAL_NOIMPL_DCTOR(className) \
	virtual ~className() { };

#define REMODEL_DECLARE_VIRTUAL_NOIMPL(ret_type, fn, ret_value) \
	virtual ret_type fn { return ret_value; }


#define REMODEL_SAVE_REGISTERS_BEFORE_STDCALL \
{\
    __asm push eax   \
    __asm push ecx   \
    __asm push edx   \
}

#define REMODEL_RESTORE_REGISTERS_AFTER_STDCALL \
{\
    __asm pop edx   \
    __asm pop ecx   \
    __asm pop eax   \
}


