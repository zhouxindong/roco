#pragma once
#ifndef _ROCO_TMP_TYPE_TRAITS_HPP_
#define _ROCO_TMP_TYPE_TRAITS_HPP_

#include "../roco_ns.h"
#include <type_traits>
#include <utility>

_ROCO_BEGIN

/**
*
INVOKE(std::forward<F>(f), std::forward<Args>(args)...)
INVOKE(f, t1, t2, ..., tN) -- #1
1. f��T�ĳ�Ա����ָ��
1.1 std::is_base_of<T, std::decay_t<decltype(t1)>>::value == true
#1 == (t1.*f)(t2, ..., tN)
1.2 std::decay_t<decltype(t1)>��std::reference_wrapper��һ���ػ�
#1 == (t1.get().*f)(t2, ..., tN)
1.3 #1 == ((*t1).*f)(t2, ..., tN)

2. N == 1 and f��T�ĳ�Ա����ָ��(INVOKE(f, t1))
2.1 std::is_base_of<T, std::decay_t<decltype(t1)>>::value == true
#1 == t1.*f
2.2 std::decay_t<decltype(t1)>��std::reference_wrapper��һ���ػ�
#1 == t.get().*f
2.3 #1 == (*t1).*f

3. ��1��2����
#1 == f(t1, t2, ..., tN)
*/

namespace detail {

	/**
	 * VS2017 successful
	 */
	template <class T>
	struct is_reference_wrapper : std::false_type {};

	template <class U>
	struct is_reference_wrapper<std::reference_wrapper<U>> : std::true_type {};

	// invoke_implģ��
	/**
	 * @brief ����ģ�壬����һ��ɵ������ͣ���ȡ��������
	 */
	template<class T> // T is general callable, primary class template
	struct invoke_impl {
		template<class F, class... Args>
		static auto call(F&& f, Args&&... args)
			-> decltype(std::forward<F>(f)(std::forward<Args>(args)...));
	};

	/**
	 *
	 double foo(int);
	 typeid(invoke_impl<double(int)>::call(foo, 3)).name(); // double
	 */

	 /**
	  * @brief ��Աָ���ػ�����ȡ��������
	  */
	template<class B, class MT>
	struct invoke_impl<MT B::*> {
		/**
		 * get()�����ֲ�ͬ������ֱ��ȡ��Աָ����Ϊ�ɵ��ö��󱻵���ʱ�İ󶨶���
		 */

		 // 1. t1�ǳ�Աָ������������� -> (t1.*f)(t2, ..., tN)
		template<class T, class Td = typename std::decay<T>::type,
			class = typename std::enable_if<std::is_base_of<B, Td>::value>::type
		>
			static auto get(T&& t)->T&&;

		// 2. t1��reference_wrapper��װ�࣬����ԭʼ���� -> (t1.get().*f)(t2, ..., tN)
		template<class T, class Td = typename std::decay<T>::type,
			class = typename std::enable_if<is_reference_wrapper<Td>::value>::type
		>
			static auto get(T&& t) -> decltype(t.get());

		// 3. ����Ϊָ�룬��ָ�����Ϊ��Աָ�����󶨵Ķ��� -> ((*t1).*f)(t2, ..., tN)
		template<class T, class Td = typename std::decay<T>::type,
			class = typename std::enable_if<!std::is_base_of<B, Td>::value>::type,
			class = typename std::enable_if<!is_reference_wrapper<Td>::value>::type
		>
			static auto get(T&& t) -> decltype(*std::forward<T>(t));

		// ���ڳ�Ա����ָ��
		template<class T, class... Args, class MT1,
			class = typename std::enable_if<std::is_function<MT1>::value>::type
		>
			static auto call(MT1 B::* pmf, T&& t, Args&&... args)
			-> decltype((invoke_impl::get(std::forward<T>(t)).*pmf)(std::forward<Args>(args)...));

		// ���ڳ�Ա����
		template<class T>
		static auto call(MT B::* pmd, T&& t)
			-> decltype(invoke_impl::get(std::forward<T>(t)).*pmd);
	};

	/**
	 * VS2017 successful
	 */
	template<class F, class... Args, class Fd = typename std::decay<F>::type>
	auto INVOKE(F&& f, Args&&... args)
		-> decltype(invoke_impl<Fd>::call(std::forward<F>(f), std::forward<Args>(args)...));

} // namespace detail

/**
 * VS2017 successful
 typedef double(*pfoo)(int);
 result_of_11<pfoo(int)>::type // double
 */
 // Minimal C++11 implementation:
template <class> struct result_of_11;

template <class F, class... ArgTypes>
struct result_of_11<F(ArgTypes...)> {
	using type = decltype(detail::INVOKE(std::declval<F>(), std::declval<ArgTypes>()...));
};

// Conforming C++14 implementation (is also a valid C++11 implementation):
/**
 * VS2017 successful
 invoke_result<void, pfoo, int>::type // double
 */
namespace detail {
	template <typename AlwaysVoid, typename, typename...>
	struct invoke_result { };

	template <typename F, typename...Args>
	struct invoke_result<decltype(void(detail::INVOKE(std::declval<F>(), std::declval<Args>()...))),
		F, Args...> {
		using type = decltype(detail::INVOKE(std::declval<F>(), std::declval<Args>()...));
	};
} // namespace detail

/**
 * VS2017 successful
 result_of<pfoo(int)>::type
 */
template <class> struct result_of;

template <class F, class... ArgTypes>
struct result_of<F(ArgTypes...)> : detail::invoke_result<void, F, ArgTypes...> {};

/**
 * VS2017 successful
 invoke_result<pfoo, int>::type
 */
template <class F, class... ArgTypes>
struct invoke_result : detail::invoke_result<void, F, ArgTypes...> {};

_ROCO_END

#endif // _ROCO_TMP_TYPE_TRAITS_HPP_