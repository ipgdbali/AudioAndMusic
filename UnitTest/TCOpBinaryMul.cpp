#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(COpMul)
	{
	public:

		TEST_METHOD(Basic)
		{
			ipgdlib::op::COpBinaryMul<int> Out(
				new CGenConstant<int>(2),
				new CGenConstant<int>(3)
			);

			Assert::AreEqual<int>(Out.get(), 6);
			Assert::AreEqual<int>(Out.get(), 6);
		}
	};
}
