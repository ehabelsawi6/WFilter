#ifndef Q_PLAYER_DATA
#define Q_PLAYER_DATA
#include "../stdafx.h"
class Character
{
struct stIngameData
{
	uint32_t ServerTime;
	uint32_t RefObjID;
	uint8_t Scale;
	uint8_t CurLevel;
	uint8_t MaxLevel;
	uint64_t ExpOffset;
	uint32_t SExpOffset;
	uint64_t Gold;
	uint32_t SkillPoint;
	uint8_t HwanLevel;
	uint8_t InventorySize;
};

public:
	std::wstring name;
	uint32_t uniqueid;
	stIngameData* Info;

	void Init();
	bool GotData;
};
extern Character* g_Character;
#endif