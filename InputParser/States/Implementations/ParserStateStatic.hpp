#pragma once
#include <vector>
#include <string>

#include "BaseParserState.hpp"

class ParserStateStatic : public BaseParserState
{
public:
    explicit ParserStateStatic(size_t container_size, std::string prefix);

    ParserStateEnum handle_data(const StrategyReadData&) override;
    void reset() noexcept override;
    ParserStateEnum get_state() const noexcept override;

    ~ParserStateStatic() = default;
private:
    void print_commands_wrapper();

private:
    size_t container_size;
    std::vector<std::string> commands;
    size_t index = 0;
};