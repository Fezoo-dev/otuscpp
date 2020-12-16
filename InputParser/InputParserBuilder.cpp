#include "InputParserBuilder.hpp"
#include "States/Implementations/ParserStateStatic.hpp"
#include "States/Implementations/ParserStateDynamic.hpp"
#include "ParseStrategy/Implementations/CurlyBracesParseStrategy.hpp"

InputParser InputParserBuilder::build(std::string prefix, size_t static_container_size){
    InputParser inputParser( new CurlyBracesParseStrategy());

    inputParser.add_state(new ParserStateStatic(static_container_size, prefix));
    inputParser.add_state(new ParserStateDynamic(prefix));
    
    return inputParser;
}