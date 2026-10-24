#ifndef Q_GLOBAL_DATA_MANAGER_H
#define Q_GLOBAL_DATA_MANAGER_H
#include "../../stdafx.h"
#include <unordered_map>
#include "../CGInterface/CSOItem.h"
#include <ctime>
#include <chrono>
#include "../../Network/MsgStreamBuffer.h"
#include <unordered_set>
#pragma pack(push, 1)
struct SGenericObjectData
{
	//Maybe, TID... didn't look into this
	DWORD dwUnknown1;
	DWORD dwRefObjID;
	char pad_to_rarity[152];
	uint8_t rarity;
};
#pragma pack(pop)
struct UniqueNotifyData
{
	bool bState;
	int RefObjID;
	std::string szKillerName;
	std::wstring UniqueName;
	std::string time;
};
struct GlobalChat
{
	int index;
	std::wstring msg;
	bool completed;
	CMsgStreamBuffer* buffer;
};

class CLevelData {
public:
	char pad[8];
	long long Exp_C;
};
struct EventData
{
	int ID;
	std::string Name;
	std::string AreaName;
	std::string Description;
	int Rewards;
};
struct EventTimes {
	std::string Name;
	std::string Time;
};

struct DSTitles
{
//	int Id;
	int TitleId;
	int Price;
};

struct Settings
{
	bool TitleManager;
	bool UniqueStatus;
	bool EventTimes;
	bool GrantName;
	bool CustomTitle;
	bool DynamicShop;
	bool Facebook;
	bool Discord;
	bool Website;
	std::string FacebookLink;
	std::string DiscordLink;
	std::string WebsiteLink;

};

class CGlobalDataManager
{
public:
	static std::unordered_map<int, int> UniqueTargetHashmap;
	static std::unordered_map<int, int> UniqueTargetHashmapPlayer;
	static std::unordered_map<uint8_t, std::string> m_CurrentTitlesList;
	static std::unordered_map<std::wstring, uint32_t> m_NameColors;
	static std::unordered_map<std::wstring, uint32_t> m_TitleColors;
	static std::unordered_map<std::wstring, std::string> m_CustomTitles;
	static std::unordered_map<int, void*> m_IconsData;
	static std::unordered_map<std::wstring, uint32_t> m_CharacterIcons;
	static std::list<UniqueNotifyData> m_UniqueData;
	static std::unordered_set<int16_t> m_PartyDisabledRegions;
	static std::list<EventData> m_EventsData;
	static std::unordered_map<int, EventTimes> m_EventTimes;
	static std::list<DSTitles> m_DSTitles;
	

	uint64_t currDate;
	uint16_t ObjID;

	std::string GetHwanString(unsigned int hwanLevel);

	uint8_t GetEmptyInventorySlots();

	CGlobalDataManager();
	~CGlobalDataManager();

	SGenericObjectData* GetGenericObjectDataByID(DWORD dwObjectID);
	std::wstring GetObjectName(SGenericObjectData* pObject);
	uint8_t GetHwanLevelByString(const std::string &hwanStr);
	std::string GetHwanStringByLevel(const uint8_t &hwanLevel);
	int16_t GetCurrentRegion();
	DWORD GetEffectIdByName(wchar_t* szNameStr);
	DWORD m_GlobalTextIndex;
	std::list<GlobalChat> GlobalChatLog;
	std::wstring m_CurrentLinkedItemName;
	DWORD m_LinkedGlobalItemBegin;
	DWORD m_LinkedGlobalItemEnd;
	uint8_t m_LinkedGlobalSlot;
	static DWORD SelectedGameChatType;
	//uint8_t m_CustomTitleCredits;

	Settings m_Settings;


	uint32_t DSPoints;
	uint32_t DShopNameColorPrice;
	uint32_t DShopTitleColorPrice;
	uint32_t DShopCustomTitlePrice;

	CLevelData* GetLevelData(int level);
};

#define g_CGlobalDataManager ((CGlobalDataManager*)0x00EEDF08)
#endif