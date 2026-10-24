#pragma once
class padder_m {
	char pad[4];
};

template<typename TKey, typename TValue>
class n_map : padder_m, public std::map<TKey, TValue>
{
	using std::map<TKey, TValue>::map;
};

class CSOItem
{
public:
	char pad_0000[24]; //0x0000
	DWORD unkClass;
	DWORD unk_1;
	DWORD ActiveShit;
	char pad_0001[16];
	DWORD dwObjID; //0x0034
	char pad_0038[84]; //0x0038
	BYTE OptLevel; //0x008C
	BYTE unkOptLevelNear;
	short unkOptLevelNear2;
	char _unk_pad[0x8];
	int CurrDurability; //0x0098
	char pad_009C[44]; //0x009C
	n_map<short,int>* pBluesMap; //0x00C8 BLUES
	DWORD dwBluesSize; //0x009C
	char pad0x009C[16]; //0x009C
	int PhyAtkPwrMax; //0x00E0
	int PhyAtkPwrMin; //0x00E4
	int MagAtkPwrMax; //0x00E8
	int MagAtkPwrMin; //0x00EC
	int BlockingRateValue; //0x00F0
	int MaxDurability; //0x00F4
	float PhyDefPwrValue; //0x00F8
	int ParryRateValue; //0x00FC
	float PhyAbsorption; //0x0100
	DWORD pad_0104; //0x0104
	int CriticalValue; //0x0108
	float MagDefPwrValue; //0x010C
	float MagAbsorption; //0x0110
	float PhyReinforcementMin; //0x0114
	float PhyReinforcementMax; //0x0118
	float MagReinforcementMin; //0x011C
	float MagReinforcementMax; //0x0120
	float PhyReinforcementValue; //0x0124
	float MagReinforcementValue; //0x0128
	DWORD pad_012C; //0x012C
	int AttackRateValue; //0x0130
	char pad_to_fixed_size[160];
	class ObjectData* GetObjectData();
};