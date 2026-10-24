#pragma once
#include "pch.h"

class CAutoCriticalSection
{
private:
	CRITICAL_SECTION m_cs;
public:
	CAutoCriticalSection();
	virtual ~CAutoCriticalSection();

	void Enter();
	void Leave();
};