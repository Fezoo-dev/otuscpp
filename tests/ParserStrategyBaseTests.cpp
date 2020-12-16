#include "ParserStrategyBaseTests.hpp"

bool ParserStrategyBaseTests::datas_are_equal(const StrategyReadData &lhs, const StrategyReadData &rhs) const noexcept
{
    return lhs.is_eof == rhs.is_eof && lhs.is_command == rhs.is_command && lhs.is_block_begin == rhs.is_block_begin && lhs.is_block_end == rhs.is_block_end && lhs.data == rhs.data;
}
