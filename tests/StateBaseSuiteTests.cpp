#include "StateBaseSuiteTests.hpp"
#include <ctime>
#include <fstream>
#include <thread>

using namespace std::chrono_literals;

void StateBaseSuiteTests::TearDown()
{
    reset_state();
    TearDownInternal();
}

void StateBaseSuiteTests::TearDownInternal()
{

}

std::string StateBaseSuiteTests::get_expected_filename() const
{
    return get_filename(std::time(nullptr));
}

std::string StateBaseSuiteTests::get_filename(time_t time) const
{
    return prefix + std::to_string(time) + ".log";
}

std::string StateBaseSuiteTests::get_expected_content() const
{
    if(handled_commands.size() == 0)
        return {};

    std::string expected_content = prefix + ": ";
    bool is_first = true;
    for(size_t i = 0; i < handled_commands.size(); i++)
    {
        if(!is_first)
            expected_content += ", ";

        is_first = false;
        expected_content += handled_commands[i];
    }

    return expected_content;
}

void StateBaseSuiteTests::handle_command(const StrategyReadData& data, bool wait)
{
    if(data.is_command)
        handled_commands.push_back(data.data);

    state->handle_data(data);
    if(wait)
        std::this_thread::sleep_for(1s);
}

void StateBaseSuiteTests::reset_state()
{
    handled_commands.clear();
    state->reset();
}

void StateBaseSuiteTests::check_file_and_its_content(std::string expected_file_name) const
{
    return check_file_and_its_content(expected_file_name, get_expected_content());
}

void StateBaseSuiteTests::check_file_and_its_content(std::string expected_file_name, std::string expected_content) const
{
    std::ifstream stream{expected_file_name};

    // First check: file should be exists.
    ASSERT_TRUE((bool)stream);
    
    std::string file_content;
    std::getline(stream, file_content);

    // Second check: file should contains expected content.
    ASSERT_EQ(file_content, expected_content);

    // Cleanup.
    std::remove(expected_file_name.c_str());
}
