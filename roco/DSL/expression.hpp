#pragma once

#ifndef _ROCO_DSL_EXPRESSION_HPP_
#define _ROCO_DSL_EXPRESSION_HPP_

#include "../roco_ns.h"

_ROCO_BEGIN

struct plus
{
	static float apply(float a, float b)
	{
		return a + b;
	}
};

struct minus
{
	static float apply(float a, float b)
	{
		return a - b;
	}
};

template <class L, class OpTag, class R>
struct Expression
{
	Expression(L const& l, R const& r)
		: l(l), r(r) {}

	float operator[](unsigned index) const
	{
		retur OpTag::apply(l[index], r[index]);
	}

	L const& l;
	R const& r;
};

template <class L, class R>
Expression<L, plus, R>
operator+(L const& l, R const& r)
{
	return Expression<L, plus, R>(l, r);
}



_ROCO_END

#endif // _ROCO_DSL_EXPRESSION_HPP_