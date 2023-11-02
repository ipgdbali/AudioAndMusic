#include "pch.h"
#include "CppUnitTest.h"
#include "../AudioGenerator/COCUNegate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(COCUNegate)
	{
	public:

		TEST_METHOD(Basic)
		{
			ipgdlib::op::COCUNegate<int> negate(new ipgdlib::op::CGenConstant<int>(10));

			Assert::AreEqual<int>(negate.get(), -10);
			Assert::AreEqual<int>(negate.get(), -10);
		}
	};
}
