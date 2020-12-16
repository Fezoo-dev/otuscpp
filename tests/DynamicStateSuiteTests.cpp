#include "DynamicStateSuiteTests.hpp"
#include <fstream>
#include <cstdio>
#include <ctime>

#pragma region Fixture class implementation
void DynamicStateSuiteTests::SetUp()
{
    StateBaseSuiteTests::SetUp();
    state = new ParserStateDynamic(prefix);
}

void DynamicStateSuiteTests::TearDownInternal()
{
    delete state;
}
#pragma endregion

#pragma region get_state tests
TEST_F(DynamicStateSuiteTests, GetState_ShouldReturnDynamicState)
{
    ASSERT_EQ(state->get_state(), ParserStateEnum::dynamic_state);
}
#pragma endregion

#pragma region handle_data tests
TEST_F(DynamicStateSuiteTests, HandleEOFData_ShouldReturnEndState)
{
    ASSERT_EQ(state->handle_data(eof_command), ParserStateEnum::end);
}

TEST_F(DynamicStateSuiteTests, HandleBlockEnd_ShouldReturnStaticState)
{
    ASSERT_EQ(state->handle_data(block_end_command), ParserStateEnum::static_state);
}

TEST_F(DynamicStateSuiteTests, HandleEOFData_WithoutAnyCommands_ShouldNotToCreateFile)
{
    // Arrange
    const auto expected_filename = get_expected_filename();

    // Act
    state->handle_data(eof_command);

    // Assert
    std::ifstream stream{expected_filename};
    ASSERT_FALSE((bool)stream);
}

TEST_F(DynamicStateSuiteTests, HandleEOFData_AfterOneCommand_ShouldNotToCreateFile)
{
    // Arrange
    const auto expected_filename = get_expected_filename();

    // Act
    state->handle_data(good_command);
    state->handle_data(eof_command);

    // Assert
    std::ifstream stream{expected_filename};
    ASSERT_FALSE((bool)stream);
}

TEST_F(DynamicStateSuiteTests, HandleBlockEnd_AfterGreaterThanZeroCommands_ShouldToCreateFile)
{
    // Arrange
    const auto expected_filename = get_expected_filename();

    // Act
    handle_command(good_command);
    handle_command(block_end_command);

    // Assert
    check_file_and_its_content(expected_filename);
}

TEST_F(DynamicStateSuiteTests, BigNestingTest)
{
    // Arrange
    const auto expected_filename = get_expected_filename();

    // Act
    handle_command(good_command);
    {
        handle_command(block_begin_command);
        handle_command(good_command);
        handle_command(good_command);
        {
            handle_command(block_begin_command);
            handle_command(good_command);
            handle_command(good_command);
            handle_command(good_command);
            handle_command(block_end_command);
        }
        handle_command(good_command);
        handle_command(block_end_command);
    }
    handle_command(good_command);
    handle_command(block_end_command);

    // Assert
    check_file_and_its_content(expected_filename);
}

TEST_F(DynamicStateSuiteTests, HandleTwoCorrectCommandBlocks_ShouldToCreateTwoFiles)
{
    std::string expected_filename;
    for (int i = 0; i < 2; i++)
    {
        expected_filename = get_expected_filename();

        handle_command(good_command, true);
        handle_command(block_end_command);

        check_file_and_its_content(expected_filename);

        reset_state();
    }
}
#pragma endregion
