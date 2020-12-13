#pragma once
#include <string>
#include <iostream>
#include "StrategyReadResult.hpp"

struct IParseStrategy
{
    virtual ~IParseStrategy() = 0;
    
    virtual const StrategyReadResult& read(std::istream& stream) noexcept = 0;
};