#pragma once
#include <locale>
#include <codecvt>
#include <string>

#define WSTR(str) StringUtils::to_wstring(str)
#define STR(wstr) StringUtils::to_string(wstr)

namespace StringUtils
{
	std::wstring to_wstring(const std::string& utf8_string)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(utf8_string);
	}

	std::string to_string(const std::wstring& utf16_string)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(utf16_string);
	}
}