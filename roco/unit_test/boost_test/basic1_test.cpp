#include "pch.h"
#include "CppUnitTest.h"
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace boosttest
{
	TEST_CLASS(iterator_test)
	{
	public:

		TEST_METHOD(end_test)
		{
			typedef boost::mpl::vector<char, short, int, long, float, double> types;
			typedef boost::mpl::find<types, long>::type long_pos;
			typedef boost::mpl::end<types>::type finish;
			Assert::IsTrue(!std::is_same_v<long_pos, finish>);
		}

		TEST_METHOD(deref_test)
		{
			typedef boost::mpl::vector<char, short, int, long, float, double> types;
			typedef boost::mpl::find<types, long>::type long_pos;
			typedef boost::mpl::deref<long_pos>::type x;
			Assert::IsTrue(std::is_same_v<x, long>);
		}
	};
}