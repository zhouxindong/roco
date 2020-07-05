#pragma once
#ifndef _ROCO_TMP_QUANTITY_HPP_
#define _ROCO_TMP_QUANTITY_HPP_

#include "../roco_ns.h"

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>

_ROCO_BEGIN

typedef boost::mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
typedef boost::mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
typedef boost::mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
typedef boost::mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> angle;

typedef boost::mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity; // l/t
typedef boost::mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;
typedef boost::mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;
typedef boost::mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;

typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar;

template <class T, class Dimensions>
struct quantity
{
	explicit quantity(T x) : m_value(x) {}

	T value() const
	{
		return m_value;
	}

	template <class OtherDimensions>
	quantity(quantity<T, OtherDimensions> const& rhs)
		: m_value(rhs.value())
	{
		static_assert(boost::mpl::equal<Dimensions, OtherDimensions>::type::value);
	}

private:
	T m_value;
};

// quantity<float, length> l(1.0f);
// quantity<float, mass> m(2.0f);

template <class T, class D>
quantity<T, D>
operator+(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() + y.value());
}

template <class T, class D>
quantity<T, D>
operator-(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() - y.value());
}

//quantity<float, length> len1(1.0f);
//quantity<float, length> len2(2.0f);
//
//len1 = len1 + len2;   // OK

struct plus_f
{
	template <class T1, class T2>
	struct apply
	{
		typedef typename boost::mpl::plus<T1, T2>::type type;
	};
};

template <class T, class D1, class D2>
quantity<
	T,
	typename boost::mpl::transform<D1, D2, plus_f>::type
>
operator*(quantity<T, D1> x, quantity<T, D2> y)
{
	typedef typename boost::mpl::transform<D1, D2, plus_f>::type dim;
	return quantity<T, dim>(x.value() * y.value());
}

//quantity<float, mass> m(5.0f);
//quantity<float, acceleration> a(9.8f);
//(m* a).value();

struct minus_f
{
	template <class T1, class T2>
	struct apply : boost::mpl::minus<T1, T2> {};
};

template <class T, class D1, class D2>
quantity<
	T, 
	typename boost::mpl::transform<D1, D2, minus_f>::type
>
operator/(quantity<T, D1> x, quantity<T, D2> y)
{
	typedef typename boost::mpl::transform<D1, D2, minus_f>::type dim;
	return quantity<T, dim>(x.value() / y.value());
}

_ROCO_END

#endif // _ROCO_TMP_QUANTITY_HPP_