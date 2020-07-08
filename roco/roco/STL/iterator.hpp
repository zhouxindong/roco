#pragma once
#ifndef _ROCO_STL_ITERATOR_HPP_
#define _ROCO_STL_ITERATOR_HPP_

#include "../roco_ns.h"

_ROCO_BEGIN

template <typename T>
class ListItem
{
public:
	T value() const {
		return _value;
	}

	ListItem* next() const
	{
		return _next;
	}

private:
	T _value;
	ListItem* _next;
};

template <typename T>
class List
{
	void insert_front(T value);
	void insert_end(T value);
	void display(std::ostream& os = std::cout) const;

private:
	ListItem<T>* _end;
	ListItem<T>* _front;
	long _size;
};

template <class Item>
struct ListIter
{
	Item* ptr;
	ListIter(Item* p = 0)
		:ptr(p) {}

	Item& operator*() const
	{
		return *ptr;
	}

	Item* operator->() const
	{
		return ptr;
	}

	ListIter& operator++()
	{
		ptr = ptr->next();
		return *this;
	}

	ListIter operator++(int)
	{
		ListIter tmp = *this;
		++(*this);
		return tmp;
	}

	bool operator==(const ListIter& i) const
	{
		return ptr == i.ptr;
	}

	bool operator!=(const ListIter& i) const
	{
		return ptr != i.ptr;
	}
};

_ROCO_END

#endif // _ROCO_STL_ITERATOR_HPP_