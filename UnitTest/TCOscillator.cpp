#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ipgdlib::processor;

namespace UnitTest
{
	TEST_CLASS(TestCOscillator)
	{
	public:

		TEST_METHOD(StackInit)
		{
			COscillator<ipgdlib::efpk64Bit> osc(50,
				new CGenConstant<double>(5)
			);

			Assert::AreEqual<double>(osc.get(), 0.0);
			Assert::AreEqual<double>(osc.get(), 0.1);
			Assert::AreEqual<double>(osc.get(), 0.2);
			Assert::AreEqual<double>(osc.get(), 0.3);
			Assert::AreEqual<double>(osc.get(), 0.4);
			Assert::AreEqual<double>(osc.get(), 0.0);

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
