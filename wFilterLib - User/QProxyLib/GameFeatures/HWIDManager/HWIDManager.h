#ifndef Q_LIB_HWID_MANAGER_H
#define Q_LIB_HWID_MANAGER_H
#include "../../Network/MsgStreamBuffer.h"
class HWIDManager
{
public:
	void Initialize();
	void Free();
private:
	CMsgStreamBuffer* packet;
};

#endif