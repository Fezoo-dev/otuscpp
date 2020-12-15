#pragma once
#include <string>

struct StrategyReadData
{
    bool is_eof = true;
    bool is_command = false;
    bool is_block_begin = false;
    bool is_block_end = false;
    std::string data;
};
