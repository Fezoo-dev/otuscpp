#include "BaseParserState.hpp"

BaseParserState::BaseParserState(std::string prefix) : prefix(prefix) {}

ParserStateEnum BaseParserState::handle_command(const StrategyReadResult &result)
{
    if (result.is_command && is_first_command())
        register_first_command();

    return get_state();
}

bool BaseParserState::is_first_command() const
{
    return filename_timestamp == 0;
}

void BaseParserState::register_first_command()
{
    filename_timestamp = std::time(nullptr);
}
