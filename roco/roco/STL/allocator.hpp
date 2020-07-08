#pragma once
#ifndef _ROCO_STL_ALLOCATOR_HPP_
#define _ROCO_STL_ALLOCATOR_HPP_

#include "../roco_ns.h"

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

_ROCO_BEGIN

template <class T>
inline T* _allocate(std::ptrdiff_t size, T*)
{
	set_new_handler(0);
	T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if (tmp == 0) {
		std::cerr << "out of memory" << std::endl;
		exit(1);
	}
	return tmp;
}

template <class T>
inline void _deallocate(T* buffer)
{
	::operator delete(buffer);
}

template <class T1, class T2>
inline void _construct(T1* p, const T2& value)
{
	new(p) T1(value);
}

template <class T>
inline void _destroy(T* ptr)
{
	ptr->~T();
}

template <class T>
class allocator {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t diference_type;

	template <class U>
	struct rebind {

	};
};

_ROCO_END

#endif // _ROCO_STL_ALLOCATOR_HPP_