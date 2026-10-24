#ifndef Q_PHBOT_MANAGER_H
#define Q_PHBOT_MANAGER_H
#include "../../stdafx.h"
#include "../../Network/MsgStreamBuffer.h"
class PHBotManager
{
public:
	void Handle(CMsgStreamBuffer* packet);
	PHBotManager();

private:

};
#endif