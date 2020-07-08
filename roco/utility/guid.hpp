#pragma once
#ifndef _ROCO_UTILITY_GUID_HPP_
#define _ROCO_UTILITY_GUID_HPP_

#include "../roco_ns.h"

#include <sstream>
#include <random>
#include <string>

_ROCO_BEGIN

inline
unsigned int
random_char()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);
	return dis(gen);
}

inline
std::string
guid_hex(const unsigned int len)
{
	std::ostringstream oss;
	for (unsigned int i = 0; i < len; ++i)
	{
		const auto rc = random_char();
		std::ostringstream hex_stream;
		hex_stream << std::hex << rc;
		auto hex = hex_stream.str();
		oss << (hex.length() < 2 ? '0' + hex : hex);
	}
	return oss.str();
}

_ROCO_END

#endif // _ROCO_UTILITY_GUID_HPP_