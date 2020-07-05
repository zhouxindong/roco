#pragma once
#ifndef _ROCO_EXTENSION_CONTAINER_HPP_
#define _ROCO_EXTENSION_CONTAINER_HPP_

#include "../roco_ns.h"
#include <algorithm>
#include <functional>

_ROCO_BEGIN

/**
 * @brief erase-remove style for container
 */
template <typename _Cont>
inline
_Cont& 
erase_remove(
	_Cont& c, 
	std::function<bool(typename _Cont::value_type)> f
)
{
	c.erase(
		std::remove_if(c.begin(), c.end(),
			f), c.end()
	);
	return c;
}

/**
 * @brief replace new value for set element
 */
template <typename _Cont>
inline
bool
replace_key(
	_Cont& c,
	const typename _Cont::key_type& old_key,
	const typename _Cont::key_type& new_key
)
{
	typename _Cont::iterator pos;
	pos = c.find(old_key);
	if (pos != c.end())
	{
		c.insert(typename _Cont::value_type(new_key, pos->second));
		c.erase(pos);
		return true;
	}
	else
		return false;
}

_ROCO_END

#endif // _ROCO_EXTENSION_CONTAINER_HPP_