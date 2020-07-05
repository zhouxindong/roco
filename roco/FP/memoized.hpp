#pragma once

#ifndef _ROCO_FP_MEMOIZED_HPP_
#define _ROCO_FP_MEMOIZED_HPP_

#include "../roco_ns.h"

#include <map>
#include <tuple>

_ROCO_BEGIN

template <typename Result, typename ...Args>
auto make_memoized(Result(*f)(Args...))
{
	std::map<std::tuple<Args...>, Result> cache;

	return [f, cache](Args... args) mutable -> Result
	{
		const auto args_tuple = std::make_tuple(args...);
		const auto cached = cache.find(args_tuple);

		if (cached == cache.end()) {
			auto result = f(args...);
			cache[args_tuple] = result;
			return result;
		}
		else {
			return cached->second;
		}
	};
}

_ROCO_END

#endif // _ROCO_FP_MEMOIZED_HPP_