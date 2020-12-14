#include <queue>
#include <string>
#include <algorithm>

#include "ParserStateDynamic.hpp"

ParserStateDynamic::ParserStateDynamic(std::string prefix) : BaseParserState(prefix)
{
}

ParserStateEnum ParserStateDynamic::get_state() const noexcept{
    return ParserStateEnum::dynamic_state;
}

ParserStateEnum ParserStateDynamic::handle_data(const StrategyReadData& data)
{
    BaseParserState::handle_data(data);

    if(data.is_eof){
        return ParserStateEnum::end;
    }

    if (data.is_command)
    {
        if(index < commands.size())
        {
            commands[index] = data.data;
        }
        else
        {
            commands.push_back(data.data);
        }
        index++;
    }
    else
    {
        if(data.is_block_begin)
        {
            nesting_level++;
        }
        else if(data.is_block_end)
        {
            if(nesting_level == 0)
            {
                print_commands_wrapper();
                return ParserStateEnum::static_state;
            }
            else
            {
                if(nesting_level > 0)
                    nesting_level--;
                else
                    return ParserStateEnum::error;
            }
        }
    }
    
    return get_state();
}

void ParserStateDynamic::print_commands_wrapper() noexcept
{
    print_commands(commands.begin(), next(commands.begin(), index));
}

void ParserStateDynamic::reset() noexcept
{
    index = 0;
    nesting_level = 0;
}
