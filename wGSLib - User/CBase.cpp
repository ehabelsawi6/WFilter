#include "pch.h"
#include "CBase.h"

bool m_isInitialized = false;

fnGetTypeNamePtr CBase::m_GetTypeNamePtr = 0;
fnConstructor CBase::m_Ctor = 0;

CBase::CBase()
{
	if (!m_isInitialized)
	{
		m_GetTypeNamePtr = reinterpret_cast<fnGetTypeNamePtr>(0x009761B0);
		m_Ctor = reinterpret_cast<fnConstructor>(0x0042F650);
		m_isInitialized = true;
	}

	m_Ctor(this, FALSE);
}

CBase::~CBase()
{

}

LPCSTR*
CBase::GetTypeNamePtr() const
{
	return m_GetTypeNamePtr();
}

LPCSTR
CBase::GetTypeName() const
{
	return *this->GetTypeNamePtr();
}