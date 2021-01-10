#include <iostream>
#include <boost/filesystem.hpp>
#include "CommandLineParser.hpp"
#include "FileFinder.hpp"

int main(int argc, char** argv)
{
    CommandLineParser parser;

    if(!parser.parse(argc, argv, std::cerr))
        std::cout << "parsed" << std::endl;
   // return 1;
    
    //FileFinder ff(parser.get_directories(), parser.get_nesting_level());
    std::vector<std::string> vvv = {"/home/fezoo/tmp/0", "/home/fezoo/tmp/00", "/home/fezoo/tmp/0"};
    FileFinder ff(vvv, 0);

    for(auto& entry : ff)
        std::cout << *entry << std::endl;
    // for (auto it = ff.next(); !ff.end(); it = ff.next())
    // {
    //     std::cout << *it << std::endl;
    // }
    return 0;
}