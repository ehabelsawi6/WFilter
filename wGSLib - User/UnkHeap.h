#ifndef UNKHEAP_H
#define UNKHEAP_H
#include "pch.h"
class UnkHeap
{
public:
	char pad_0000[16]; //0x0000
	BYTE N0000426D; //0x0010
	BYTE N0000427B; //0x0011
	BYTE N0000427E; //0x0012
	BYTE UnkPvpRelatedCanBe2; //0x0013
	char pad_0014[48]; //0x0014
}; //Size: 0x0044

#endif