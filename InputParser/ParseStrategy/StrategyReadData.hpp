#pragma once
#include <string>

struct StrategyReadData
{
    bool is_eof;
    bool is_command;
    bool is_block_begin = true;
    bool is_block_end = false;
    std::string data;
};
