#ifndef GAMEWORLDCONTEXTEX_H
#define GAMEWORLDCONTEXTEX_H

#include "CRTNavCellQuad.h"
#include "CGameWorld_Default.h"

//For GetPlayerPosForForceTeleport(CGObjPC* pc);
#pragma pack(push, 1)
typedef struct tPositionWithNavCellQuad
{
	CRTNavCellQuad* pCellQuad; //0
	WORD Unk1; //4 
	WORD Unk2;
	uintptr_t RegionId; //8
	float PosX; //12
	float PosY;//16
	float PosZ;//20
};
#pragma pack(pop)

class GameWorldContextEX
{
public:
	char pad_0000[8]; //0x0000
	tPositionWithNavCellQuad iPosition;
	char pad_0020[4]; //0x0020
	CGameWorld_Default* iCGameWorld_Default; //0x0024
	char pad_0028[24]; //0x0028
}; //Size: 0x0040

#endif