#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(COpAdd)
	{
	public:

		TEST_METHOD(Basic)
		{
			ipgdlib::processor::COpAdd<int> Out(
				new CGenConstant<int>(10),
				new CGenConstant<int>(30)
			);

			Assert::AreEqual<int>(Out.get(), 40);
			Assert::AreEqual<int>(Out.get(), 40);
		}
	};
}
