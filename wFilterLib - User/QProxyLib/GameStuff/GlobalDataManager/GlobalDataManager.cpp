#include "GlobalDataManager.h"
#include "../../Helpers/CStringHelper.h"
#include "TextStringManager.h"
#include "../CICPlayer/CICPlayer.h"

typedef SGenericObjectData* (__thiscall* fnGetGenericObjectDataByID)(CGlobalDataManager*, DWORD dwObjectID);
fnGetGenericObjectDataByID pfnGetGenericObjectDataByID = NULL;
std::unordered_map<int, int> CGlobalDataManager::UniqueTargetHashmap;
std::unordered_map<int, int> CGlobalDataManager::UniqueTargetHashmapPlayer;
std::unordered_map<uint8_t, std::string> CGlobalDataManager::m_CurrentTitlesList;
std::unordered_map<std::wstring, uint32_t> CGlobalDataManager::m_NameColors;
std::unordered_map<std::wstring, uint32_t> CGlobalDataManager::m_TitleColors;
std::unordered_map<std::wstring, std::string> CGlobalDataManager::m_CustomTitles;
std::unordered_map<int, void*> CGlobalDataManager::m_IconsData;
std::unordered_map<std::wstring, uint32_t> CGlobalDataManager::m_CharacterIcons;
std::list<UniqueNotifyData> CGlobalDataManager::m_UniqueData;
std::unordered_set<int16_t> CGlobalDataManager::m_PartyDisabledRegions;
std::list<EventData> CGlobalDataManager::m_EventsData;
std::unordered_map<int, EventTimes> CGlobalDataManager::m_EventTimes;

//dynamic shop
std::list<DSTitles> CGlobalDataManager::m_DSTitles;


DWORD CGlobalDataManager::SelectedGameChatType;

std::string CGlobalDataManager::GetHwanString(unsigned int hwanLevel)
{
	if (hwanLevel == 0)
		return std::string();
	w_string_last wstr = w_string_last();

	int type = 1;
	if (ObjID > 0)
	{
		if (ObjID >= 1907 && ObjID <= 1932)
			type = 0;
	}
	reinterpret_cast<void(__thiscall*)(CGlobalDataManager*, w_string_last*, unsigned int, unsigned int)>(0x00941000)(g_CGlobalDataManager, &wstr, hwanLevel, type);

	//Convert...
	//delete last char if its space?
	std::wstring wstr_new(wstr.c_str());
	if (wstr.length() == 0)
		return "Title not found in media";
	return std::string(wstr_new.begin(), wstr_new.end());
}

uint8_t CGlobalDataManager::GetEmptyInventorySlots()
{
	DWORD dwCallAddr_1 = 0x00798D00;
	DWORD dwCallAddr_2 = 0x006A1D20;
	DWORD dwCallAddr_3 = 0x006B6230;

	uint8_t remainingSlots = 0;

	__asm
	{
		mov ecx, dword ptr ds : 0x0110F80C;
		call dwCallAddr_1;
		mov ecx, eax;
		call dwCallAddr_2;
		mov ecx, eax;
		call dwCallAddr_3;
		mov remainingSlots, al;
	}

	return remainingSlots;
}
SGenericObjectData* CGlobalDataManager::GetGenericObjectDataByID(DWORD dwObjectID)
{
	//chernobyl noticed some issues regarding getting generic data from the client not sure if it was skill or effect related, did u double checked this?
	//ya itt works on every objects tho, well the chernobyl issue is his own bug tho, he  was applied a (bugfix try) that's why it was happened, i also have that dmp file
	//lemme show it to u tho
	return pfnGetGenericObjectDataByID(g_CGlobalDataManager, dwObjectID);
}
std::wstring CGlobalDataManager::GetObjectName(SGenericObjectData* pObject)
{
	w_string_last* sn_str = reinterpret_cast<w_string_last*>(((DWORD)pObject) + 0x60);
	w_string_last str = w_string_last(sn_str->c_str());
	auto objName = g_pTextStrMgr->GetString(str);
	return std::wstring(objName.c_str());
}

uint8_t CGlobalDataManager::GetHwanLevelByString(const std::string &hwanStr)
{
	for (auto Item : m_CurrentTitlesList)
	{
		if (Item.second == hwanStr)
			return Item.first;
	}
	return 0;
}
std::string CGlobalDataManager::GetHwanStringByLevel(const uint8_t &hwanLevel)
{
	for (auto Item : m_CurrentTitlesList)
	{
		if (Item.first == hwanLevel)
			return Item.second;
	}
	return std::string();
}

int16_t CGlobalDataManager::GetCurrentRegion()
{
	if(g_CICPlayer && g_CGamePtr)
		return *(int16_t*)(0xEEF68C);
	return 0;
}

DWORD CGlobalDataManager::GetEffectIdByName(wchar_t* szNameStr)
{
	return reinterpret_cast<DWORD(__cdecl*)(wchar_t*, DWORD)>(0x00A950A0)(szNameStr, 0);
}

CLevelData* CGlobalDataManager::GetLevelData(int level) {
	return ((CLevelData*(__thiscall*)(CGlobalDataManager*, int level))0x00937F20)(this, level);
}

CGlobalDataManager::CGlobalDataManager()
{
	pfnGetGenericObjectDataByID = reinterpret_cast<fnGetGenericObjectDataByID>(0x0093F710);
}

CGlobalDataManager::~CGlobalDataManager()
{
}