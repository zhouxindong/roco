#pragma once

#ifndef _ROCO_UTILITY_EASY_SIGNAL_HPP_
#define _ROCO_UTILITY_EASY_SIGNAL_HPP_

#include "../roco_ns.h"

#include <functional>
#include <vector>
#include <algorithm>
#include <utility>

#include "../TMP/easy_bind.hpp"
#include "guid.hpp"
#include "../extension/container.hpp"

_ROCO_BEGIN

// forward declare
template <typename _Signature>
class Easy_signal;

// forward declare
template <typename _Ret, typename ..._Args>
class Easy_signal<_Ret(_Args...)>;

template <typename _Signature>
class Easy_connect;

template <typename _Ret, typename ..._Args>
class Easy_connect<_Ret(_Args...)>
{
public:
	template <typename _Callable>
	Easy_connect(_Callable&& c, Easy_signal<_Ret(_Args...)> & signal)
		: callee_(std::forward<_Callable>(c))
		, id_(guid_hex(24))
		, signal_(std::ref(signal)) 
	{
	}

	Easy_connect(Easy_connect const& rhs)
		: callee_(rhs.callee_)
		, id_(rhs.id_)
		, signal_(rhs.signal_)
		, connected_(rhs.connected_)
	{}

	Easy_connect& operator=(Easy_connect const& rhs)
	{
		callee_ = rhs.callee_;
		id_ = rhs.id_;
		signal_ = rhs.signal_;
		connected_ = rhs.connected_;
		return *this;
	}

	_Ret operator()(_Args... args) const
	{
		return callee_(args...);
	}

public:
	std::string const& get_id() const
	{
		return id_;
	}

	void set_connected(bool connected)
	{
		connected_ = connected;
	}

	bool connected() const
	{
		return connected_;
	}

public:
	void disconnect()
	{
		if (!connected_)
			return;
		signal_.get().disconnect(id_);
		connected_ = false;
	}

private:
	std::function<_Ret(_Args...)> callee_;
	std::string id_;
	std::reference_wrapper<Easy_signal<_Ret(_Args...)>> signal_;
	bool connected_{ true };
};

/**
 * @brief Easy_signal
 */
template <typename _Signature>
class Easy_signal;

template <typename _Ret, typename ..._Args>
class Easy_signal<_Ret(_Args...)>
{
public:
	void swap(Easy_signal& rhs) noexcept
	{
		std::swap(slots_, rhs.slots_);
		std::swap(signals_, rhs.signals_);
	}

public:
	Easy_signal() noexcept {}

	~Easy_signal() {}

	Easy_signal(const Easy_signal& rhs) noexcept
		: slots_(rhs.slots_)
		, signals_(rhs.signals_)
	{
	}

	Easy_signal(Easy_signal&& rhs) noexcept
		: slots_(std::move(rhs.slots_))
		, signals_(std::move(rhs.signals_))
	{
	}

	Easy_signal& operator=(const Easy_signal& rhs) noexcept
	{
		Easy_signal temp(rhs);
		swap(temp);
		return *this;
	}

	Easy_signal& operator=(Easy_signal&& rhs) noexcept
	{
		Easy_signal temp(std::move(rhs));
		swap(temp);
		return *this;
	}

	/**
	 * connect slots to signal
	 1. function
	 2. functor
	 3. lambda
	 */
	template <typename _Callable>
	Easy_connect<_Ret(_Args...)> connect(_Callable&& call) noexcept
	{
		using Functor = std::decay_t<_Callable>;
		auto conn = Easy_connect<_Ret(_Args...)>(std::forward<Functor>(call), *this);
		slots_.push_back(conn);
		return conn;
	}

	/**
	 * connect class member function to signal
	 */
	template <typename _Ret2, typename _Class, std::size_t... Is>
	Easy_connect<_Ret(_Args...)> connect(_Ret2 _Class::* pmf, _Class& obj, detail::indices<Is...>)
	{
		auto conn = Easy_connect<_Ret(_Args...)>(std::bind(pmf, obj, placeholder<Is + 1>{}...), *this);
		slots_.push_back(conn);
		return conn;
	}

	template <typename _Ret2, typename _Class>
	Easy_connect<_Ret(_Args...)> connect(_Ret2 _Class::* pmf, _Class& obj)
	{
		return connect(pmf, obj, detail::build_indices<sizeof...(_Args)>{});
	}

	/**
	 * signal connect to signal
	 */
	void connect(const Easy_signal& rhs)
	{
		signals_.push_back(rhs);
	}

	/**
	 * emit signal
	 */
	void operator()(_Args&&... args) const
	{
		std::for_each(slots_.cbegin(), slots_.cend(), [&](const Easy_connect<_Ret(_Args...)>& f)
			{
				//if (f.connected())
					f(std::forward<_Args>(args)...);
			});
	}

public:
	void disconnect(std::string id)
	{
		auto pos = std::find_if(slots_.begin(), slots_.end(),
			[id](auto& conn) {
				return conn.get_id() == id;
			});
		if (pos != slots_.end())
		{
			slots_.erase(pos);
			//pos->set_connected(false);
		}
	}

private:
	std::vector<Easy_connect<_Ret(_Args...)>> slots_;
	std::vector<std::reference_wrapper<Easy_signal>> signals_;
};

_ROCO_END

#endif // _ROCO_UTILITY_EASY_SIGNAL_HPP_