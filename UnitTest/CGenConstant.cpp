#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ipgdlib::processor;

enum class eSomething { A, B, C };

static std::wstring ToString(const eSomething& esom)
{
	switch (esom)
	{
	case eSomething::A: return L"Something A";
	case eSomething::B: return L"Something B";
	case eSomething::C: return L"Something C";
	}
}

namespace Util
{

	TEST_CLASS(GenConstant)
	{
	public:

		TEST_METHOD(type_enumerate)
		{

			CGenConstant<eSomething> genConstant(eSomething::A);
			Assert::AreEqual<eSomething>(genConstant.get(), eSomething::A);
			Assert::AreEqual<eSomething>(genConstant.get(), eSomething::A);

			genConstant.setConstant(eSomething::B);
			Assert::AreEqual<eSomething>(genConstant.get(), eSomething::B);
			Assert::AreEqual<eSomething>(genConstant.get(), eSomething::B);
		}


		TEST_METHOD(type_size_t)
		{

			CGenConstant<size_t> genConstant(10);
			Assert::AreEqual<size_t>(genConstant.get(), 10);
			Assert::AreEqual<size_t>(genConstant.get(), 10);

			genConstant.setConstant(30);
			Assert::AreEqual<size_t>(genConstant.get(), 30);
			Assert::AreEqual<size_t>(genConstant.get(), 30);
		}

		TEST_METHOD(type_float)
		{

			CGenConstant<float> genConstant(0.0);
			Assert::AreEqual<float>(genConstant.get(), 0.0);
			Assert::AreEqual<float>(genConstant.get(), 0.0);

			genConstant.setConstant(1.0);
			Assert::AreEqual<float>(genConstant.get(), 1.0);
			Assert::AreEqual<float>(genConstant.get(), 1.0);

			genConstant.setConstant(-1.0);
			Assert::AreEqual<float>(genConstant.get(), -1.0);
			Assert::AreEqual<float>(genConstant.get(), -1.0);
		}

		TEST_METHOD(type_double)
		{

			CGenConstant<double> genConstant(0.0);
			Assert::AreEqual<double>(genConstant.get(), 0.0);
			Assert::AreEqual<double>(genConstant.get(), 0.0);

			genConstant.setConstant(1.0);
			Assert::AreEqual<double>(genConstant.get(), 1.0);
			Assert::AreEqual<double>(genConstant.get(), 1.0);
		}
	};
}
