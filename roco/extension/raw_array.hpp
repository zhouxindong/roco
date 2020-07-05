#pragma once
#ifndef _ROCO_EXTENSION_RAW_ARRAY_HPP_
#define _ROCO_EXTENSION_RAW_ARRAY_HPP_

#include "../roco_ns.h"

_ROCO_BEGIN

/**
 * @brief bulid_in array equals
 * 
 */
template <typename _Tx, size_t N, typename _Ty, size_t M>
inline bool array_equals (_Tx(&arr1)[N], _Ty(&arr2)[M])
{
	if (N > M)
		return false;

	for (size_t i = 0; i < N; ++i)
	{
		if (arr1[i] != (_Tx)arr2[i])
			return false;
	}
	return true;
}

template <typename _Tx, size_t N, typename _Ty>
inline bool array_equals(_Tx(&arr1)[N], _Ty const* parr2, size_t len)
{
	if (N > len)
		return false;
	for (size_t i = 0; i < N; ++i)
	{
		if (arr1[i] != (_Tx)parr2[i])
			return false;
	}
	return true;
}

_ROCO_END

#endif // _ROCO_EXTENSION_RAW_ARRAY_HPP_