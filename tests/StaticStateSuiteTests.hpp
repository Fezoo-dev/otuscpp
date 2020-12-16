#pragma once
#include "StateBaseSuiteTests.hpp"

#include "../InputParser/States/Implementations/ParserStateStatic.hpp"

class StaticStateSuiteTests : public StateBaseSuiteTests
{
protected:
    virtual void SetUp() override;
    virtual void TearDownInternal() override;

    const size_t static_block_size = 3;
};
