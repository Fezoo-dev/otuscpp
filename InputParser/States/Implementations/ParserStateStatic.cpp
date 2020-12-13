#include <queue>
#include <string>
#include <algorithm>

#include "ParserStateStatic.hpp"

ParserStateStatic::ParserStateStatic(size_t container_size, std::string prefix) : 
    BaseParserState(prefix),
    container_size(container_size)
{
    commands.reserve(container_size);
    //commands.assign(container_size, std::string());
}

ParserStateEnum ParserStateStatic::get_state(){
    return ParserStateEnum::static_state;
}

ParserStateEnum ParserStateStatic::handle_command(const StrategyReadResult& data)
{
    BaseParserState::handle_command(data);

    if(data.is_eof){
        print_commands_wrapper();
        return ParserStateEnum::end;
    }

    if (data.is_command)
    {
        if(index < commands.size())
            commands[index] = data.data;
        else
            commands.push_back(data.data);

        if (++index == container_size)
        {
            print_commands_wrapper();
            reset();
        }
        return get_state();
    }
    else
    {
        if(data.is_block_begin)
            return ParserStateEnum::dynamic_state;
        else
            return ParserStateEnum::error;
    }
    
}

void ParserStateStatic::print_commands_wrapper(){
    print_commands(commands.begin(), next(commands.begin(), index));
}

void ParserStateStatic::reset()
{
    index = 0;
}
