#pragma once
#ifndef _ROCO_UTILITY_HASH_HPP_
#define _ROCO_UTILITY_HASH_HPP_

#include "../roco_ns.h"

#include <functional>

_ROCO_BEGIN

template <typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


template <typename T>
inline void hash_val(std::size_t& seed, const T& val)
{
	hash_combine(seed, val);
}

template <typename T, typename ...Types>
inline void hash_val(std::size_t& seed, const T& val, const Types&&... args)
{
	hash_combine(seed, val);
	hash_val(seed, args...);
}

template <typename ...Types>
inline std::size_t hash_val(const Types&... args)
{
	std::size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}

/*
class CustomerHash
{
public:
	std::size_t operator()(const Customer& c) const {
		return hash_val(c.fname, c.lname, c.no);
	}
};
*/

_ROCO_END

#endif // _ROCO_UTILITY_HASH_HPP_