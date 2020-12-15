#pragma once
#include "StateBaseSuiteTests.hpp"

#include "../InputParser/States/Implementations/ParserStateDynamic.hpp"

class DynamicStateSuiteTests : public StateBaseSuiteTests
{
protected:
    virtual void SetUp() override;
    virtual void TearDownInternal() override;
};
