#pragma once
#include <vector>
#include <string>

#include "BaseParserState.hpp"

class ParserStateDynamic : public BaseParserState
{
public:
    ParserStateDynamic(std::string prefix);

    ParserStateEnum handle_command(const StrategyReadResult&) override;
    void reset() override;
    ParserStateEnum get_state() override;

    ~ParserStateDynamic() = default;

private:
    void print_commands_wrapper();

private:
    std::vector<std::string> commands;
    size_t index = 0;
    size_t nesting_level = 0;
};