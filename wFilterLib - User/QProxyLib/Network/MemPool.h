#pragma once
#ifndef MEM_POOL_H
#define MEM_POOL_H 
//kys man rly :D
//sizeof(SMemPool) = 16

template<typename T>
class CMemPool
{
public:
	T AllocItem() { return  reinterpret_cast<T(__thiscall*)(CMemPool<T>*)>(0x00425400)(this); }
};

#endif