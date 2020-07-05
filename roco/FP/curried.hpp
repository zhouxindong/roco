#pragma once

#ifndef _ROCO_FP_CURRIED_HPP_
#define _ROCO_FP_CURRIED_HPP_

#include "../roco_ns.h"

#include <tuple>
#include <type_traits>

_ROCO_BEGIN

template <typename Function, typename ...CapturedArgs>
class curried {
public:
	curried(Function function, CapturedArgs... args)
		: m_function(function)
		, m_captured(std::make_tuple(args...))
	{
	}

	curried(Function function, std::tuple<CapturedArgs...> args)
		: m_function(function)
		, m_captured(args)
	{
	}

	template <typename ...NewArgs>
	auto operator()(NewArgs&& ...args) const
	{
		auto new_args = std::make_tuple(std::forward<NewArgs>(args)...);
		auto all_args = std::tuple_cat(m_captured, std::move(new_args));

		if constexpr (std::is_invocable<Function, CapturedArgs..., NewArgs...>::value) {
			return std::apply(m_function, all_args);

		}
		else {
			return curried<Function, CapturedArgs..., NewArgs...>(
				m_function, all_args);
		}
	}

private:
	Function m_function;
	std::tuple<CapturedArgs...> m_captured;
};


// Needed for pre-C++17 compilers
template <typename Function>
curried<Function> make_curried(Function&& f)
{
	return curried<Function>(std::forward<Function>(f));
}

_ROCO_END

#endif // _ROCO_FP_CURRIED_HPP_