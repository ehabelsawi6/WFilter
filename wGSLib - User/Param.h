#pragma once
#include "pch.h"

enum GOBJ_PARAM : UINT16
{
	PARAM_LEVEL = 0,
	PARAM_STRENGTH = 1,
	PARAM_INTELLECT = 2,
	PARAM_MAX_HEALTH = 3,
	PARAM_MAX_MANA = 4,
	PARAM_PHY_DEF = 5,
	PARAM_MAG_DEF = 6,
	PARAM_PARRY_RATIO = 9,
	PARAM_HIT_RATE = 11,
	PARAM_PHY_ATTACK_MIN = 13,
	PARAM_PHY_ATTACK_MAX = 14,
	PARAM_MAG_ATTACK_MIN = 15,
	PARAM_MAG_ATTACK_MAX = 16,
	PARAM_PHY_ATTACK_MIN2 = 17,
	PARAM_PHY_ATTACK_MAX2 = 18,
	PARAM_MAG_ATTACK_MIN2 = 19,
	PARAM_MAG_ATTACK_MAX2 = 20,

	//PARAM_ADD_STRENGTH 0x36, 54
	//PARAM_ADD_INTELLECT 0x37, 55

	//used for special equipset boost (garment/protector)
	PARAM_MANA_CONSUMPTION_RELATED = 23,
	PARAM_MOVEMENT_SPEED = 24,
	PARAM_MAX_HP2 = 54,
	PARAM_MAX_MANA2 = 55,

	PARAM_COUNT = 61
};

#ifndef CPARAM_H
#define CPARAM_H
class CParam
{
public:
	char pad_0000[4]; //0x0000
	uintptr_t SomeFlagPossibly; //0x0004
	char pad_0008[20]; //0x0008
	float Unknown; //0x001C
	char pad_0020[4]; //0x0020
	uintptr_t HeapPointer; //0x0024
	float UnknownCanBeFloat; //0x0028
	char pad_002C[12]; //0x002C
	uintptr_t N000051AD; //0x0038
}; //Size: 0x003C

#endif