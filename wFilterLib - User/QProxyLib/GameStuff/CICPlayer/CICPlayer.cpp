#include "CICPlayer.h"
#include "../../GameMain/GameMain.h"

#define MEMUTIL_ADD_PTR(ptr, offset) \
	(((uintptr_t)(ptr)) + offset)

#define MEMUTIL_READ_BY_PTR_OFFSET(ptr, offset, type) \
	*(type*)(((uintptr_t)ptr) + offset)

#define SETUP_CHARNAME_TEXTURE_FUNC_OFFSET					0x009CFD50
#define SETUP_CHAR_TITLE_TEXTURE_FUNC_OFFSET				0x009C28A0

#define GET_CHARACTOR_NAME_STR(ptr) \
	MEMUTIL_READ_BY_PTR_OFFSET(ptr, 0x110, w_string_last)

#define GET_CHARACTOR_TITLE_STR(ptr) \
	MEMUTIL_READ_BY_PTR_OFFSET(ptr, 0x194, w_string_last)

#define GET_CHARACTOR_NAME_TEXTURE(ptr) \
	(CGFontTexture*)(MEMUTIL_ADD_PTR(ptr, 0x12C));

#define GET_CHARACTOR_TITLE_TEXTURE(ptr) \
	(CGFontTexture*)(MEMUTIL_ADD_PTR(ptr, 0x1B0));



CGFontTexture* CICPlayer::GetTitleFontTexture() const
{
	CGFontTexture* pTexture = reinterpret_cast<CGFontTexture*>(
		reinterpret_cast<DWORD>(this->cobjchild_padding - 8) + 0x1B0);
	
	return pTexture;
}

std::wstring CICPlayer::GetCurrentTitle()
{
	w_string_last tmp = GET_CHARACTOR_TITLE_STR(this);
	if(tmp.length() > 0)
		return std::wstring(tmp.c_str());
	return std::wstring(L"");
}

void CICPlayer::SetCurrentTitle(const std::wstring Title)
{
	DWORD shit = reinterpret_cast<DWORD>(this->cobjchild_padding) - 8;
	w_string_last shiit = w_string_last(Title);
	*(w_string_last*)(shit + 0x194) = shiit;
}
int32_t CICPlayer::GetRegion()
{
	return *(int16_t*)((this->cobjchild_padding - 8) + 0xFC);
}
void CICPlayer::SetClothes(int id)
{
	/*
		0x1233 => OV ESI, shit;
		0x1234 => MOV ECX, DWORD PTR[ESI + 0x9C];
	*/
	if (g_CICPlayer)
	{
		const DWORD shit = reinterpret_cast<DWORD>(this->cobjchild_padding) - 8;
		const DWORD call_addr = 0xA60F90;
		__asm
		{
			MOV ESI, shit;
			MOV ECX, DWORD PTR[ESI + 0x9C];
			MOV EAX, id;
			PUSH EAX;
			call call_addr;
		}
	}
}
void CICPlayer::ShowMessageAbove(const w_string_last* message, DWORD color)
{
	reinterpret_cast<void(__thiscall*)(CICPlayer*, const w_string_last*, DWORD)>(0x009c77c0)(this, message, color);
}
void CICPlayer::MakeEffect(uint32_t effectID)
{
	reinterpret_cast<void* (__thiscall*)(CICPlayer*, uint32_t)>(0x009CF960)(this, effectID);
}

void CICPlayer::RemoveEffect(uint32_t effectID)
{
	reinterpret_cast<void* (__thiscall*)(CICPlayer*, uint32_t)>(0x009CD2B0)(this, effectID);
}

CICPlayer* CICPlayer::GetCICPlayerByUniqueID(DWORD UniqueID)
{
	return reinterpret_cast<CICPlayer*(__cdecl*)(DWORD)>(0x009C3220)(UniqueID);
}
uint32_t CICPlayer::GetUniqueID()
{
	return *(uint32_t*)((this->cobjchild_padding - 8)+0xF8);
}
uint8_t CICPlayer::GetHwanLevel()
{
	return *(uint8_t*)((this->cobjchild_padding - 8)+0x764);
}

std::wstring* CICPlayer::GetCharName()
{
	return reinterpret_cast<std::wstring*>((this->cobjchild_padding - 8)+0x114);
}
void CICPlayer::UpdateNameColor(uint32_t Color)
{
	if (GetJobStatus() == 4 && Color != 0xFF62F5B1)
	{
		for (auto Player : g_GlobalDataMgr->m_NameColors)
		{
			if (this->GetCharName()->c_str() == Player.first)
			{
				reinterpret_cast<void(__thiscall*)(CICPlayer*, uint32_t)>(0x009C1920)(this, Player.second);
				break;
			}
		}
	}
	else
		reinterpret_cast<void(__thiscall*)(CICPlayer*, uint32_t)>(0x009C1920)(this, Color);
}
uint8_t CICPlayer::GetJobStatus()
{
	return *(uint8_t*)((this->cobjchild_padding - 8) + 0x50d);
}
DWORD CICPlayer::GetObjID()
{
	return *(DWORD*)((this->cobjchild_padding -8) + 0x21C);
}
DWORD CICPlayer::GetObjEffect()
{//Does this gets the proper NEEDED effect or it might be getting another effect? well, its the proper addr of the effect of the whole objects in sro, and i got it from makeeffect function so xD
	return *(DWORD*)((this->cobjchild_padding -8) + 0x754);
}
void CICPlayer::SetObjEffect(DWORD effect)
{
	*(DWORD*)((this->cobjchild_padding -8) + 0x754) = effect;
}