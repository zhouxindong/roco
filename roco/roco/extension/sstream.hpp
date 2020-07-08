#pragma once

#ifndef _ROCO_EXTENSION_SSTREAM_HPP_
#define _ROCO_EXTENSION_SSTREAM_HPP_

#include "../roco_ns.h"

#include <sstream>

_ROCO_BEGIN

/**
 * @brief clear ostringstream rdbuf
 */
template <
	typename CharT, 
	typename Traits = std::char_traits<CharT>,
	typename Allocator = std::allocator<CharT>
>
std::basic_ostringstream<CharT, Traits, Allocator>&
clear_content(std::basic_ostringstream<CharT, Traits, Allocator>& oss)
{
	oss.str(std::basic_string<CharT, Traits, Allocator>());
	return oss;
}

_ROCO_END

#endif // _ROCO_EXTENSION_SSTREAM_HPP_