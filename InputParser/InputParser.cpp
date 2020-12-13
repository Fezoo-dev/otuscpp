#include <memory>
#include <ctime>
#include "InputParser.hpp"

InputParser::InputParser(IParseStrategy *parse_strategy)
    : parse_strategy(parse_strategy)
{
}

void InputParser::add_state(IParserState* state){
    states.emplace(state->get_state(), state);
    if(!this->state)
        this->state = state;
}

void InputParser::parse(std::istream &from)
{
    while (true)
    {
        auto next_state = state->handle_command(
            parse_strategy->read(from));

        if(next_state == ParserStateEnum::end || next_state == ParserStateEnum::error)
            break;
        
        else if (state->get_state() != next_state)
        {
            state = states[next_state].operator->();
            state->reset();
        }
    }
}
