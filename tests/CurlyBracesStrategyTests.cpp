#include "CurlyBracesStrategyTests.hpp"

void CurlyBracesStrategyTests::SetUp()
{
    strategy = new CurlyBracesParseStrategy();
}

void CurlyBracesStrategyTests::TearDown()
{
    delete strategy;
}

TEST_F(CurlyBracesStrategyTests, ReadFromEmptyStream_ShouldReturnEOFData)
{
    std::istringstream empty_ss{""};

    auto result = strategy->read(empty_ss);

    ASSERT_TRUE(result.is_eof);
}

TEST_F(CurlyBracesStrategyTests, ReadBeginBlock_ShouldReturnBeginBlockData)
{
    std::istringstream begin_block_ss{"{"};

    auto result = strategy->read(begin_block_ss);

    ASSERT_TRUE(result.is_block_begin);
}

TEST_F(CurlyBracesStrategyTests, ReadEndBlock_ShouldReturnEndBlockData)
{
    std::istringstream end_block_ss{"}"};

    auto result = strategy->read(end_block_ss);

    ASSERT_TRUE(result.is_block_end);
}

TEST_F(CurlyBracesStrategyTests, ReadCommands_ShouldReturnCorrectCommandsData)
{
    StrategyReadData result;
    std::istringstream two_commands_ss{"cmd cmd"};
    const StrategyReadData expected_data{false, true, false, false, "cmd"};

    for(int i = 0; i < 2; i++)
    {
        result = strategy->read(two_commands_ss);
        ASSERT_TRUE(datas_are_equal(result, expected_data));
    }

    result = strategy->read(two_commands_ss);
    ASSERT_TRUE(result.is_eof);
}