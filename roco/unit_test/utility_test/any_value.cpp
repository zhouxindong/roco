#include "pch.h"
#include "CppUnitTest.h"
#include "utility/any_value.hpp"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace roco;;

namespace utilitytest
{
	TEST_CLASS(any_value_test)
	{
	public:

		TEST_METHOD(Value_holder_test)
		{
			Value_holder<int> v(3);
			Assert::AreEqual(3, v.held);

			Value_holder<std::string> v2("hello");
			Assert::IsTrue(std::string("hello") == v2.held);
			Assert::IsTrue(v2.held == ((Value_holder<std::string>*)v2.clone())->held);
		}

		TEST_METHOD(Any_value_test1)
		{
			Any_value a = 3.14159;
			auto a1 = a.as<double>();
			Assert::AreEqual(3.14159, a1);

			a = "string";
			auto a2 = a.as<const char*>();
			Assert::IsTrue(std::string("string") == std::string(a2));

			a = std::string("string");
			auto a3 = a.as<std::string>();
			Assert::IsTrue(std::string("string") == a3);

			struct obj {
				const char* str() {
					return "string";
				}
			};

			obj* o = new obj();
			a = o;
			auto a4 = a.as<obj*>();
			Assert::IsTrue(std::string("string") == std::string(a4->str()));

			Any_value aa2 = std::move(a);
			auto a5 = aa2.as<obj*>();
			Assert::IsTrue(std::string("string") == std::string(a5->str()));

			Any_value av = std::vector<int>(10, 3);
			aa2 = av;
			auto a6 = aa2.as<std::vector<int>>();
			Assert::AreEqual((size_t)10, a6.size());

			aa2 = std::move(av);
			auto a7 = aa2.as<std::vector<int>>();
			Assert::AreEqual((size_t)10, a7.size());

			double d = 3;
			Any_value aa3(&d);
			d = 3.14159;
			double* pd = aa3.as<double*>();
			Assert::AreEqual(d, *pd);

			Any_value avv = std::vector<int>();
			Assert::IsFalse(avv.can_as<double>());
			Assert::IsTrue(avv.can_as<std::vector<int>>());

			Any_value avv2 = 8;
			Assert::IsTrue(avv2.can_as<int>());
			Assert::IsFalse(avv2.can_as<long>());
		}
	};
}
