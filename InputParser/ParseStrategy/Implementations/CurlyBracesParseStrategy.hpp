#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../IParseStrategy.hpp"

class CurlyBracesParseStrategy : public IParseStrategy{
public:
    const StrategyReadData& read(std::istream& stream) override;

    ~CurlyBracesParseStrategy() = default;

private:
    StrategyReadData data;
};