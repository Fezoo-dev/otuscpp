#pragma once
#include <vector>
#include "../gtest/googletest/include/gtest/gtest.h"

#include "../InputParser/States/IParserState.hpp"

class StateBaseSuiteTests : public ::testing::Test
{
    protected:
    // Sorry, TearDown is final. Use TearDownInternal instead.
    void TearDown() override final;
    // Use this for cleanup managed resources.
    virtual void TearDownInternal();

    std::string get_expected_filename() const;
    std::string get_filename(time_t time) const;
    void check_file_and_its_content(std::string expected_file_name, std::string expected_content) const;

    #pragma region wrapper for handling commands
    void handle_command(const StrategyReadData& command);
    void clear_expected_commands();
    std::string get_expected_content() const;
    void check_file_and_its_content(std::string expected_file_name) const;
    #pragma endregion

    protected:
    // Use SetUp() and TearDownInternal() methods for management resources.
    IParserState* state;

    const std::string prefix = "bulk";
    const StrategyReadData
        eof_command{true, false, false, false},
        good_command{false, true, false, false, "cmd"},
        block_begin_command{false, false, true, false},
        block_end_command{false, false, false, true};

    private:
    std::vector<std::string> handled_commands;
};
