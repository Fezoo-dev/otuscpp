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
    check_file_and_its_content(expected_filename, get_expected_content());
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
        handle_command(block_end_command);
        handle_command(block_end_command);
    }
    handle_command(good_command);
    handle_command(block_end_command);

    // Assert
    check_file_and_its_content(expected_filename);
}

// TEST_F(DynamicStateSuiteTests, HandleOneCommand_ShouldReturnStaticState)
// {
//     ASSERT_EQ(state->handle_data(good_command), ParserStateEnum::static_state);
// }

// TEST_F(DynamicStateSuiteTests, HandleLessThanBlockSizeCommands_ShouldNotToCreateFile)
// {
//     time_t now = std::time(nullptr);
//     for(size_t i = 0; i < static_block_size - 1; i++)
//         state->handle_data(good_command);

//     std::ifstream stream{prefix + std::to_string(now) + ".log"};

//     ASSERT_EQ((bool)stream, false);
// }

// TEST_F(DynamicStateSuiteTests, HandleExactlyBlockSizeCommands_ShouldToCreateFile)
// {
//     // Arrange
//     time_t now = std::time(nullptr);

//     std::string expected_content = prefix;
//     expected_content += ": ";
//     for(size_t i = 0; i < static_block_size; i++){
//         if(i != 0)
//             expected_content += ", ";

//         expected_content += good_command.data;
//     }

//     // Act
//     for(size_t i = 0; i < static_block_size; i++)
//         state->handle_data(good_command);
        
//     // Assert
//     const std::string file_name = prefix + std::to_string(now) + ".log";
//     std::ifstream stream{file_name};

//     // First check: file should be exists.
//     ASSERT_EQ((bool)stream, true);
    
//     std::string file_content;
//     std::getline(stream, file_content);
//     // Second check: file should contain expected content.
//     ASSERT_EQ(file_content, expected_content);

//     // Cleanup.
//     std::remove(file_name.c_str());
// }
#pragma endregion
