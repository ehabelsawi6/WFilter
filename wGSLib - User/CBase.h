#ifndef C_BASE_H
#define C_BASE_H
#include "pch.h"
class CBase;

//0
typedef LPCSTR* (__stdcall* fnGetTypeNamePtr)();
//1
typedef CBase* (__thiscall* fnConstructor)(CBase* _ecx, BOOL unk);


//VFTABLE - 0x00AE0B00

class CBase
{
public:
	CBase();
	virtual ~CBase();

	LPCSTR*
		GetTypeNamePtr() const;

	LPCSTR
		GetTypeName() const;
private:
	static fnGetTypeNamePtr m_GetTypeNamePtr;
	static fnConstructor m_Ctor;
};

#endif