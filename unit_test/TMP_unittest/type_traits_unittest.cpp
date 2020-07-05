#include "pch.h"
#include "CppUnitTest.h"
#include "TMP/type_traits.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace roco;
using namespace std;

namespace TMPunittest
{
	void foo()
	{

	}

	int foo2(int, double)
	{
		return 1;
	}

	class fooClass
	{
	public:
		double operator()(int) const
		{
			return 1;
		}
	};

	class fooclass2
	{};

	TEST_CLASS(type_traits_unittest)
	{
	public:

		TEST_METHOD(Callable_traits_test)
		{
			//Callable_traits<fooClass>::call(3);
			//Callable_traits<fooclass2>::call(3);
		}
	};
}