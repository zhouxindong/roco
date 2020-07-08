#include "pch.h"
#include "CppUnitTest.h"
#include "extension/string.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace roco;
using namespace std;

namespace extensionunittest
{
	TEST_CLASS(string_unittest)
	{
	public:

		TEST_METHOD(trim_test)
		{
			string s = "abcd";
			Assert::IsTrue(s == trim_left(s));
			Assert::IsTrue(s == trim_right(s));
			Assert::IsTrue(s == trim(s));

			string s2 = " abcd";
			Assert::IsTrue(s == trim_left(s2));
			Assert::IsTrue(s2 == trim_right(s2));
			Assert::IsTrue(s == trim(s2));

			string s3 = "     abcd";
			Assert::IsTrue(s == trim_left(s3));
			Assert::IsTrue(s3 == trim_right(s3));
			Assert::IsTrue(s == trim(s3));

			string s4 = "abcd  ";
			Assert::IsTrue(s4 == trim_left(s4));
			Assert::IsTrue(s == trim_right(s4));
			Assert::IsTrue(s == trim(s4));

			string s5 = "    abcd  ";
			Assert::IsTrue("abcd  " == trim_left(s5));
			Assert::IsTrue("    abcd" == trim_right(s5));
			Assert::IsTrue(s == trim(s5));
		}
	};
}