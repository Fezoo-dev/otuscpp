#pragma once
#include "../ParseStrategy/StrategyReadResult.hpp"
#include <ctime>
#include <fstream>

enum class ParserStateEnum{
    static_state, dynamic_state,
    error, end
};

struct IParserState {
    virtual ParserStateEnum get_state() = 0;
    virtual ParserStateEnum handle_command(const StrategyReadResult&) = 0;
    virtual void reset() = 0;
    virtual ~IParserState() = 0;
};