#pragma once
#include "../../stdafx.h"
#include "../../Helpers/CStringHelper.h"
class CGFontTexture
{
public:
	DWORD SetColor(DWORD dwNewColor)
	{
		return reinterpret_cast<DWORD(__thiscall*)(CGFontTexture*, DWORD)>(0x008B2B70)(this, dwNewColor);
	}
	void SetText(w_string_last* newText)
	{
		reinterpret_cast<void(__thiscall*)(CGFontTexture*, w_string_last*)>(0x008B3BD0)(this, newText);//this works
	}
};
class CICPlayer {
	virtual void *GetType();
	virtual void *GetParentType();
	virtual ~CICPlayer();
	char cobjchild_padding[2144];
public:
	//4 byte self pointer
	//std::wstring CharName16; //0x0848
	unsigned char level; //0x0868
	long long exp_current;
	int skill_exp;
	char gap_cicplayer[4];
	int skillpoints;
	char gap87C[6292];
	void ShowMessageAbove(const w_string_last* message, DWORD color);
	void MakeEffect(uint32_t effectID);
	void RemoveEffect(uint32_t effectID);
	void SetClothes(int id);
	CICPlayer* GetCICPlayerByUniqueID(DWORD UniqueID);
	DWORD GetObjID();
	std::wstring GetCurrentTitle();
	void SetCurrentTitle(const std::wstring Title);
	void UpdateNameColor(uint32_t Color);
	std::wstring* GetCharName();
	int32_t GetRegion();
	uint32_t GetUniqueID();
	uint8_t GetHwanLevel();
	uint8_t GetJobStatus();
	DWORD GetObjEffect();
	void SetObjEffect(DWORD effect);
	CGFontTexture* GetTitleFontTexture() const;
};

#define g_CICPlayer (*((CICPlayer**)0x00EEF5EC))
#define g_CGamePtr (0x00eece80)
