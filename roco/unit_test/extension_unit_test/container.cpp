#include "pch.h"
#include "CppUnitTest.h"
#include "extension/container.hpp"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace roco;
using namespace std;

namespace extensionunittest
{
	TEST_CLASS(container_unittest)
	{
	public:

		TEST_METHOD(erase_remove_test)
		{
			std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
			erase_remove(v, [](int i) {return i == 3; });
			Assert::IsTrue(v.size() == 8);
			Assert::IsTrue(v[0] == 1);
			Assert::IsTrue(v[1] == 2);
			Assert::IsTrue(v[2] == 4);
			Assert::IsTrue(v[3] == 5);
			Assert::IsTrue(v[4] == 6);
			Assert::IsTrue(v[5] == 7);
			Assert::IsTrue(v[6] == 8);
			Assert::IsTrue(v[7] == 9);
		}
	};
}