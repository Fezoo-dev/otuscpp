#pragma once
#include "../IParserState.hpp"

class BaseParserState : public IParserState
{
public:
    explicit BaseParserState(std::string prefix);

    ParserStateEnum handle_command(const StrategyReadResult& result) override;

protected:
    template <typename ForwardIt>
    void print_commands(ForwardIt from, ForwardIt to)
    {
        if(from == to)
            return;

        current_output.open(prefix + std::to_string(filename_timestamp) + ".log");
        current_output << prefix << ": ";
        for (auto it = from; it != to; ++it)
        {
            if (it != from)
                current_output << ", ";

            current_output << *it;
        }
        current_output << std::endl;
        current_output.close();

        filename_timestamp = 0;
    }

    bool is_first_command() const;

    void register_first_command();

private:
    std::string prefix;
    time_t filename_timestamp = 0;
    std::ofstream current_output;
};
