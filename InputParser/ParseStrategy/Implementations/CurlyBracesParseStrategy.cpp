#include "CurlyBracesParseStrategy.hpp"

const StrategyReadResult& CurlyBracesParseStrategy::read(std::istream& stream) noexcept
{
    data.is_eof = !(stream >> data.data);
    data.is_block_begin = data.data == "{";
    data.is_block_end = data.data == "}";
    data.is_command = !(data.is_eof || data.is_block_begin || data.is_block_end);
    return data;
}