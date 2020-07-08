#pragma once
#ifndef _ROCO_FP_FLUENT_PIPE_HPP_
#define _ROCO_FP_FLUENT_PIPE_HPP_

#include "../roco_ns.h"

#include <algorithm>
#include <type_traits>
#include <numeric>
#include <functional>

#include "TMP/type_traits.hpp"

_ROCO_BEGIN

/**
 * @brief map pipe
 */
	template <
	template <typename, typename> class _Cont,
	typename _Callable,
	typename _Tx
	>
	auto pipe_map(const _Cont<_Tx, std::allocator<_Tx>>& c, _Callable f)
{
	using R = typename roco::invoke_result<_Callable, _Tx>::type;
	_Cont<R, std::allocator<R>> r;
	r.resize(c.size());
	std::transform(c.begin(), c.end(), r.begin(), f);
	return r;
}

/**
 * @brief filter pipe
 */
template <
	template <typename, typename> class _Cont,
	typename _Callable,
	typename _Tx
>
auto pipe_filter(const _Cont<_Tx, std::allocator<_Tx>>& c, _Callable f)
{
	_Cont<_Tx, std::allocator<_Tx>> result;
	std::copy_if(c.begin(), c.end(), std::back_inserter(result), f);
	return result;
}

template <
	typename _Tx
>
struct Reduce_policy
{
	static constexpr _Tx init_value = 0;
};

/**
 * @brief reduce
 */
template <
	template <typename, typename> class _Cont,
	typename _Callable,
	typename _Tx,
	typename _Policy = Reduce_policy<_Tx>
>
auto sink(const _Cont<_Tx, std::allocator<_Tx>>& c, _Callable f)
{
	return std::accumulate(c.begin(), c.end(), _Policy::init_value, f);
}

template <
	template <typename, typename > class _Cont,
	typename _Callable,
	typename _Tx
>
auto operator|(const _Cont<_Tx, std::allocator<_Tx>>& c, _Callable f) ->
std::enable_if_t<std::is_same_v<bool, typename roco::invoke_result<_Callable, _Tx>::type>, decltype(pipe_filter(c, f))>
{
	return pipe_filter(c, f);
}

template <
	template <typename, typename > class _Cont,
	typename _Callable,
	typename _Tx
>
auto operator|(const _Cont<_Tx, std::allocator<_Tx>>& c, _Callable f) ->
std::enable_if_t<!std::is_same_v<bool, typename roco::invoke_result<_Callable, _Tx>::type>, decltype(pipe_map(c, f))>
{
	return pipe_map(c, f);
}

template <
	template <typename, typename > class _Cont,
	typename _Tx,
	typename _R,
	typename _Policy = Reduce_policy<_Tx>
>
_R operator|(const _Cont<_Tx, std::allocator<_Tx>>& c, std::function<_R(_R, _Tx)> f)
{
	return std::accumulate(c.begin(), c.end(), _Policy::init_value, f);
}

_ROCO_END

#endif // _ROCO_FP_FLUENT_PIPE_HPP_