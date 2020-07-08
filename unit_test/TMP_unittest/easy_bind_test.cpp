#include "pch.h"
#include "CppUnitTest.h"
#include "TMP/easy_bind.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace roco;

namespace TMPunittest
{
	TEST_CLASS(easy_bind_test)
	{
	public:

		TEST_METHOD(indices_test)
		{
			Assert::IsTrue(std::is_base_of_v<
				roco::detail::indices<0>,
				roco::detail::build_indices<1>				
			>);

			Assert::IsTrue(std::is_base_of_v<
				roco::detail::indices<0, 1>,
				roco::detail::build_indices<2>
			>);

			Assert::IsTrue(std::is_base_of_v<
				roco::detail::indices<0, 1, 2>,
				roco::detail::build_indices<3>
			>);
		}
	};
}