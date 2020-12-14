#include <memory>
#include <ctime>
#include "InputParser.hpp"

InputParser::InputParser(IParseStrategy *parse_strategy)
    : parse_strategy(parse_strategy)
{
}

void InputParser::add_state(IParserState* state) noexcept
{
    states.emplace(state->get_state(), state);
    if(!this->state)
        this->state = state;
}

void InputParser::parse(std::istream& from) noexcept
{
    ParserStateEnum next_state;
    while (true)
    {
        try
        {
            state->handle_data(
                parse_strategy->read(from)   
            );
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            next_state = ParserStateEnum::error;
        }

        // handle error state here;
        if(next_state == ParserStateEnum::error)
            break;

        if(next_state == ParserStateEnum::end)
            break;
        
        else if (state->get_state() != next_state)
        {
            state = states[next_state].operator->();
            state->reset();
        }
    }
}
