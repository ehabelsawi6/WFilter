#pragma once
#ifndef MEM_POOL_MANAGER_H
#define MEM_POOL_MANAGER_H

#include "MemPool.h"

struct SMsgStreamBufferNode;

//NOT the original impl !
class CMemPoolManager
{

private:
	static CMemPool<SMsgStreamBufferNode*>* s_pMsgStreamBufferNodePool;
public:
	static void Initialize();

	template<typename T>
	static T& GetPool()
	{
		T result = nullptr;

		if (std::is_same<T, CMemPool<SMsgStreamBufferNode*>*>())
			result = s_pMsgStreamBufferNodePool;

		return result;
	}
};

#endif