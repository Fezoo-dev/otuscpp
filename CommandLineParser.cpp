#include <iostream>
#include "CommandLineParser.hpp"

CommandLineParser::CommandLineParser()
{
    visible_options.add_options()
        (CommandLineOptions::help, "This help.")
        (CommandLineOptions::exclude, po::value<strings>()->default_value({}, ""), "Exclude directories.")
        (CommandLineOptions::file_mask, po::value<strings>()->default_value({ "*" }, ""), "File masks.")
        (CommandLineOptions::block_size, po::value<size_t>()->default_value(8), "Block size in bytes for read.")
        (CommandLineOptions::nesting_level, po::value<size_t>()->default_value(0), "Nesting level for search.");
        ;

    cmd_line_options.add(visible_options);
    cmd_line_options.add_options()
        (CommandLineOptions::dirs, po::value<strings>(), "Directories for scan.");
}

bool CommandLineParser::parse(int argc, char** argv, std::ostream& error_stream) noexcept
{
    bool parseResult = true;

    try
    {
        po::positional_options_description p;
        p.add(CommandLineOptions::dirs, -1);

        po::variables_map vm;
        po::store(
            po::command_line_parser(argc, argv)
            .options(cmd_line_options)
            .positional(p)
            .run(),
            vm);

        //po::notify(vm);

        move_strings(vm, CommandLineOptions::dirs, dirs);
        move_strings(vm, CommandLineOptions::exclude, exclude_dirs);        
        move_strings(vm, CommandLineOptions::file_mask, file_masks);
        
        block_size = vm[CommandLineOptions::block_size].as<size_t>();
        nesting_level = vm[CommandLineOptions::nesting_level].as<size_t>();

        if (dirs.size() == 0)
        {
            error_stream << std::string(argv[0]) << " path1 [path2 [...]]" << '\n';
            parseResult = false;
        }

        if (vm.count(CommandLineOptions::help))
        {
            error_stream << visible_options;
            parseResult = false;
        }

    }
    catch (std::exception& e)
    {
        error_stream << e.what();
        parseResult = false;
    }

    return parseResult;
}

void CommandLineParser::move_strings(po::variables_map& vm, const char* key, strings& output) noexcept
{
    if (vm.count(key))
        output = std::move(vm[key].as<strings>());
}

const strings& CommandLineParser::get_directories() const noexcept
{
    return dirs;
}

const strings& CommandLineParser::get_exclude_directories() const noexcept
{
    return exclude_dirs;
}

const strings& CommandLineParser::get_file_masks() const noexcept
{
    return file_masks;
}

size_t CommandLineParser::get_block_size() const noexcept
{
    return block_size;
}

size_t CommandLineParser::get_nesting_level() const noexcept
{
    return nesting_level;
}