#include "MemPoolManager.h"

CMemPool<SMsgStreamBufferNode*>* CMemPoolManager::s_pMsgStreamBufferNodePool = nullptr;

void CMemPoolManager::Initialize()
{
	s_pMsgStreamBufferNodePool = reinterpret_cast<CMemPool<SMsgStreamBufferNode*>*>(0x00EECD98);
}