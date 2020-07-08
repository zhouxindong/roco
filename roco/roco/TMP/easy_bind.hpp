#pragma once
#ifndef _ROCO_TMP_EASY_BIND_HPP_
#define _ROCO_TMP_EASY_BIND_HPP_

#include "../roco_ns.h"

#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

_ROCO_BEGIN

/**
 * @brief place holder for bind
 */
template <int I>
struct placeholder {
	static constexpr int value = I;
	typedef placeholder<I> type;
};

_ROCO_END

namespace std {
	template <int I>
	struct is_placeholder<roco::placeholder<I>> :
		std::integral_constant<int, I> {};
}

_ROCO_BEGIN

namespace detail
{
	template <std::size_t... Indices>
	struct indices {};

	template <std::size_t... Is>
	struct build_indices;

	template <std::size_t N, std::size_t... Is>
	struct build_indices<N, Is...>
		: build_indices<N - 1, N - 1, Is...> {};

	template <std::size_t... Is>
	struct build_indices<0, Is...> : indices<Is...> {};

	/**
	 * @brief need C++17
	 */
	//template <std::size_t... Is>
	//void show(indices<Is...>)
	//{
	//	(((std::cout << " ") << Is), ...);
	//}

	/**
	 * @brief apply1
	 */
	template <std::size_t... Is>
	std::vector<std::size_t> make_index_vector(indices<Is...>)
	{
		return { Is... };
	}

	/**
	 * @brief apply2
	 * @usage gen_placeholders(build_indices<N>())
	 */
	template <std::size_t... Is>
	auto gen_placeholders(indices<Is...>)
	{
		return std::make_tuple(placeholder<Is + 1>()...);
	}

	template<std::size_t... Is, class F, class... Args>
	auto easy_bind(indices<Is...>, F const& f, Args&&... args)
		-> decltype(std::bind(f, std::forward<Args>(args)...,
			placeholder<Is + 1>{}...))
	{
		return std::bind(f, std::forward<Args>(args)...,
			placeholder<Is + 1>{}...);
	}

	// easy_bind(build_indices<sizeof...(Args)>(), ...)

} // detail::

_ROCO_END
#endif // _ROCO_TMP_EASY_BIND_HPP_