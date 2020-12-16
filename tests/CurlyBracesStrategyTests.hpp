#pragma once
#include "ParserStrategyBaseTests.hpp"
#include "../InputParser/ParseStrategy/Implementations/CurlyBracesParseStrategy.hpp"

class CurlyBracesStrategyTests : public ParserStrategyBaseTests
{
    protected:
    void SetUp() override;
    void TearDown() override;
};
