#include "CStringHelper.h"
#include <codecvt>


std::string CStringHelper::ws2s(const std::wstring& source)
{
	using convert_typeX = std::codecvt_utf8_utf16<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(source);
}

std::wstring CStringHelper::s2ws(const std::string &str)
{
	std::vector<wchar_t> buf(str.size());
	std::use_facet<std::ctype<wchar_t>>(std::locale("Turkish")).widen(str.data(), str.data() + str.size(), buf.data());

	return std::wstring(buf.data(), buf.size());
}
bool CStringHelper::startsWith(const std::string& haystack, const std::string& needle) {
	return needle.length() <= haystack.length()
		&& std::equal(needle.begin(), needle.end(), haystack.begin());
}
std::string CStringHelper::removeWhiteSpaces(std::string str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}
bool CStringHelper::contains(std::string source, std::string needle)
{
	if (source.find(needle) != std::string::npos) {
		return true;
	}
	return false;
}

std::string CStringHelper::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

std::wstring CStringHelper::ReplaceAllW(std::wstring str, const std::wstring& from, const std::wstring& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}
std::vector<std::string> CStringHelper::split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
		// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;
}
std::vector<std::wstring> CStringHelper::wsplit(const std::wstring &InputString, wchar_t delimiterChar) {
	std::vector<std::wstring> ResultVec;
	std::wstringstream sStream(InputString);
	std::wstring item;

	while (std::getline(sStream, item, delimiterChar)) {
		ResultVec.push_back(item);
	}
	return ResultVec;
};