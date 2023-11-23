#include "pch.h"
#include "CppUnitTest.h"
#include "../AudioGenerator/CGenConstant.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ipgdlib::processor;

namespace UnitTest
{
	TEST_CLASS(TCGenConstant)
	{
	public:

		TEST_METHOD(StackInit)
		{

			CGenConstant<int> genConstant(10);
			Assert::AreEqual(genConstant.get(), 10);
			Assert::AreEqual(genConstant.get(), 10);

			genConstant.setConstant(30);
			Assert::AreEqual(genConstant.get(), 30);
			Assert::AreEqual(genConstant.get(), 30);
		}

		TEST_METHOD(HeapInit)
		{
			auto  pGenConstant = new CGenConstant<int>(10);

			Assert::AreEqual(pGenConstant->get(), 10);
			Assert::AreEqual(pGenConstant->get(), 10);

			pGenConstant->setConstant(30);
			Assert::AreEqual(pGenConstant->get(), 30);
			Assert::AreEqual(pGenConstant->get(), 30);
		}
	};
}
