#include "StaticStateSuiteTests.hpp"
#include <fstream>
#include <cstdio>
#include <ctime>

#pragma region Fixture class implementation
void StaticStateSuiteTests::SetUp()
{
    StateBaseSuiteTests::SetUp();
    state = new ParserStateStatic(static_block_size, prefix);
}

void StaticStateSuiteTests::TearDownInternal()
{
    delete state;
}
#pragma endregion

#pragma region get_state tests
TEST_F(StaticStateSuiteTests, GetState_ShouldReturnStaticState)
{
    ASSERT_EQ(state->get_state(), ParserStateEnum::static_state);
}
#pragma endregion

#pragma region handle_data tests
TEST_F(StaticStateSuiteTests, HandleEOFData_ShouldReturnEndState)
{
    ASSERT_EQ(state->handle_data(eof_command), ParserStateEnum::end);
}

TEST_F(StaticStateSuiteTests, HandleNonCommandData_AfterOneCommand_ShouldToCreateFile)
{
    // Arrange
    const std::string expected_filename = get_expected_filename();
    
    // Act
    handle_command(good_command);
    handle_command(eof_command);
        
    // Assert
    check_file_and_its_content(expected_filename);
}

TEST_F(StaticStateSuiteTests, HandleBlockBegin_ShouldReturnDynamicState)
{
    ASSERT_EQ(state->handle_data(block_begin_command), ParserStateEnum::dynamic_state);
}

TEST_F(StaticStateSuiteTests, HandleBlockEnd_ShouldReturnErrorState)
{
    ASSERT_EQ(state->handle_data(block_end_command), ParserStateEnum::error);
}

TEST_F(StaticStateSuiteTests, HandleOneCommand_ShouldReturnStaticState)
{
    ASSERT_EQ(state->handle_data(good_command), ParserStateEnum::static_state);
}

TEST_F(StaticStateSuiteTests, HandleLessThanBlockSizeCommands_ShouldNotToCreateFile)
{
    // Arrange
    const auto expected_filename = get_expected_filename();

    // Act
    for(size_t i = 0; i < static_block_size - 1; i++)
        handle_command(good_command);

    // Assert
    std::ifstream stream{expected_filename};
    ASSERT_FALSE((bool)stream);
}

TEST_F(StaticStateSuiteTests, HandleExactlyBlockSizeCommands_ShouldToCreateFile)
{
    // Arrange
    const auto expected_filename = get_expected_filename();

    // Act
    for(size_t i = 0; i < static_block_size; i++)
        handle_command(good_command);
        
    // Assert
    check_file_and_its_content(expected_filename);
}
#pragma endregion
