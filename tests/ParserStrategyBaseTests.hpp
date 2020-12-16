#pragma once
#include "../gtest/googletest/include/gtest/gtest.h"

#include "../InputParser/ParseStrategy/IParseStrategy.hpp"

class ParserStrategyBaseTests : public ::testing::Test
{
    protected:
    [[nodiscard]]
    bool datas_are_equal (const StrategyReadData& lhs, const StrategyReadData& rhs) const noexcept;

    protected:
    IParseStrategy* strategy;
};