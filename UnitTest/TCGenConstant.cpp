#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ipgdlib::op;

namespace UnitTest
{
	TEST_CLASS(CGenConstant)
	{
	public:

		TEST_METHOD(StackInit)
		{

			ipgdlib::op::CGenConstant<int> genConstant(10);
			Assert::AreEqual(genConstant.get(), 10);
			Assert::AreEqual(genConstant.get(), 10);

			genConstant.setConstant(30);
			Assert::AreEqual(genConstant.get(), 30);
			Assert::AreEqual(genConstant.get(), 30);
		}

		TEST_METHOD(HeapInit)
		{
			auto  pGenConstant = new ipgdlib::op::CGenConstant<int>(10);

			Assert::AreEqual(pGenConstant->get(), 10);
			Assert::AreEqual(pGenConstant->get(), 10);

			pGenConstant->setConstant(30);
			Assert::AreEqual(pGenConstant->get(), 30);
			Assert::AreEqual(pGenConstant->get(), 30);
		}
	};
}
