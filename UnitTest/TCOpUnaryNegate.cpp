#include "pch.h"
#include "CppUnitTest.h"
#include "../AudioGenerator/COpUnaryNegate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(COpUnaryNegate)
	{
	public:

		TEST_METHOD(Basic)
		{
			ipgdlib::op::COpUnaryNegate<int> negate(new ipgdlib::op::CGenConstant<int>(10));

			Assert::AreEqual<int>(negate.get(), -10);
			Assert::AreEqual<int>(negate.get(), -10);
		}
	};
}
