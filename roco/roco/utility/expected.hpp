#pragma once
#ifndef _ROCO_UTILITY_EXPECTED_HPP_
#define _ROCO_UTILITY_EXPECTED_HPP_

#include "../roco_ns.h"

#include <stdexcept>

_ROCO_BEGIN

template <typename T, typename E>
class expected
{
public:
	using value_type = T;
	using error_type = E;

private:
	union 
	{
		T value_;
		E error_;
	};
	bool valid_;

public:
	T& get()
	{
		return get_impl();
	}

	const T& get() const {
		return get_impl();
	}

	E& error()
	{
		return error_impl();
	}

	const E& error() const {
		return error_impl();
	}

	/**
	 * @brief valid value
	 */
	template <typename ...Args>
	static expected success(Args&&... params)
	{
		expected result;
		result.valid_ = true;
		new (&result.value_)
			T(std::forward<Args>(params)...); // placement new
		return result;
	}

	template <typename ...Args>
	static expected error(Args&&... params)
	{
		expected result;
		result.valid_ = false;
		new (&result.error_)
			E(std::forward<Args>(params)...);
		return result;
	}

	~expected()
	{
		if (valid_)
			value_.~T();
		else
			error_.~E();
	}

	expected(const expected& other)
		: valid_(other.valid_)
	{
		if (valid_)
		{
			new (&value_)
				T(other.value_);
		}
		else
		{
			new (&error_)
				E(other.error_);
		}
	}

	expected(expected&& other)
		: valid_(other.valid_)
	{
		if (valid_)
		{
			new (&value_)
				T(std::move(other.value_));
		}
		else
		{
			new (&error_)
				E(std::move(other.error_));
		}
	}

	void swap(expected& other)
	{
		using std::swap;
		if (valid_)
		{
			if (other.valid_)
			{
				swap(value_, other.value_);
			}
			else
			{
				auto temp = std::move(other.error_);
				other.error_.~E();
				new (&other.value_) T(std::move(value_));
				value_.~T();
				new (&error_) E(std::move(temp));
				std::swap(valid_, other.valid_);
			}
		}
		else
		{
			if (other.valid_)
			{
				other.swap(*this);
			}
			else
			{
				swap(error_, other.error_);
			}
		}
	}

	expected& operator=(expected other)
	{
		swap(other);
		return *this;
	}

	operator bool() const {
		return valid_;
	}

private:
	T& get_impl()
	{
		if (!valid_)
		{
			throw std::logic_error("Missing a value");
		}
		return value_;
	}

	E& error_impl()
	{
		if (valid_)
		{
			throw std::logic_error("There is no error");
		}
		return error_;
	}
};

_ROCO_END

#endif // _ROCO_UTILITY_EXPECTED_HPP_