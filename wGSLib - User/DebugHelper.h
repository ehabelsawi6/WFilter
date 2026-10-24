#pragma once
#include "pch.h"

class CDebugHelper
{
private:
	static BOOL SetDebugPrivilege(BOOL bEnable);
public:
	static bool Initialize();
	static BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
	static std::string DumpExceptionRecord(_EXCEPTION_RECORD* pRecord);
	static std::string DumpExceptionContext(_CONTEXT* pContext);
	static std::string DumpStack(int count);

};