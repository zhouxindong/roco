#include "pch.h"
#include "CppUnitTest.h"

#include "extension/raw_array.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace roco;

namespace extensionunittest
{
	TEST_CLASS(raw_array_unittest)
	{
	public:

		TEST_METHOD(array_equals_test)
		{
			unsigned char uc[3] = { 0xEF, 0xBB, 0xBF };
			char c[]{ 0xEF, 0xBB, 0xBF, 0xC3, 0x94 };
			Assert::IsTrue(array_equals(uc, c));
			char c2[]{ 0xEF, 0xBB, 0xBF };
			Assert::IsTrue(array_equals(uc, c2));
			char c3[]{ 0xEF, 0xBB };
			Assert::IsFalse(array_equals(uc, c3));

			char* pc = new char[5];
			pc[0] = 0xEF;
			pc[1] = 0xBB;
			pc[2] = 0xBF;
			pc[3] = 0xC3;
			pc[4] = 0x94;
			Assert::IsTrue(array_equals(uc, pc, 5));
			delete[] pc;

			pc = new char[3];
			pc[0] = 0xEF;
			pc[1] = 0xBB;
			pc[2] = 0xBF;
			Assert::IsTrue(array_equals(uc, pc, 3));
			delete[] pc;

			pc = new char[2];
			pc[0] = 0xEF;
			pc[1] = 0xBB;
			Assert::IsFalse(array_equals(uc, pc, 2));
			delete[] pc;
		}
	};
}