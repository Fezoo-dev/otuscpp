#include "InputParser/InputParserBuilder.hpp"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " N" << std::endl;
        return 1;
    }

    size_t N = std::stoi(argv[1]);

    const std::string prefix = "bulk";
    
    auto parser = InputParserBuilder::build(prefix, N);

    parser.parse(std::cin);

    return 0;
}