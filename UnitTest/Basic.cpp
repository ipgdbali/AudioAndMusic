#include "pch.h"
#include "CppUnitTest.h"
#include "../AudioGenerator/CGenConstant.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace ipgdlib;
using namespace ipgdlib::stream;

namespace UnitTest
{
	TEST_CLASS(CGenConstant)
	{
	public:
		
		TEST_METHOD(Define)
		{
			auto pGenConstant = new stream::CGenConstant<float>(440.0);
		}


	};
}
