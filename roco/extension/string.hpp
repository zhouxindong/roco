#pragma once
#ifndef _ROCO_EXTENSION_STRING_HPP_
#define _ROCO_EXTENSION_STRING_HPP_

#include "../roco_ns.h"

#include <string>
#include <algorithm>

_ROCO_BEGIN

inline 
bool is_not_space(char c)
{
	return c != ' ';
}

inline
std::string trim_left(std::string s)
{
	s.erase(s.begin(),
		std::find_if(s.begin(), s.end(), is_not_space));
	return (s);
}

inline 
std::string trim_right(std::string s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), is_not_space).base(),
		s.end());
	return (s);
}

inline
std::string trim(std::string s)
{
	return trim_left(trim_right(std::move(s)));
}

_ROCO_END

#endif // _ROCO_EXTENSION_STRING_HPP_