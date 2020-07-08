#pragma once

#ifndef _ROCO_CODEC_CODE_CONVERTER_HPP_
#define _ROCO_CODEC_CODE_CONVERTER_HPP_

#include "../roco_ns.h"

#include <Windows.h>
#include <string>

#include "../extension/raw_array.hpp"

constexpr unsigned int GBK_CODE_PAGE = 936;
constexpr unsigned char UTF8_BOM[]{ 0xEF, 0xBB, 0xBF };

_ROCO_BEGIN

class Code_converter 
{
public:
	static std::string ansi_to_utf8(const std::string& s)
	{
		return convert_code_(s, CP_ACP, CP_UTF8);
	}

	static std::string utf8_to_ansi(const std::string& s)
	{
		if(!is_bom_utf8(s))
			return convert_code_(s, CP_UTF8, CP_ACP);
		else
		{
			std::string no_bom_s = trim_bom_utf8(s);
			return convert_code_(no_bom_s, CP_UTF8, CP_ACP);
		}
	}

private:
	static std::string convert_code_(const std::string& s, unsigned int s_code, unsigned int d_code)
	{		
		int wlen = ::MultiByteToWideChar(s_code, 0, s.c_str(), -1, NULL, 0);
		wchar_t* wbuf = new wchar_t[static_cast<int>(wlen + 1)];
		::ZeroMemory(wbuf, static_cast<int>(wlen * 2 + 2));
		::MultiByteToWideChar(s_code, 0, s.c_str(), static_cast<int>(s.length()), wbuf, wlen);
		int len = ::WideCharToMultiByte(d_code, 0, wbuf, -1, NULL, NULL, NULL, NULL);
		char* buf = new char[static_cast<int>(len + 1)];
		::ZeroMemory(buf, static_cast<int>(len + 1));
		::WideCharToMultiByte(d_code, 0, wbuf, wlen, buf, len, NULL, NULL);
		std::string ret(buf);
		delete[] wbuf;
		delete[] buf;
		return ret;
	}

	static bool is_bom_utf8(const std::string& s)
	{
		return roco::array_equals(UTF8_BOM, s.c_str(), s.length());
	}

	static std::string trim_bom_utf8(const std::string& s)
	{
		return s.substr(3, s.length() - 3);
	}
};

_ROCO_END

#endif // _ROCO_CODEC_CODE_CONVERTER_HPP_