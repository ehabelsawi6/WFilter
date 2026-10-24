#pragma once
#include "../stdafx.h"
#include "MsgStreamBuffer.h"

class CMsgHandler
{
private:
public:
	CMsgHandler();
	~CMsgHandler();

	void SetupHandlers();
}; extern CMsgHandler* g_MsgHandler;