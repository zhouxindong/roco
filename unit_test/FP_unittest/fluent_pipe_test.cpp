#include "pch.h"
#include "CppUnitTest.h"
#include "FP/fluent_pipe.hpp"

#include <vector>
#include <string>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace roco;

namespace FPunittest
{
	class Addtwo
	{
	public:
		double operator()(int i) const
		{
			return i + 2.0;
		}
	};

	class OddFilter
	{
	public:
		bool operator()(int i) const
		{
			return i % 2 != 0;
		}
	};

	float add2(int i)
	{
		return i + 3.23f;
	}

	bool odd(int i)
	{
		return i % 2 != 0;
	}

	class SumClass
	{
	public:
		int operator()(int r, int i) const
		{
			return r + i;
		}
	};

	int sum_func(int r, int i)
	{
		return r + i;
	}

	TEST_CLASS(fluent_pipe_test)
	{
	public:


		TEST_METHOD(map_test)
		{
			std::vector<int> v{ 1,2,3,4,5,6 };
			auto r = pipe_map(v, Addtwo());
			Assert::IsTrue(r.size() == 6);
			Assert::IsTrue(r[0] == 3.0);
			Assert::IsTrue(r[1] == 4.0);
			Assert::IsTrue(r[2] == 5.0);
			Assert::IsTrue(r[3] == 6.0);
			Assert::IsTrue(r[4] == 7.0);
			Assert::IsTrue(r[5] == 8.0);

			auto r2 = pipe_map(v, add2);
			Assert::IsTrue(r2.size() == 6);
			Assert::IsTrue(r2[0] == 4.23f);
			Assert::IsTrue(r2[1] == 5.23f);
			Assert::IsTrue(r2[2] == 6.23f);
			Assert::IsTrue(r2[3] == 7.23f);
			Assert::IsTrue(r2[4] == 8.23f);
			Assert::IsTrue(r2[5] == 9.23f);

			auto r3 = pipe_map(v, [](int i)->std::string {
				std::ostringstream oss;
				oss << i;
				return oss.str();
				});
			Assert::IsTrue(r3.size() == 6);
			Assert::IsTrue(r3[0] == "1");
			Assert::IsTrue(r3[1] == "2");
			Assert::IsTrue(r3[2] == "3");
			Assert::IsTrue(r3[3] == "4");
			Assert::IsTrue(r3[4] == "5");
			Assert::IsTrue(r3[5] == "6");
		}

		TEST_METHOD(filter_test)
		{
			std::vector<int> v{ 1,2,3,4,5,6 };
			auto r = pipe_filter(v, OddFilter());
			Assert::IsTrue(r.size() == 3);
			Assert::IsTrue(r[0] == 1);
			Assert::IsTrue(r[1] == 3);
			Assert::IsTrue(r[2] == 5);

			auto r2 = pipe_filter(v, odd);
			Assert::IsTrue(r2.size() == 3);
			Assert::IsTrue(r2[0] == 1);
			Assert::IsTrue(r2[1] == 3);
			Assert::IsTrue(r2[2] == 5);

			auto r3 = pipe_filter(v, [](int i) {
				return i % 2 != 0;
				});
			Assert::IsTrue(r3.size() == 3);
			Assert::IsTrue(r3[0] == 1);
			Assert::IsTrue(r3[1] == 3);
			Assert::IsTrue(r3[2] == 5);
		}

		TEST_METHOD(reduce_test)
		{
			std::vector<int> v{ 1,2,3,4,5,6 };
			auto sum = sink(v, SumClass());
			Assert::IsTrue(sum == 21);

			auto sum3 = sink(v, [](int r, int i) {
				return r + i;
				});
			Assert::IsTrue(sum3 == 21);

			auto sum2 = sink(v, sum_func);
			Assert::IsTrue(sum2 == 21);
		}

		TEST_METHOD(operator_pipe_test)
		{
			std::vector<int> v{ 1,2,3,4,5,6 };
			auto r = v | OddFilter();
			Assert::IsTrue(r.size() == 3);
			Assert::IsTrue(r[0] == 1);
			Assert::IsTrue(r[1] == 3);
			Assert::IsTrue(r[2] == 5);

			auto r2 = v | Addtwo();
			Assert::IsTrue(r2.size() == 6);
			Assert::IsTrue(r2[0] == 3.0);
			Assert::IsTrue(r2[1] == 4.0);
			Assert::IsTrue(r2[2] == 5.0);
			Assert::IsTrue(r2[3] == 6.0);
			Assert::IsTrue(r2[4] == 7.0);
			Assert::IsTrue(r2[5] == 8.0);

			auto r3 = v | OddFilter() | Addtwo();
			Assert::IsTrue(r3.size() == 3);
			Assert::IsTrue(r3[0] == 3.0);
			Assert::IsTrue(r3[1] == 5.0);
			Assert::IsTrue(r3[2] == 7.0);

			auto r4 = v | std::function<int(int, int)>(SumClass());
			Assert::IsTrue(r4 == 21);
		}
	};
}