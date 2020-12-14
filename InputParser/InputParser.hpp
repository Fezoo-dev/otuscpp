#pragma once
#include <memory>
#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include "ParseStrategy/IParseStrategy.hpp"
#include "States/IParserState.hpp"

using CommandType = std::string;

class InputParser
{
public:
    InputParser(IParseStrategy* parse_strategy);

    void add_state(IParserState* state) noexcept;
    void parse(std::istream& from) noexcept;

private:
    IParserState* state = nullptr;
    std::unique_ptr<IParseStrategy> parse_strategy;

    std::map<ParserStateEnum, std::unique_ptr<IParserState>> states;
};
