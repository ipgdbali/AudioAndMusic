#include "pch.h"
#include "CppUnitTest.h"
#include "../AudioGenerator/COpNegate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(COpNegate)
	{
	public:

		TEST_METHOD(Basic)
		{
			ipgdlib::processor::COpNegate<int> negate(new ipgdlib::processor::CGenConstant<int>(10));

			Assert::AreEqual<int>(negate.get(), -10);
			Assert::AreEqual<int>(negate.get(), -10);
		}
	};
}
