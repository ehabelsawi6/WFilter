#pragma once
#include "../../stdafx.h"
#include "../../Helpers/CStringHelper.h"

//#pragma pack(push, 1)
//class wstring0520
//{
//public:
//	wstring0520(const wchar_t* cstr)
//	{
//		m_allocator = nullptr;
//		m_reserved_size = m_size = wcslen(cstr);
//		if (m_size < 8)
//			memcpy(buffer, cstr, (m_size + 1) * sizeof(wchar_t));
//		else
//			p_buffer = cstr;
//	}
//
//	const wchar_t* c_str() const
//	{
//		return (m_size > 8) ? p_buffer : buffer;
//	}
//
//	int size() const
//	{
//		return m_size;
//	}
//private:
//
//	void* m_allocator; //+4
//	union {
//		wchar_t buffer[8]; //+8
//		const wchar_t* p_buffer; //+4
//	};
//
//	char pad[4];
//
//	int m_size;
//	int m_reserved_size;
//};
//#pragma pack(pop)

class CTextStringManager
{
public:
	w_string_last GetString(const w_string_last &identifier)
	{
		return reinterpret_cast<const w_string_last &(__thiscall *)(CTextStringManager *, const w_string_last&)>(0x008c9bb0)(this, identifier);
	}
};

extern CTextStringManager* g_pTextStrMgr;