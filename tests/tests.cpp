#include "../gtest/googletest/include/gtest/gtest.h"

#include "StaticStateSuiteTests.hpp"


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}