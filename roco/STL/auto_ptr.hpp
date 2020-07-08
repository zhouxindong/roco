#pragma once

#ifndef _ROCO_STL_AUTO_PTR_HPP_
#define _ROCO_STL_AUTO_PTR_HPP_

#include "../roco_ns.h"


_ROCO_BEGIN

template <class T>
class auto_ptr {
public:
	explicit auto_ptr(T* p = 0) : pointee(p) {}

	template <class U>
	auto_ptr(auto_ptr<U>& rhs)
		: pointee(rhs.release()) {}

	~auto_ptr()
	{
		delete pointee;
	}

	template <class U>
	auto_ptr<T>& operator=(auto_ptr<U>& rhs)
	{
		if (this != &rhs)
			reset(rhs.release());
		return *this;
	}

	T& operator*() const
	{
		return *pointee;
	}

	T* operator->() const
	{
		return pointee;
	}

	T* get() const
	{
		return pointee;
	}

private:
	T* pointee;
};
_ROCO_END

#endif // _ROCO_STL_AUTO_PTR_HPP_