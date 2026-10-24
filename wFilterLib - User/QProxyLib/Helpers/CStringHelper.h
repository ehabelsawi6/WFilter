#pragma once
#include "../stdafx.h"

#pragma pack(push, 1)
struct SStringBufferPtr
{
	const wchar_t* buffer;
	char pad[12];
};
#pragma pack(pop)
class padder {
	char pad_[4];
};
// Use n_string everywhere
class n_string : padder, public std::string {
	using std::string::string;
};
// Use n_wstring everywhere
class w_string_last : padder, public std::wstring {
	using std::wstring::wstring;
};

class CStringHelper
{
public:
	static std::string ws2s(const std::wstring& source);
	static std::wstring s2ws(const std::string& str);
	static bool startsWith(const std::string& haystack, const std::string& needle);
	static bool contains(std::string source, std::string needle);
	static std::string removeWhiteSpaces(std::string str);
	static std::vector<std::string> split(const std::string &s, char delim);
	static std::vector<std::wstring> wsplit(const std::wstring &s,const wchar_t delim);
	static std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
	static std::wstring ReplaceAllW(std::wstring str, const std::wstring& from, const std::wstring& to);
};