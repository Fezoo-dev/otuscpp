#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../IParseStrategy.hpp"

class CurlyBracesParseStrategy : public IParseStrategy{
public:
    const StrategyReadResult& read(std::istream& stream) noexcept override;

    ~CurlyBracesParseStrategy() = default;

private:
    StrategyReadResult data;
};