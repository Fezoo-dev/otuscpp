#pragma once
#include "../ParseStrategy/StrategyReadData.hpp"
#include <ctime>
#include <fstream>

enum class ParserStateEnum{
    static_state, dynamic_state,
    error, end
};

struct IParserState {
    [[nodiscard]]
    virtual ParserStateEnum get_state() const noexcept = 0;
    [[nodiscard]]
    virtual ParserStateEnum handle_data(const StrategyReadData&) = 0;
    virtual void reset() noexcept = 0;
    virtual ~IParserState() = 0;
};