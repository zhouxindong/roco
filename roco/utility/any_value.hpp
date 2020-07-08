#pragma once

#ifndef _ROCO_UTILITY_ANY_VALUE_HPP
#define _ROCO_UTILITY_ANY_VALUE_HPP

#include "../roco_ns.h"

#include <typeinfo>
#include <utility>
#include <type_traits>
#include <string>

_ROCO_BEGIN

/**
* @brief 动多态的基础
* @note 各种类型数据的抽象
*/
class Holder_base
{
public:
	virtual ~Holder_base() {} // abstract base class need

public:
	virtual const std::type_info& type() const = 0;
	virtual Holder_base* clone() const = 0;	// virtual constructor
};

/**
* @brief 实际存放特定类型数据的派生类
*/
template <typename _Value_type>
class Value_holder : public Holder_base
{
public:
	template <typename _Tx>
	Value_holder(_Tx&& value)
		: held(std::forward<_Tx>(value)) {}

public:
	virtual const std::type_info& type() const
	{
		return typeid(std::decay_t<_Value_type>);
	}

	virtual Holder_base* clone() const
	{
		return new Value_holder(held);
	}

public:
	_Value_type held;
};

/**
* @brief class can hold any type value
*/
class Any_value
{
	Holder_base* holder_;

public:
	friend void swap(Any_value& a, Any_value& b) noexcept;

	Any_value() noexcept : holder_(nullptr) {}

	Any_value(const Any_value& rhs) noexcept :
		holder_(rhs.holder_ != nullptr ? rhs.holder_->clone() : nullptr)
	{
	}

	Any_value(Any_value&& rhs) noexcept :
		holder_(rhs.holder_)
	{
		rhs.holder_ = nullptr;
	}

	Any_value& operator=(const Any_value& rhs) noexcept
	{
		Any_value tmp(rhs);
		swap(*this, tmp);
		return *this;
	}

	Any_value& operator=(Any_value&& rhs) noexcept
	{
		swap(*this, rhs);
		return *this;
	}

	template <
		typename _Tx,
		typename = typename std::enable_if<!std::is_same<Any_value, typename std::decay<_Tx>::type>::value>::type>
		Any_value(_Tx&& value)
		: holder_(new Value_holder<typename std::decay<_Tx>::type>(std::forward<_Tx>(value)))
	{
	}

	template <
		typename _Tx,
		typename = typename std::enable_if<!std::is_same<Any_value, typename std::decay<_Tx>::type>::value>::type>
		Any_value& operator=(_Tx&& rhs)
	{
		delete holder_;
		holder_ = new Value_holder<typename std::decay<_Tx>::type>(std::forward<_Tx>(rhs));
		return *this;
	}

	template <typename _Tx>
	bool can_as() const
	{
		if (holder_ == nullptr)
			return false;

		return (typeid(typename std::decay<_Tx>::type).hash_code() == type().hash_code());
	}

	template <typename _Tx>
	bool can_as()
	{
		if (holder_ == nullptr)
			return false;

		return (typeid(typename std::decay<_Tx>::type).hash_code() == type().hash_code());
	}

	template <typename _Tx>
	const _Tx& as() const
	{
		if (!can_as<_Tx>())
			throw std::bad_cast();
		return static_cast<Value_holder<_Tx>*>(holder_)->held;
	}

	template <typename _Tx>
	_Tx& as()
	{
		if (!can_as<_Tx>())
			throw std::bad_cast();
		return static_cast<Value_holder<_Tx>*>(holder_)->held;
	}

	~Any_value()
	{
		delete holder_;
	}

	const std::type_info& type() const {
		return holder_ ? holder_->type() : typeid(void);
	}
};

inline
void
swap(Any_value& a, Any_value& b) noexcept
{
	std::swap(a.holder_, b.holder_);
}

_ROCO_END

#endif // _ROCO_UTILITY_ANY_VALUE_HPP