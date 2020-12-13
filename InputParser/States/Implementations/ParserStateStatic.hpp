#pragma once
#include <vector>
#include <string>

#include "BaseParserState.hpp"

class ParserStateStatic : public BaseParserState
{
public:
    explicit ParserStateStatic(size_t container_size, std::string prefix);

    ParserStateEnum handle_command(const StrategyReadResult&) override;
    void reset() override;
    ParserStateEnum get_state() override;

    ~ParserStateStatic() = default;

private:
    void print_commands_wrapper();

private:
    size_t container_size;
    std::vector<std::string> commands;
    size_t index = 0;
};