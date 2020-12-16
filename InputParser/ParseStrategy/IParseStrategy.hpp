#pragma once
#include <string>
#include <iostream>
#include "StrategyReadData.hpp"

struct IParseStrategy
{
    [[nodiscard]]
    virtual const StrategyReadData& read(std::istream& stream) = 0;

    virtual ~IParseStrategy() = 0;
};