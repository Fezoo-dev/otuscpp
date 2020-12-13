#include <iostream>
#include <fstream>
#include <map>
#include <queue>

#include "InputParser/States/Implementations/ParserStateStatic.hpp"
#include "InputParser/States/Implementations/ParserStateDynamic.hpp"
#include "InputParser/ParseStrategy/Implementations/CurlyBracesParseStrategy.hpp"
#include "InputParser/InputParser.hpp"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " N";
        return 1;
    }

    size_t N = std::stoi(argv[1]);

    const std::string prefix = "bulk";
    
    InputParser inputParser( new CurlyBracesParseStrategy());
    inputParser.add_state(new ParserStateStatic(N, prefix));
    inputParser.add_state(new ParserStateDynamic(prefix));

    inputParser.parse(std::cin);

    return 0;
}